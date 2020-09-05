#pragma once

#include <QWidget>
#include <QApplication>
#include <QTextEdit>
#include <QPushButton>
#include <QMediaPlayer>
#include <QVideoWidget>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QSlider>
#include <iostream>
#include "widgets/text_edit.h"
#include "parser.h"
#include "renderer.h"
#include "widgets/video.h"
#include <QProgressDialog>
#include <QProgressBar>
#include <QTimer>

class Editor : public QWidget {

    Q_OBJECT

public:
    explicit Editor(QWidget *parent = 0);
    void playPause();
    void updateSlider();
    void syncSlider();

public Q_SLOTS:
    void seek(int seconds);

private slots:
    void Preview();
    void Save();

private:
    QPushButton *playPauseButton;
    QPushButton *previewButton;
    QPushButton *renderButton;
    MyVideoWidget *video;
    MyTextEdit *input;
    QtPlayer *player;
    QSlider *slider;
    Timeline *timeline;
    uint videoLength;
    QTimer *timer;
};
