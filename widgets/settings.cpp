#include "settings.h"

SettingsEditor::SettingsEditor(QWidget *parent) : QWidget(parent) {
    setWindowFlag(Qt::WindowStaysOnTopHint);

    auto *videoSection = new QLabel("Video Options");
    auto *audioSection = new QLabel("Audio Options");
    auto *viewSection = new QLabel("View Options");

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

    auto *videoHardwareBox = new QHBoxLayout();
    auto *videoHardwareLabel = new QLabel("Hardware Acceleration:");
    videoHardwareSelect = new QComboBox();
    auto *model = new QStandardItemModel(this);
    auto *hwNone = new QStandardItem();
    hwNone->setData(tr("Disabled"), Qt::DisplayRole);
    hwNone->setData(0, Qt::UserRole);
    model->setItem(0, hwNone);
    auto *hwVaAPI = new QStandardItem();
    hwVaAPI->setData(tr("Linux VA-API"), Qt::DisplayRole);
    hwVaAPI->setData(1, Qt::UserRole);
    model->setItem(1, hwVaAPI);
    auto *hwNVDEC = new QStandardItem();
    hwNVDEC->setData(tr("nVidia NVDEC"), Qt::DisplayRole);
    hwNVDEC->setData(2, Qt::UserRole);
    model->setItem(2, hwNVDEC);
    auto *hwD9 = new QStandardItem();
    hwD9->setData(tr("Windows D3D9"), Qt::DisplayRole);
    hwD9->setData(3, Qt::UserRole);
    model->setItem(3, hwD9);
    auto *hwD11 = new QStandardItem();
    hwD11->setData(tr("Windows D3D11"), Qt::DisplayRole);
    hwD11->setData(4, Qt::UserRole);
    model->setItem(4, hwD11);
    auto *hwMac = new QStandardItem();
    hwMac->setData(tr("MacOS VideoToolBox"), Qt::DisplayRole);
    hwMac->setData(5, Qt::UserRole);
    model->setItem(5, hwMac);
    auto *hwVDPAU = new QStandardItem();
    hwVDPAU->setData(tr("Linux VDPAU"), Qt::DisplayRole);
    hwVDPAU->setData(6, Qt::UserRole);
    model->setItem(6, hwVDPAU);
    auto *hwQsv = new QStandardItem();
    hwQsv->setData(tr("Intel QSV"), Qt::DisplayRole);
    hwQsv->setData(7, Qt::UserRole);
    model->setItem(7, hwQsv);
    videoHardwareSelect->setModel(model);
    videoHardwareSelect->setCurrentIndex(settings.value("video/hw_acceleration", 0).toInt());
    videoHardwareBox->addWidget(videoHardwareLabel);
    videoHardwareBox->addWidget(videoHardwareSelect);

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

    // VIEW
    auto *previewPositionBox = new QHBoxLayout();
    auto *previewPositionLabel = new QLabel("Preview position:");
    previewPositionSelect = new QComboBox();
    if (settings.value("view/layout") == QString("Left")) {
        previewPositionSelect->addItem("Left", QVariant(QVariant::Type::String));
        previewPositionSelect->addItem("Right", QVariant(QVariant::Type::String));
    } else {
        previewPositionSelect->addItem("Right", QVariant(QVariant::Type::String));
        previewPositionSelect->addItem("Left", QVariant(QVariant::Type::String));
    }
    previewPositionBox->addWidget(previewPositionLabel);
    previewPositionBox->addWidget(previewPositionSelect);

    // END

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
    layout->addLayout(videoHardwareBox);

    layout->addWidget(audioSection);
    layout->addLayout(audioSampleRateBox);
    layout->addLayout(audioCodecBox);

    layout->addWidget(viewSection);
    layout->addLayout(previewPositionBox);

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
    if (videoHardwareSelect->currentData(Qt::UserRole) != settings.value("video/hw_acceleration", 0).toInt()) {
        settings.setValue("video/hw_acceleration", videoHardwareSelect->currentData(Qt::UserRole));
        settings.sync();
        ShowRestartDialog();
    }

    if (!audioSampleRateInput->text().isEmpty()) {
        settings.setValue("audio/sample_rate", audioSampleRateInput->text());
    }
    if (!audioCodecSelect->currentText().isEmpty()) {
        settings.setValue("audio/codec", audioCodecSelect->currentText());
    }

    if (previewPositionSelect->currentText() != settings.value("view/layout", "Left")) {
        cerr << previewPositionSelect->currentText().toStdString() << endl;
        settings.setValue("view/layout", previewPositionSelect->currentText());
        settings.sync();
        ShowRestartDialog();
    }

    close();
}

void SettingsEditor::ShowRestartDialog() {
    QMessageBox dialog(this);
    dialog.setWindowTitle("Settings");
    dialog.setText("You have to restart the app for changes to take effect.");
    dialog.setInformativeText("Restart now?");
    dialog.setStandardButtons(QMessageBox::Cancel | QMessageBox::Ok);
    dialog.setDefaultButton(QMessageBox::Ok);
    int ret = dialog.exec();
    if (ret == QMessageBox::Ok) {
        QApplication::quit();
        QProcess::startDetached(QApplication::arguments()[0], QApplication::arguments());
    }
}
