#pragma once

#include <QWidget>
#include <QPaintEvent>
#include <QImage>
#include "Fraction.h"
#include "video_renderer.h"


class VideoRenderWidget : public QWidget {

    Q_OBJECT

private:
    VideoRenderer *renderer;
    QImage image;
    openshot::Fraction aspect_ratio;
    openshot::Fraction pixel_ratio;

public:
    explicit VideoRenderWidget(QWidget *parent = nullptr);
    ~VideoRenderWidget() override;

    VideoRenderer *GetRenderer() const;
    void SetAspectRatio(openshot::Fraction new_aspect_ratio, openshot::Fraction new_pixel_ratio);

protected:
    void paintEvent(QPaintEvent *event) override;

    QRect centeredViewport(int width, int height);

private slots:
    void present(const QImage &image);

};