#include <QtPlayer.h>
#include "editor.h"

using namespace std;

Editor::Editor(QWidget *parent) : QWidget(parent) {
    videoLength = 0;

    playPauseButton = new QPushButton(QIcon("../icons/pause.png"), "", this);
    previewButton = new QPushButton("Preview", this);
    renderButton = new QPushButton("Save", this);
    input = new MyTextEdit("", this);

    renderButton->setEnabled(false);

    video = new MyVideoWidget(this);
    video->setMinimumSize(400, 150);
    player = new QtPlayer(video->GetRenderer());
    video->SetPlayer(player);
    player->SetQWidget(reinterpret_cast<uintptr_t>(video));
    player->Volume(50);
    //player->Loading();

    playPauseButton->setMaximumWidth(30);
    playPauseButton->setEnabled(false);

    slider = new QSlider(Qt::Orientation::Horizontal, this);
    slider->setEnabled(false);

    auto *previewGrid = new QGridLayout();
    previewGrid->addWidget(video);
    //previewGrid->addWidget(playPauseButton);
    previewGrid->addWidget(slider);

    auto *inputGrid = new QGridLayout();
    inputGrid->addWidget(input);
    inputGrid->addWidget(previewButton);
    inputGrid->addWidget(renderButton);

    auto *layout = new QHBoxLayout(this);
    layout->addLayout(previewGrid);
    layout->addLayout(inputGrid);

    setLayout(layout);
    setWindowFlag(Qt::Window);

    buildMenuBar(this);

    timeline = new Timeline(
            settings.value("video/width", 1920).toInt(),
            settings.value("video/height", 1080).toInt(),
            Fraction(settings.value("video/fps", 24).toInt(), 1),
            settings.value("audio/sample_rate", 44100).toInt(),
            2,
            ChannelLayout::LAYOUT_STEREO);

    cerr << "Width: " << settings.value("video/width", 1920).toInt() << endl;
    cerr << "Height: " << settings.value("video/height", 1080).toInt() << endl;

    connect(previewButton, &QPushButton::clicked, this, &Editor::Preview);
    connect(renderButton, SIGNAL(clicked()), this, SLOT(Save()));
    connect(playPauseButton, &QPushButton::clicked, this, &Editor::playPause);
    connect(slider, &QSlider::sliderMoved, this, &Editor::seek);
    connect(slider, &QSlider::sliderPressed, this, &Editor::syncSlider);
}

void Editor::seek(int seconds) {
    player->Seek(seconds * settings.value("video/fps", 24).toInt());
}

void Editor::Preview() {
    if (timeline->IsOpen()) {
        timeline->Close();
        //timeline->ClearAllCache();
        player->Stop();
        timer->stop();

        timeline = new Timeline(
                settings.value("video/width", 1920).toInt(),
                settings.value("video/height", 1080).toInt(),
                Fraction(settings.value("video/fps", 24).toInt(), 1),
                settings.value("audio/sample_rate", 44100).toInt(),
                2,
                ChannelLayout::LAYOUT_STEREO);
    }

    previewButton->setEnabled(false);
    renderButton->setEnabled(true);
    vector<spv::File*> files = Parser::ParseYaml(input->toPlainText().toStdString());
    videoLength = Renderer::render(files, timeline);
    cerr << "Number of clips in timeline: " << timeline->Clips().size() << endl;
    cerr << "Timeline length (frames): " << timeline->info.video_length << endl;
    cerr << "Timeline length (s): " << timeline->info.duration << endl;
    timeline->Open();

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Editor::updateSlider);

    video->SetTimer(timer);

    player->Reader(timeline);
    player->Loading();
    player->Play();
    timer->start(1000);

    //playPauseButton->setEnabled(true);

    slider->setRange(0, videoLength);
    slider->setEnabled(true);
    slider->setSliderPosition(0);

    previewButton->setEnabled(true);
}

void Editor::playPause() {
    if (player->Mode() == PLAYBACK_PAUSED) {
        playPauseButton->setIcon(QIcon("../icons/pause.png"));
        player->Play();
        timer->start();
    } else if (player->Mode() == PLAYBACK_PLAY) {
        playPauseButton->setIcon(QIcon("../icons/play.png"));
        player->Pause();
        timer->stop();
    }
}

void Editor::Save() {
    auto *dialog = new QProgressDialog(this, Qt::Window);
    dialog->setLabelText("Rendering...");
    dialog->show();

    renderButton->setEnabled(false);
    previewButton->setEnabled(false);

    FFmpegWriter writer("../out/output.mp4");
    writer.SetAudioOptions(
            true,
            settings.value("audio/codec", "libvorbis").toString().toStdString(),
            settings.value("audio/sample_rate", 44100).toInt(),
            2,
            ChannelLayout::LAYOUT_STEREO,
            128000);
    writer.SetVideoOptions(
            true,
            settings.value("video/codec", "mpeg4").toString().toStdString(),
            Fraction(settings.value("video/fps", 24).toInt(), 1),
            settings.value("video/width", 1920).toInt(),
            settings.value("video/height", 1080).toInt(),
            Fraction(1, 1),
            false,
            false,
            settings.value("video/bitrate", 3000000).toInt());

    writer.Open();

    cerr << "Writing frames..." << endl;
    writer.WriteFrame(timeline, 1, videoLength * settings.value("video/fps", 24).toInt());

    writer.Close();
    dialog->close();

    cerr << "Done writing file." << endl;

    renderButton->setEnabled(true);
    previewButton->setEnabled(true);
}

void Editor::updateSlider() {
    if (slider->value() == slider->maximum()) {
        timer->stop();
    }
    slider->setValue(slider->value() + 1);
}

void Editor::syncSlider() {
    player->Seek(slider->value() * settings.value("video/fps", 24).toInt());
}

void Editor::buildMenuBar(QWidget *parent) {
    auto *menuBar = new QMenuBar(parent);
    menuBar->setNativeMenuBar(true);

    auto *fileMenu = new QMenu("File");
    auto *settingsAction = new QAction("Settings");
    connect(settingsAction, &QAction::triggered, this, &Editor::OpenSettings);
    fileMenu->addAction(settingsAction);

    menuBar->addMenu(fileMenu);
}

void Editor::OpenSettings() {
    auto *settingsEditor = new SettingsEditor();
    settingsEditor->resize(400, 300);
    settingsEditor->setWindowTitle("Settings");
    settingsEditor->show();
}

void Editor::closeEvent(QCloseEvent *event) {
    QWidget::closeEvent(event);
    // TODO: maybe save data?
    QCoreApplication::quit();
}
