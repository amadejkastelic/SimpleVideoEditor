#include "settings.h"

SettingsEditor::SettingsEditor(QWidget *parent) : QWidget(parent) {
    setWindowFlag(Qt::WindowStaysOnTopHint);

    auto *videoSection = new QLabel("Video Options");
    auto *audioSection = new QLabel("Audio Options");

    // VIDEO

    auto *videoWidthBox = new QHBoxLayout();
    auto *videoWidthLabel = new QLabel("Width:");
    videoWidthInput = new QLineEdit();
    videoWidthInput->setValidator(new QIntValidator(1, 10000));
    videoWidthInput->setText(settings.value("video/width", 1920).toString());
    videoWidthBox->addWidget(videoWidthLabel);
    videoWidthBox->addWidget(videoWidthInput);

    auto *videoHeightBox = new QHBoxLayout();
    auto *videoHeightLabel = new QLabel("Height:");
    videoHeightInput = new QLineEdit();
    videoHeightInput->setText(settings.value("video/height", 1080).toString());
    videoHeightInput->setValidator(new QIntValidator(1, 10000));
    videoHeightBox->addWidget(videoHeightLabel);
    videoHeightBox->addWidget(videoHeightInput);

    auto *videoFpsBox = new QHBoxLayout();
    auto *videoFpsLabel = new QLabel("FPS:");
    videoFpsInput = new QLineEdit();
    videoFpsInput->setText(settings.value("video/fps", 24).toString());
    videoFpsInput->setValidator(new QIntValidator(1, 1000));
    videoFpsBox->addWidget(videoFpsLabel);
    videoFpsBox->addWidget(videoFpsInput);

    auto *videoBitrateBox = new QHBoxLayout();
    auto *videoBitrateLabel = new QLabel("Bitrate:");
    videoBitrateInput = new QLineEdit();
    videoBitrateInput->setText(settings.value("video/bitrate", 24).toString());
    videoBitrateInput->setValidator(new QIntValidator(1, 1000000));
    videoBitrateBox->addWidget(videoBitrateLabel);
    videoBitrateBox->addWidget(videoBitrateInput);

    auto *videoCodecBox = new QHBoxLayout();
    auto *videoCodecLabel = new QLabel("Codec:");
    videoCodecSelect = new QComboBox();
    videoCodecSelect->addItem("mpeg4", QVariant(QVariant::Type::String));
    videoCodecBox->addWidget(videoCodecLabel);
    videoCodecBox->addWidget(videoCodecSelect);

    // AUDIO

    auto *audioSampleRateBox = new QHBoxLayout();
    auto *audioSampleRateLabel = new QLabel("Sample rate:");
    audioSampleRateInput = new QLineEdit();
    audioSampleRateInput->setValidator(new QIntValidator(1, 1000000));
    audioSampleRateInput->setText(settings.value("audio/sample_rate", 44100).toString());
    audioSampleRateBox->addWidget(audioSampleRateLabel);
    audioSampleRateBox->addWidget(audioSampleRateInput);

    auto *audioCodecBox = new QHBoxLayout();
    auto *audioCodecLabel = new QLabel("Codec:");
    audioCodecSelect = new QComboBox();
    audioCodecSelect->addItem("libvorbis", QVariant(QVariant::Type::String));
    audioCodecBox->addWidget(audioCodecLabel);
    audioCodecBox->addWidget(audioCodecSelect);

    auto *saveButton = new QPushButton("Save");
    connect(saveButton, &QPushButton::clicked, this, &SettingsEditor::Save);

    auto *layout = new QVBoxLayout(this);
    layout->setSpacing(0);

    layout->addWidget(videoSection);
    layout->addLayout(videoWidthBox);
    layout->addLayout(videoHeightBox);
    layout->addLayout(videoFpsBox);
    layout->addLayout(videoBitrateBox);
    layout->addLayout(videoCodecBox);

    layout->addWidget(audioSection);
    layout->addLayout(audioSampleRateBox);
    layout->addLayout(audioCodecBox);

    layout->addSpacing(10);
    layout->addWidget(saveButton);

    setLayout(layout);
}

void SettingsEditor::Save() {
    if (!videoWidthInput->text().isEmpty()) {
        settings.setValue("video/width", videoWidthInput->text());
    }
    if (!videoHeightInput->text().isEmpty()) {
        settings.setValue("video/height", videoHeightInput->text());
    }
    if (!videoBitrateInput->text().isEmpty()) {
        settings.setValue("video/bitrate", videoBitrateInput->text());
    }
    if (!videoFpsInput->text().isEmpty()) {
        settings.setValue("video/fps", videoFpsInput->text());
    }
    if (!videoCodecSelect->currentText().isEmpty()) {
        settings.setValue("video/codec", videoCodecSelect->currentText());
    }

    if (!audioSampleRateInput->text().isEmpty()) {
        settings.setValue("audio/sample_rate", audioSampleRateInput->text());
    }
    if (!audioCodecSelect->currentText().isEmpty()) {
        settings.setValue("audio/codec", audioCodecSelect->currentText());
    }

    close();
}
