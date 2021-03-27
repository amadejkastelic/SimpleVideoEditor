#pragma once

#include <QWidget>
#include <QLayout>

using namespace std;

class PreviewWidget : public QWidget {

Q_OBJECT

public:
    explicit PreviewWidget(QWidget *parent = nullptr, QLayout *layout = nullptr);
};
