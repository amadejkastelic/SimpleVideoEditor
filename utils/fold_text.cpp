#include "fold_text.h"


FoldedText::FoldedText(QObject *parent) : QObject(parent) {}

QSizeF FoldedText::intrinsicSize(QTextDocument *doc, int pos, const QTextFormat &format) {
    Q_UNUSED(doc)
    Q_UNUSED(pos)
    Q_ASSERT(format.type() == format.CharFormat);
    const auto &charFormat = reinterpret_cast<const QTextCharFormat&>(format);

    auto font = charFormat.font();
    QFontMetrics fontMetrics(font);

    QSizeF size = fontMetrics.boundingRect(*foldedText).size();

    return size;
}

void FoldedText::drawObject(QPainter *painter, const QRectF &rect, QTextDocument *doc, int pos, const QTextFormat &format) {
    Q_UNUSED(doc)
    Q_UNUSED(pos)
    Q_ASSERT(format.type() == format.CharFormat);

    painter->drawText(rect, *foldedText);
    painter->drawRect(rect);
}

Q_DECLARE_METATYPE(QTextDocumentFragment)

void FoldedText::fold(QTextCursor cursor) {
    QTextCharFormat textFormat;
    textFormat.setObjectType(type());

    /*cursor.setPosition(cursor.Down, QTextCursor::MoveAnchor);
    cursor.setPosition(cursor.EndOfLine, QTextCursor::KeepAnchor);
    cursor.setPosition(cursor.Down, QTextCursor::MoveAnchor);
    cursor.setPosition(cursor.EndOfLine, QTextCursor::KeepAnchor);*/
    cursor.select(QTextCursor::Document);

    QVariant variant;
    variant.setValue(cursor.selection());

    textFormat.setProperty(prop(), variant);
    cursor.insertText(QString(QChar::ObjectReplacementCharacter), textFormat);
}

bool FoldedText::unfold(QTextCursor cursor) {
    if (cursor.hasSelection()) {
        return false;
    }

    QTextCharFormat textFormat = cursor.charFormat();
    if (textFormat.objectType() == type()) {
        cursor.movePosition(cursor.Left, cursor.KeepAnchor);
        QVariant variant = textFormat.property(prop());
        auto fragment = variant.value<QTextDocumentFragment>();
        cursor.select(QTextCursor::LineUnderCursor);
        cursor.removeSelectedText();
        cursor.insertFragment(fragment);
        return true;
    }

    return false;
}
