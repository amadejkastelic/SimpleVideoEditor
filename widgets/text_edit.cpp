#include "text_edit.h"

void MyTextEdit::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Tab) {
        QTextEdit::insertPlainText("    ");
    } else {
        QTextEdit::keyPressEvent(event);
    }
    //QTextEdit::keyPressEvent(event);
}

MyTextEdit::MyTextEdit(const QString &text, QWidget *parent) : QTextEdit(text, parent) {
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
