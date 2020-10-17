#pragma once

#include <QApplication>
#include <QWidget>
#include <QTextEdit>
#include <QPushButton>
#include <QMediaPlayer>
#include <QCompleter>
#include <QFileSystemModel>
#include <QVideoWidget>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QColorDialog>
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
#include <QErrorMessage>

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
    void ColorSelected();
    void InitVideoPreviewWidget();

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
    int cursorLine;
    FFmpegReader *reader;
    QCompleter *font_completer;
    QCompleter *path_completer;
    QColorDialog *colorPicker;
    QGridLayout *previewGrid;
};
