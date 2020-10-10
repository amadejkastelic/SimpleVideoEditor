#pragma once

#include "RendererBase.h"
#include <QObject>
#include <QImage>
#include <memory>


class QPainter;

class VideoRenderer : public QObject, public openshot::RendererBase
{
Q_OBJECT

public:
    VideoRenderer(QObject *parent = 0);
    ~VideoRenderer();

    /// Override QWidget which needs to be painted
    void OverrideWidget(int64_t qwidget_address);

signals:
    void present(const QImage &image);

protected:
    //void render(openshot::OSPixelFormat format, int width, int height, int bytesPerLine, unsigned char *data);
    void render(std::shared_ptr<QImage> image);

private slots:

private:
    QWidget* override_widget;
};