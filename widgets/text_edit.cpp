#include "text_edit.h"


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

    const bool isShortcut = (event->modifiers().testFlag(Qt::ControlModifier) && event->key() == Qt::Key_Space);

    if (!m_completer || !isShortcut) {
        if (event->key() == Qt::Key_Tab) {
            QPlainTextEdit::insertPlainText("    ");
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

MyTextEdit::MyTextEdit(const QString &text, QWidget *parent) : QPlainTextEdit(text, parent) {
    highlightColor = new QColor(23, 23, 23);

    lineNumberArea = new LineNumberArea(this);

    connect(this, &MyTextEdit::blockCountChanged, this, &MyTextEdit::updateLineNumberAreaWidth);
    connect(this, &MyTextEdit::updateRequest, this, &MyTextEdit::updateLineNumberArea);
    connect(this, &MyTextEdit::cursorPositionChanged, this, &MyTextEdit::highlightCurrentLine);

    updateLineNumberAreaWidth(0);
    highlightCurrentLine();

    setAcceptDrops(true);
    setFont();

    // load workspace
    auto settingsPath = QSettings().fileName().left(QSettings().fileName().lastIndexOf("/") + 1);
    m_workspace = new QFile(settingsPath.append("workspace.sve"));
    if (m_workspace->exists() && m_workspace->open(QIODevice::ReadWrite)) {
        QTextStream stream(m_workspace);
        setPlainText(stream.readAll());
    }
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
    if (m_completer) {
        m_completer->setWidget(this);
    }
    QPlainTextEdit::focusInEvent(event);
}

void MyTextEdit::setCompleter(QCompleter *completer) {
    m_completer = completer;
}

void MyTextEdit::keyReleaseEvent(QKeyEvent *event) {
    // save workspace
    if (!m_workspace->isOpen()) {
        m_workspace->open(QIODevice::ReadWrite);
    }
    m_workspace->resize(0);
    QTextStream stream(m_workspace);
    stream << MyTextEdit::toPlainText();
    stream.flush();

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

void MyTextEdit::updateLineNumberAreaWidth(int newBlockCount) {
    setViewportMargins(lineNumberAreaWidth(), 0, 0, 0);
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

void MyTextEdit::resizeEvent(QResizeEvent *event) {
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

void MyTextEdit::lineNumberAreaPaintEvent(QPaintEvent *event) {
    QPainter painter(lineNumberArea);
    painter.fillRect(event->rect(), Qt::lightGray);

    QTextBlock block = firstVisibleBlock();
    int blockNumber = block.blockNumber();
    int top = qRound(blockBoundingGeometry(block).translated(contentOffset()).top());
    int bottom = top + qRound(blockBoundingRect(block).height());

    while (block.isValid() && top <= event->rect().bottom()) {
        if (block.isVisible() && bottom >= event->rect().top()) {
            QString number = QString::number(blockNumber + 1);
            painter.setPen(Qt::white);
            painter.drawText(0, top, lineNumberArea->width(), fontMetrics().height(),
                             Qt::AlignRight, number);
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
