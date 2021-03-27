#include "preview_widget.h"

PreviewWidget::PreviewWidget(QWidget *parent, QLayout *layout) {
    setWindowFlag(Qt::Window);
    resize(1280, 720);
    setWindowTitle("Preview");
    setLayout(layout);
}
