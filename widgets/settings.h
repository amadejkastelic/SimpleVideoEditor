#pragma once

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QIntValidator>
#include <QLabel>
#include <QSettings>
#include <QPushButton>
#include <QComboBox>
#include <QApplication>
#include <QProcess>
#include <QMessageBox>
#include <QStandardItem>
#include <iostream>

using namespace std;

class SettingsEditor : public QWidget {

    Q_OBJECT

public:
    explicit SettingsEditor(QWidget *parent = nullptr);

private slots:
    void Save();

private:
    void ShowRestartDialog();

private:
    QSettings settings;
    QLineEdit *videoWidthInput;
    QLineEdit *videoHeightInput;
    QLineEdit *videoFpsInput;
    QLineEdit *videoBitrateInput;
    QComboBox *videoCodecSelect;
    QComboBox *videoHardwareSelect;
    QLineEdit *audioSampleRateInput;
    QComboBox *audioCodecSelect;
    QComboBox *previewPositionSelect;
};
