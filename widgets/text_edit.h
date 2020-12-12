#pragma once

#include <cmath>
#include <iostream>
#include <QPlainTextEdit>
#include <QFont>
#include <QSettings>
#include <QTextStream>
#include <QKeyEvent>
#include <QCompleter>
#include <QFontDatabase>
#include <QAbstractItemView>
#include <QScrollBar>
#include <QPainter>
#include <QTextBlock>
#include <QPaintEvent>
#include <QResizeEvent>
#include <QPushButton>

using namespace std;

class Editor;

class LineNumberArea;

class MyTextEdit : public QPlainTextEdit {

    Q_OBJECT

private:
    Editor *m_parent;
    QColor *backgroundColor;
    QColor *highlightColor;
    QColor *selectionColor;
    QColor *lineNumberColor;
    void setFont();
    QString textUnderCursor() const;
    QCompleter *m_completer = nullptr;
    QFile *m_workspace;
    QWidget *lineNumberArea;
    QWidget *buttonArea;

private slots:
    void updateLineNumberAreaWidth(int newBlockCount);
    void updateButtonAreaWidth(int newBlockCount);
    void highlightCurrentLine();
    void updateLineNumberArea(const QRect &rect, int dy);
    void updateButtonArea(const QRect &rect, int dy);

public:
    explicit MyTextEdit(Editor *editor = nullptr);
    void setCompleter(QCompleter *completer);
    QCompleter *completer() const;
    void lineNumberAreaPaintEvent(QPaintEvent *event);
    void buttonAreaPaintEvent(QPaintEvent *event);
    int lineNumberAreaWidth();
    void buttonPressEvent(QMouseEvent *event);

public slots:
    void insertCompletion(const QString &completion);

protected:
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;
    void focusInEvent(QFocusEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
};

class LineNumberArea : public QWidget {

    Q_OBJECT

public:
    explicit LineNumberArea(MyTextEdit *editor) : QWidget(editor) {
        textEdit = editor;
    }
    QSize sizeHint() const override {
        return {textEdit->lineNumberAreaWidth(), 0};
    }

protected:
    void paintEvent(QPaintEvent *event) override {
        textEdit->lineNumberAreaPaintEvent(event);
    }

private:
    MyTextEdit *textEdit;
};

class ButtonArea : public QWidget {

    Q_OBJECT

public:
    explicit ButtonArea(MyTextEdit *editor) : QWidget(editor) {
        textEdit = editor;
    }
    QSize sizeHint() const override {
        return {textEdit->lineNumberAreaWidth(), 0};
    }

protected:
    void paintEvent(QPaintEvent *event) override {
        textEdit->buttonAreaPaintEvent(event);
    }
    void mousePressEvent(QMouseEvent *event) override {
        textEdit->buttonPressEvent(event);
    }

private:
    MyTextEdit *textEdit;
};
