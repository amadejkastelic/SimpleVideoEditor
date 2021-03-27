#include "text_edit.h"
#include "../editor.h"

void MyTextEdit::keyPressEvent(QKeyEvent *event) {
    if (m_completer && m_completer->popup()->isVisible()) {
        switch (event->key()) {
            case Qt::Key_Enter:
            case Qt::Key_Return:
            case Qt::Key_Escape:
            case Qt::Key_Tab:
            case Qt::Key_Backtab:
                event->ignore();
                return;
            default:
                break;
        }
    }

    if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter) {
        QTextCursor cursor = this->textCursor();
        cursor.select(QTextCursor::LineUnderCursor);
        QString line = cursor.selection().toPlainText().trimmed();
        if (line == "part:video") {
            cursor.removeSelectedText();
            cursor.insertText(QString(section_video));
            return;
        } else if (line == "part:image") {
            cursor.removeSelectedText();
            cursor.insertText(QString(section_image));
            return;
        } else if (line == "part:text") {
            cursor.removeSelectedText();
            cursor.insertText(QString(section_text));
            return;
        } else if (line == "part:audio") {
            cursor.removeSelectedText();
            cursor.insertText(QString(section_audio));
            return;
        }
        cursor.clearSelection();
    }

    if (event->modifiers().testFlag(Qt::ControlModifier)) {
        QTextCursor cursor = this->textCursor();
        switch (event->key()) {
            case Qt::Key_S:
                cerr << "Saving workspace..." << endl;
                saveWorkspace();
                return;
            case Qt::Key_X:
                if (cursor.selectedText().isEmpty()) {
                    cursor.select(QTextCursor::LineUnderCursor);
                    cerr << cursor.selection().toPlainText().toStdString() << endl;
                    QClipboard *clipboard = QGuiApplication::clipboard();
                    clipboard->setText(cursor.selectedText() + "\n");
                    cursor.removeSelectedText();
                    cursor.deleteChar();
                    return;
                }
                break;
            case Qt::Key_D:
                cursor.select(QTextCursor::LineUnderCursor);
                QString text = cursor.selectedText();
                cursor.clearSelection();
                cursor.movePosition(QTextCursor::EndOfLine);
                cursor.insertText("\n" + text);
                return;
        }
    }

    const bool isShortcut = (event->modifiers().testFlag(Qt::ControlModifier) && event->key() == Qt::Key_Space);

    if (!m_completer || !isShortcut) {
        if (event->key() == Qt::Key_Tab) {
            QPlainTextEdit::insertPlainText("    ");
        } else if (event->key() == Qt::Key_Return) {
            QString temp = this->textCursor().block().text().split(":")[0];
            uint spaces = temp.length() - temp.trimmed().length();
            if (temp.contains("part") || temp.contains("audio") || temp.contains("text")) {
                spaces += 4;
            }
            QPlainTextEdit::insertPlainText("\n");
            for (int i = 0; i < spaces; i++) {
                QPlainTextEdit::insertPlainText(" ");
            }
        } else if (event->key() == Qt::Key_Backspace) {
            QString line = this->textCursor().block().text();
            if (line.length() > 0 && line.trimmed().isEmpty()) {
                int toDelete = 4;
                if (line.length() < 4) {
                    toDelete = line.length();
                }
                for (int i = 0; i < toDelete; i++) {
                    this->textCursor().deletePreviousChar();
                }
            } else {
                QPlainTextEdit::keyPressEvent(event);
            }
        } else {
            QPlainTextEdit::keyPressEvent(event);
        }
        //return;
    }

    const bool ctrlOrShift = event->modifiers().testFlag(Qt::ControlModifier) ||
            event->modifiers().testFlag(Qt::ShiftModifier);
    if (!m_completer || (ctrlOrShift && event->text().isEmpty())) {
        return;
    }

    static QString eow("~!@#$%^&*()_+{}|:\"<>?,./;'[]\\-="); // end of word
    const bool hasModifier = (event->modifiers() != Qt::NoModifier) && !ctrlOrShift;
    QString completionPrefix = textUnderCursor();
    std::cerr << completionPrefix.toStdString() << std::endl;

    if (!isShortcut && (hasModifier || event->text().isEmpty()|| completionPrefix.length() < 1
                        || eow.contains(event->text().right(1)))) {
        m_completer->popup()->hide();
        return;
    }

    if (completionPrefix != m_completer->completionPrefix()) {
        m_completer->setCompletionPrefix(completionPrefix);
        m_completer->popup()->setCurrentIndex(m_completer->completionModel()->index(0, 0));
    }
    QRect cr = cursorRect();
    cr.setWidth(m_completer->popup()->sizeHintForColumn(0)
                + m_completer->popup()->verticalScrollBar()->sizeHint().width());
    m_completer->complete(cr);
}

MyTextEdit::MyTextEdit(Editor *editor) : QPlainTextEdit(editor) {
    m_parent = editor;

    foldHandler = new FoldedText(this);
    this->document()->documentLayout()->registerHandler(FoldedText::type(), foldHandler);
    this->setLineWrapMode(NoWrap);

    backgroundColor = new QColor(33, 33, 33);
    selectionColor = new QColor(53, 53, 53);
    highlightColor = new QColor(18, 18, 18);
    lineNumberColor = new QColor(66, 66, 66);

    setAcceptDrops(true);
    setFont();

    QPalette palette = this->palette();
    palette.setColor(QPalette::All, QPalette::Base, *backgroundColor);
    this->setPalette(palette);
    this->setBackgroundVisible(false);

    // load workspace
    auto settingsPath = QSettings().fileName().left(QSettings().fileName().lastIndexOf("/") + 1);
    m_workspace = new QFile(settingsPath.append("workspace.sve"));
    if (m_workspace->exists() && m_workspace->open(QIODevice::ReadWrite)) {
        QTextStream stream(m_workspace);
        setPlainText(stream.readAll());
    }

    // add line numbers
    lineNumberArea = new LineNumberArea(this);
    connect(this, &MyTextEdit::blockCountChanged, this, &MyTextEdit::updateLineNumberAreaWidth);
    connect(this, &MyTextEdit::updateRequest, this, &MyTextEdit::updateLineNumberArea);
    connect(this, &MyTextEdit::cursorPositionChanged, this, &MyTextEdit::highlightCurrentLine);
    updateLineNumberAreaWidth(0);

    // add buttons
    buttonArea = new ButtonArea(this);
    connect(this, &MyTextEdit::blockCountChanged, this, &MyTextEdit::updateButtonAreaWidth);
    connect(this, &MyTextEdit::updateRequest, this, &MyTextEdit::updateButtonArea);
    updateButtonAreaWidth(0);

    highlightCurrentLine();
}

void MyTextEdit::setFont() {
    QFont font;
    font.setFamily("Fira Code");
    font.setStyleHint(QFont::Monospace);
    font.setFixedPitch(true);
    font.setPointSize(12);

    QFontMetricsF metrics(font);
    auto stopWidth = 4 * metrics.width(' ');
    auto letterSpacing = (ceil(stopWidth) - stopWidth) / 4;

    font.setLetterSpacing(QFont::AbsoluteSpacing, letterSpacing);

    QPlainTextEdit::setFont(font);
    QPlainTextEdit::setTabStopDistance(stopWidth);
}

QCompleter *MyTextEdit::completer() const {
    return m_completer;
}

void MyTextEdit::insertCompletion(const QString &completion) {
    if (m_completer->widget() != this) {
        return;
    }
    QTextCursor tc = textCursor();
    int extra = completion.length() - m_completer->completionPrefix().length();
    tc.movePosition(QTextCursor::Left);
    tc.movePosition(QTextCursor::EndOfWord);
    tc.insertText(completion.right(extra));
    setTextCursor(tc);
}

QString MyTextEdit::textUnderCursor() const {
    QTextCursor tc = textCursor();
    tc.select(QTextCursor::WordUnderCursor);
    return tc.selectedText();
}

void MyTextEdit::focusInEvent(QFocusEvent *event) {
    /*if (m_completer) {
        m_completer->setWidget(this);
    }*/
    QPlainTextEdit::focusInEvent(event);
}

void MyTextEdit::setCompleter(QCompleter *completer) {
    m_completer = completer;
}

void MyTextEdit::saveWorkspace() {
    // save workspace
    if (!m_workspace->isOpen()) {
        m_workspace->open(QIODevice::ReadWrite);
    }
    m_workspace->resize(0);
    QTextStream stream(m_workspace);
    stream << MyTextEdit::toPlainText();
    stream.flush();
}

void MyTextEdit::keyReleaseEvent(QKeyEvent *event) {
    saveWorkspace();
    QPlainTextEdit::keyReleaseEvent(event);
}

int MyTextEdit::lineNumberAreaWidth() {
    int digits = 1;
    int max = qMax(1, blockCount());
    while (max >= 10) {
        max /= 10;
        ++digits;
    }

    int space = 3 + fontMetrics().horizontalAdvance(QLatin1Char('9')) * digits;

    return space;
}

void MyTextEdit::updateLineNumberAreaWidth(int) {
    setViewportMargins(lineNumberAreaWidth() * 2, 0, 0, 0);
}

void MyTextEdit::updateButtonAreaWidth(int) {
    setViewportMargins(lineNumberAreaWidth() * 2, 0, 0, 0);
}

void MyTextEdit::updateLineNumberArea(const QRect &rect, int dy) {
    if (dy) {
        lineNumberArea->scroll(0, dy);
    } else {
        lineNumberArea->update(0, rect.y(), lineNumberArea->width(), rect.height());
    }

    if (rect.contains(viewport()->rect())) {
        updateLineNumberAreaWidth(0);
    }
}

void MyTextEdit::updateButtonArea(const QRect &rect, int dy) {
    if (dy) {
        buttonArea->scroll(0, dy);
    } else {
        buttonArea->update(0, rect.y(), buttonArea->width(), rect.height());
    }

    if (rect.contains(viewport()->rect())) {
        updateButtonAreaWidth(0);
    }
}

void MyTextEdit::resizeEvent(QResizeEvent *event) {
    QPlainTextEdit::resizeEvent(event);

    QRect cr = contentsRect();
    lineNumberArea->setGeometry(QRect(cr.left(), cr.top(), lineNumberAreaWidth(), cr.height()));
    buttonArea->setGeometry(QRect(cr.left() + lineNumberAreaWidth(), cr.top(), lineNumberAreaWidth(), cr.height()));
}

void MyTextEdit::lineNumberAreaPaintEvent(QPaintEvent *event) {
    QPainter painter(lineNumberArea);
    painter.fillRect(event->rect(), *backgroundColor);

    QTextBlock block = firstVisibleBlock();
    int blockNumber = block.blockNumber();
    int top = qRound(blockBoundingGeometry(block).translated(contentOffset()).top());
    int bottom = top + qRound(blockBoundingRect(block).height());

    while (block.isValid() && top <= event->rect().bottom()) {
        if (block.isVisible() && bottom >= event->rect().top()) {
            QString number = QString::number(blockNumber + 1);
            painter.setPen(*lineNumberColor);
            painter.drawText(0, top, lineNumberArea->width(), fontMetrics().height(),
                             Qt::AlignRight, number);
        }

        block = block.next();
        top = bottom;
        bottom = top + qRound(blockBoundingRect(block).height());
        ++blockNumber;
    }
}

void MyTextEdit::buttonAreaPaintEvent(QPaintEvent *event) {
    QPainter painter(buttonArea);
    painter.fillRect(event->rect(), *backgroundColor);

    QTextBlock block = firstVisibleBlock();
    int blockNumber = block.blockNumber();
    int top = qRound(blockBoundingGeometry(block).translated(contentOffset()).top());
    int bottom = top + qRound(blockBoundingRect(block).height());

    while (block.isValid() && top <= event->rect().bottom()) {
        if (block.isVisible() && bottom >= event->rect().top()) {
            /*QString number = QString::number(blockNumber + 1);
            painter.setPen(*lineNumberColor);
            painter.drawText(0, top, buttonArea->width(), fontMetrics().height(),
                             Qt::AlignRight, number);*/
            if (block.text().contains("path:")) {
                painter.setPen(*lineNumberColor); // TODO: change color
                painter.drawText(0, top, buttonArea->width(), fontMetrics().height(),
                                 Qt::AlignCenter, "▶️");
            } else if (block.text().contains("font:")) {
                painter.drawText(0, top, buttonArea->width(), fontMetrics().height(),
                                 Qt::AlignCenter, "🆎");
            } else if (block.text().contains("color:")) {
                painter.drawText(0, top, buttonArea->width(), fontMetrics().height(),
                                 Qt::AlignCenter, "🎨");
            } else if (block.text().contains(QChar::ObjectReplacementCharacter)) {
                painter.drawText(0, top, buttonArea->width(), fontMetrics().height(),
                                 Qt::AlignCenter, "+");
            } else if (block.text().contains("part:") || block.text().contains("variables:")) {
                painter.drawText(0, top, buttonArea->width(), fontMetrics().height(),
                                 Qt::AlignCenter, "-");
            }
        }

        block = block.next();
        top = bottom;
        bottom = top + qRound(blockBoundingRect(block).height());
        ++blockNumber;
    }
}

void MyTextEdit::highlightCurrentLine() {
    QList<QTextEdit::ExtraSelection> extraSelections;

    if (!isReadOnly()) {
        QTextEdit::ExtraSelection selection;
        selection.format.setBackground(*highlightColor);
        selection.format.setProperty(QTextFormat::FullWidthSelection, true);
        selection.cursor = textCursor();
        selection.cursor.clearSelection();
        extraSelections.append(selection);
    }

    setExtraSelections(extraSelections);
}

void MyTextEdit::buttonPressEvent(QMouseEvent *event) {
    int lineNumber = ceil(event->localPos().y()/fontMetrics().height()) +  firstVisibleBlock().blockNumber();
    cerr << "Clicked line number: " << lineNumber << endl;
    m_parent->SideButtonClick(lineNumber);
}

void MyTextEdit::fold() {
    foldHandler->fold(this->textCursor());
}

void MyTextEdit::unfold() {
    foldHandler->unfold(this->textCursor());
}
