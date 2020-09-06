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

class SettingsEditor : public QWidget {

    Q_OBJECT

public:
    explicit SettingsEditor(QWidget *parent = nullptr);

private slots:
    void Save();

private:
    QSettings settings;
    QLineEdit *videoWidthInput;
    QLineEdit *videoHeightInput;
    QLineEdit *videoFpsInput;
    QLineEdit *videoBitrateInput;
    QComboBox *videoCodecSelect;
    QLineEdit *audioSampleRateInput;
    QComboBox *audioCodecSelect;
};
