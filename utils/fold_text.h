#pragma once

#include <iostream>
#include <QObject>
#include <QPainter>
#include <QTextDocument>
#include <QTextBlock>
#include <QTextObjectInterface>
#include <QTextDocumentFragment>

using namespace std;

class FoldedText : public QObject, public QTextObjectInterface {

    Q_OBJECT
    Q_INTERFACES(QTextObjectInterface)

private:
    const QString *foldedText = new QString(" ... ");

public:
    explicit FoldedText(QObject *parent = nullptr);
    static int type() {
        return QTextFormat::UserObject + 2;
    }
    static int prop() {
        return 2;
    }
    QSizeF intrinsicSize(QTextDocument *doc, int pos, const QTextFormat &format) override;
    void drawObject(QPainter *painter, const QRectF &rect, QTextDocument *doc, int pos, const QTextFormat &format) override;
    void fold(QTextCursor cursor);
    bool unfold(QTextCursor cursor);
};