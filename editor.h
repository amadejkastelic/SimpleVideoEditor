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
#include <fstream>
#include "widgets/text_edit.h"
#include "parser.h"
#include "renderer.h"
#include "widgets/video.h"
#include <QProgressDialog>
#include <QProgressBar>
#include <QTimer>
#include <QSettings>
#include <QTextBlock>
#include <QMenuBar>
#include <QMenu>
#include "widgets/settings.h"

class Editor : public QWidget {

    Q_OBJECT

public:
    explicit Editor(QWidget *parent = nullptr);
    void playPause();
    void updateSlider();
    void syncSlider();
    void buildMenuBar(QWidget *parent);

public Q_SLOTS:
    void seek(int seconds);

private slots:
    void Preview();
    void Save();
    void OpenSettings();
    void PreviewOnCursor();

protected:
    void closeEvent(QCloseEvent *event) override;

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
    QSettings settings;
    uint cursorLine;
    FFmpegReader *reader;
};
