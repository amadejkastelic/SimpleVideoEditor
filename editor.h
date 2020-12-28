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
#include <QFontDialog>
#include <QFileDialog>
#include <QSlider>
#include <iostream>
#include <fstream>
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
#include "widgets/highlighter.h"
#include <QErrorMessage>
#include <QtConcurrent/QtConcurrent>
#include "utils/lists.h"

class MyTextEdit;

class Editor : public QWidget {

Q_OBJECT

public:
    explicit Editor(QWidget *parent = nullptr);
    void playPause();
    void updateSlider();
    void syncSlider();
    QMenuBar* buildMenuBar(QWidget *parent = nullptr) const;
    void SideButtonClick(int lineNumber);

public Q_SLOTS:
    void seek(int seconds);

private slots:
    void Preview();
    void PreviewFile(string *path);
    void Save();
    void OpenSettings();
    void ColorSelected();
    void FontSelected();
    void FileSelected();
    void InitVideoPreviewWidget();
    void OnCursor();

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
    QCompleter *variableCompleter;
    QCompleter *scaleCompleter;
    QCompleter *positionCompleter;
    QCompleter *typeCompleter;
    QCompleter *pathCompleter;
    QColorDialog *colorPicker;
    QFontDialog *fontPicker;
    QFileDialog *filePicker;
    QGridLayout *previewGrid;
    Highlighter *highlighter;
};
