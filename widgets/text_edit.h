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

class MyTextEdit : public QPlainTextEdit {

    Q_OBJECT

private:
    void setFont();
    QString textUnderCursor() const;
    QCompleter *m_completer = nullptr;
    QFile *m_workspace;

public:
    explicit MyTextEdit(const QString &text, QWidget *parent = nullptr);
    void setCompleter(QCompleter *completer);
    QCompleter *completer() const;

public slots:
    void insertCompletion(const QString &completion);

protected:
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;
    void focusInEvent(QFocusEvent *event) override;
};
