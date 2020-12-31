#include "fold_text.h"


FoldedText::FoldedText(QObject *parent) : QObject(parent) {}

QSizeF FoldedText::intrinsicSize(QTextDocument *doc, int pos, const QTextFormat &format) {
    Q_UNUSED(doc)
    Q_UNUSED(pos)
    Q_ASSERT(format.type() == format.CharFormat);
    const auto &charFormat = reinterpret_cast<const QTextCharFormat&>(format);

    auto font = charFormat.font();
    QFontMetrics fontMetrics(font);

    QSizeF size = QSizeF(fontMetrics.boundingRect(*foldedText).width()*1.05,
                         fontMetrics.boundingRect(*foldedText).height()*0.6);

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

    QString command;
    if (cursor.block().text().startsWith("- variables:")) {
        command = "- part:";
    } else {
        command = cursor.block().text();
    }

    cursor.clearSelection();
    cursor.movePosition(QTextCursor::EndOfLine);

    int i = cursor.blockNumber()+1;
    while (!cursor.document()->findBlockByLineNumber(i).text().startsWith(command) && i < cursor.document()->lineCount()) {
        cursor.movePosition(QTextCursor::Down, QTextCursor::KeepAnchor);
        cursor.movePosition(QTextCursor::EndOfLine, QTextCursor::KeepAnchor);
        i++;
    }

    QVariant variant;
    variant.setValue(cursor.selection());

    cerr << variant.value<QTextDocumentFragment>().toPlainText().toStdString() << endl;

    textFormat.setProperty(prop(), variant);
    cursor.insertText(QString(QChar::ObjectReplacementCharacter), textFormat);
}

bool FoldedText::unfold(QTextCursor cursor) {
    if (cursor.hasSelection()) {
        return false;
    }

    cursor.movePosition(cursor.EndOfLine, cursor.MoveAnchor);
    while (cursor.selectedText() != QChar::ObjectReplacementCharacter) {
        cursor.clearSelection();
        cursor.movePosition(cursor.Left, cursor.KeepAnchor);
    }
    cursor.clearSelection();
    cursor.movePosition(QTextCursor::StartOfLine, QTextCursor::KeepAnchor);
    QString temp = cursor.selectedText();
    cursor.removeSelectedText();
    cursor.clearSelection();

    cursor.movePosition(QTextCursor::EndOfLine, QTextCursor::MoveAnchor);
    cursor.movePosition(cursor.Left, cursor.KeepAnchor);
    QVariant variant = cursor.charFormat().property(prop());
    auto fragment = variant.value<QTextDocumentFragment>();
    cursor.select(QTextCursor::LineUnderCursor);
    cursor.removeSelectedText();
    cursor.insertText(temp);
    cursor.insertFragment(fragment);
    return true;
}
