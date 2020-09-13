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
            QTextEdit::insertPlainText("    ");
        } else {
            QTextEdit::keyPressEvent(event);
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

MyTextEdit::MyTextEdit(const QString &text, QWidget *parent) : QTextEdit(text, parent) {
    setAcceptDrops(true);
    setFont();
    setAcceptRichText(false);
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

    QTextEdit::setFont(font);
    QTextEdit::setTabStopDistance(stopWidth);
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
    QTextEdit::focusInEvent(event);
}

void MyTextEdit::setCompleter(QCompleter *completer) {
    m_completer = completer;
}
