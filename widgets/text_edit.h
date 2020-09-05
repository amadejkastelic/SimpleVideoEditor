#pragma once

#include <cmath>
#include <QTextEdit>
#include <QFont>
#include <QKeyEvent>

class MyTextEdit : public QTextEdit {

    Q_OBJECT

private:
    void setFont();

public:
    explicit MyTextEdit(const QString &text, QWidget *parent = nullptr);
    void keyPressEvent(QKeyEvent *event) override;
};
