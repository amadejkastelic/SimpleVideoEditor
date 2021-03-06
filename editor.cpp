#include <QtPlayer.h>
#include "editor.h"
#include "widgets/text_edit.h"

using namespace std;

Editor::Editor(QWidget *parent) : QWidget(parent) {
    videoLength = 0;
    cursorLine = 0;
    reader = nullptr;

    colorPicker = new QColorDialog(this);
    connect(colorPicker, &QColorDialog::colorSelected, this, &Editor::ColorSelected);

    fontPicker = new QFontDialog(this);
    connect(fontPicker, &QFontDialog::fontSelected, this, &Editor::FontSelected);

    filePicker = new QFileDialog(this);
    connect(filePicker, &QFileDialog::fileSelected, this, &Editor::FileSelected);

    //playPauseButton = new QPushButton(QIcon("../icons/pause.png"), "", this);
    previewButton = new QPushButton("Preview", this);
    renderButton = new QPushButton("Save", this);
    input = new MyTextEdit(this);

    variableCompleter = new QCompleter(Lists::variables(), input);
    variableCompleter->setWidget(input);
    variableCompleter->setCompletionMode(QCompleter::PopupCompletion);
    variableCompleter->setCaseSensitivity(Qt::CaseSensitive);
    connect(variableCompleter, QOverload<const QString &>::of(&QCompleter::activated), input,
            &MyTextEdit::insertCompletion);

    typeCompleter = new QCompleter(Lists::type(), input);
    typeCompleter->setWidget(input);
    typeCompleter->setCompletionMode(QCompleter::PopupCompletion);
    typeCompleter->setCaseSensitivity(Qt::CaseInsensitive);
    connect(typeCompleter, QOverload<const QString &>::of(&QCompleter::activated), input,
            &MyTextEdit::insertCompletion);

    scaleCompleter = new QCompleter(Lists::scale(), input);
    scaleCompleter->setWidget(input);
    scaleCompleter->setCompletionMode(QCompleter::PopupCompletion);
    scaleCompleter->setCaseSensitivity(Qt::CaseInsensitive);
    connect(scaleCompleter, QOverload<const QString &>::of(&QCompleter::activated), input,
            &MyTextEdit::insertCompletion);

    positionCompleter = new QCompleter(Lists::position(), input);
    positionCompleter->setWidget(input);
    positionCompleter->setCompletionMode(QCompleter::PopupCompletion);
    positionCompleter->setCaseSensitivity(Qt::CaseInsensitive);
    connect(positionCompleter, QOverload<const QString &>::of(&QCompleter::activated), input,
            &MyTextEdit::insertCompletion);

    renderButton->setEnabled(false);

    video = new MyVideoWidget(this);
    video->setMinimumSize(400, 150);
    player = new QtPlayer(video->GetRenderer());
    video->SetPlayer(player);
    player->SetQWidget(reinterpret_cast<uintptr_t>(video));
    player->Volume(50);
    //player->Loading();

    //playPauseButton->setMaximumWidth(30);
    //playPauseButton->setEnabled(false);

    slider = new QSlider(Qt::Orientation::Horizontal, this);
    slider->setEnabled(false);

    previewGrid = new QGridLayout();
    previewGrid->addWidget(video);
    //previewGrid->addWidget(playPauseButton);
    previewGrid->addWidget(slider);

    //InitVideoPreviewWidget();

    auto *inputGrid = new QGridLayout();
    inputGrid->addWidget(input);
    inputGrid->addWidget(previewButton);
    inputGrid->addWidget(renderButton);

    auto *layout = new QHBoxLayout();
    layout->setMenuBar(buildMenuBar(this));
    if (settings.value("view/layout", "Left") == QString("Left")) {
        layout->addLayout(previewGrid);
        layout->addLayout(inputGrid);
    } else if (settings.value("view/layout", "Left") == QString("Detached")) {
        layout->addLayout(inputGrid);
        previewWidget = new PreviewWidget(this, previewGrid);
        previewWidget->show();
    } else {
        layout->addLayout(inputGrid);
        layout->addLayout(previewGrid);
    }


    setLayout(layout);
    setWindowFlag(Qt::Window);

    timeline = new Timeline(
            settings.value("video/width", 1920).toInt(),
            settings.value("video/height", 1080).toInt(),
            Fraction(settings.value("video/fps", 24).toInt(), 1),
            settings.value("audio/sample_rate", 44100).toInt(),
            2,
            ChannelLayout::LAYOUT_STEREO);
    timeline->SetCache(new CacheMemory(settings.value("timeline/cache_size", 0).toInt()));

    cerr << "Width: " << settings.value("video/width", 1920).toInt() << endl;
    cerr << "Height: " << settings.value("video/height", 1080).toInt() << endl;

    highlighter = new Highlighter(input->document());

    connect(previewButton, &QPushButton::clicked, this, &Editor::Preview);
    connect(renderButton, SIGNAL(clicked()), this, SLOT(Save()));
    //connect(playPauseButton, &QPushButton::clicked, this, &Editor::playPause);
    connect(slider, &QSlider::sliderMoved, this, &Editor::seek);
    connect(slider, &QSlider::sliderPressed, this, &Editor::syncSlider);
    connect(input, &MyTextEdit::cursorPositionChanged, this, &Editor::OnCursor);
}

void Editor::seek(int seconds) {
    player->Seek(seconds * settings.value("video/fps", 24).toInt());
}

void Editor::PreviewFile(string *path) {
    InitVideoPreviewWidget();
    if (reader != nullptr && reader->IsOpen()) {
        timer->stop();
        player->Stop();
        reader->Close();
    }

    if (timeline->IsOpen()) {
        timeline->Close();
        player->Stop();
        timer->stop();

        timeline = new Timeline(
                settings.value("video/width", 1920).toInt(),
                settings.value("video/height", 1080).toInt(),
                Fraction(settings.value("video/fps", 24).toInt(), 1),
                settings.value("audio/sample_rate", 44100).toInt(),
                2,
                ChannelLayout::LAYOUT_STEREO);
        timeline->SetCache(new CacheMemory(
                settings.value("timeline/cache_size", 0).toInt()));
    }

    timeline->AddClip(new Clip(*path));

    previewButton->setEnabled(false);

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

    slider->setRange(0, timeline->Clips().front()->Duration());
    slider->setEnabled(true);
    slider->setSliderPosition(0);

    previewButton->setEnabled(true);
}

void Editor::Preview() {
    if (input->toPlainText().length() == 0) {
        return;
    }

    InitVideoPreviewWidget();
    if (reader != nullptr && reader->IsOpen()) {
        timer->stop();
        player->Stop();
        reader->Close();
    }

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
        timeline->SetCache(new CacheMemory(
                settings.value("timeline/cache_size", 0).toInt()));
    }

    vector<spv::File*> files;
    QProgressDialog progressDialog("", "", 0, 0, this);
    progressDialog.setCancelButton(nullptr);
    progressDialog.setValue(0);
    progressDialog.setWindowTitle("Rendering...");
    progressDialog.setWindowModality(Qt::WindowModal);

    try {
        files = Parser::ParseYaml(input->toPlainText().toStdString());
        videoLength = Renderer::render(files, timeline);
        progressDialog.cancel();
    } catch (...) {
        progressDialog.cancel();
        return;
    }

    if (videoLength == 0) {
        QErrorMessage dialog(this);
        dialog.setWindowTitle("Error");
        dialog.showMessage("Parsing error...");
        dialog.exec();
        return;
    }

    previewButton->setEnabled(false);
    renderButton->setEnabled(true);

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

    FFmpegWriter writer("output.mp4");
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

QMenuBar* Editor::buildMenuBar(QWidget *parent) const {
    auto *menuBar = new QMenuBar(parent);
    menuBar->setNativeMenuBar(true);

    auto *fileMenu = new QMenu("File");
    auto *settingsAction = new QAction("Settings");
    connect(settingsAction, &QAction::triggered, this, &Editor::OpenSettings);
    fileMenu->addAction(settingsAction);

    menuBar->addMenu(fileMenu);

    if (settings.value("view/layout", "Left") == QString("Detached")) {
        auto *viewMenu = new QMenu("View");
        auto *previewAction = new QAction("Show Preview");
        connect(previewAction, &QAction::triggered, this, &Editor::OpenPreviewWindow);
        viewMenu->addAction(previewAction);
        menuBar->addMenu(viewMenu);
    }

    return menuBar;
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

void Editor::OnCursor() {
    QTextCursor cursor = input->textCursor();
    QString line = cursor.block().text().trimmed();

    if (!line.contains(":")) {
        if (input->completer() != variableCompleter) {
            input->setCompleter(variableCompleter);
        }
    } else if (line.contains("position:")) {
        if (input->completer() != positionCompleter) {
            input->setCompleter(positionCompleter);
        }
    } else if (line.contains("type:")) {
        if (input->completer() != typeCompleter) {
            input->setCompleter(typeCompleter);
        }
    } else if (line.contains("scale:")) {
        if (input->completer() != scaleCompleter) {
            input->setCompleter(scaleCompleter);
        }
    /*} else if (line.contains("path:")) {
        if (input->completer() != pathCompleter) {
            input->setCompleter(pathCompleter);
        }*/
    } else {
        if (input->completer() != nullptr) {
            input->setCompleter(nullptr);
        }
    }

    cursorLine = cursor.blockNumber();
}

void Editor::SideButtonClick(int lineNumber) {
    InitVideoPreviewWidget();

    // move cursor to line
    QTextCursor cursor(input->document()->findBlockByLineNumber(lineNumber - 1));
    input->setTextCursor(cursor);

    QString line = cursor.block().text().trimmed();
    if (line.contains("path:")) {
        //input->setCompleter(nullptr);

        /*if (filePicker != nullptr && filePicker->isVisible()) {
            return;
        }

        cerr << line.toStdString() << " " << line.split(":").length() << endl;
        if ((line.split(":").size() > 1 && line.split(":")[1].isEmpty())
                || cursorLine != cursor.blockNumber()) {
            filePicker->open();
        }*/
        /*if (input->completer() != path_completer) {
            input->setCompleter(path_completer);
        }

        if (cursorLine == cursor.blockNumber() && reader != nullptr && reader->IsOpen()) {
            return;
        }*/

        string path = Parser::getString(line.split(":")[1].trimmed().toStdString(),
                                        input->toPlainText().toStdString());
        cerr << "Path: " << path << endl;
        if (!fopen(path.c_str(), "r")) {
            cerr << "File doesn't exist." << endl;
            return;
        }

        try {
            this->PreviewFile(&path);
        } catch (...) {
            return;
        }
    } else if (line.contains("font:")) {
        /*if (input->completer() != font_completer) {
            input->setCompleter(font_completer);
        }*/
        input->setCompleter(nullptr);
        if (fontPicker != nullptr && fontPicker->isVisible()) {
            return;
        }

        fontPicker->open();
    } else if (line.contains("color:")) {
        input->setCompleter(nullptr);
        if (colorPicker != nullptr && colorPicker->isVisible()) {
            return;
        }

        colorPicker->open();
    } else if (line.contains(QChar::ObjectReplacementCharacter)) {
        cerr << "Unfolding..." << endl;
        input->unfold();
    } else if (line.contains("part:") || line.contains("variables:")) {
        cerr << "Folding..." << endl;
        input->fold();
    } else {
        input->setCompleter(nullptr);
    }

    cursorLine = cursor.blockNumber();
}

void Editor::ColorSelected() {
    input->moveCursor(QTextCursor::MoveOperation::EndOfLine);
    QTextCursor cursor = input->textCursor();
    QString line = cursor.block().text().trimmed();
    cerr << line.toStdString() << endl;
    while (line.contains(":")) {
        cursor.deletePreviousChar();
        line = cursor.block().text().trimmed();
    }
    input->insertPlainText(": " + colorPicker->selectedColor().name(QColor::NameFormat::HexArgb).toUpper().mid(1));
}

void Editor::FontSelected() {
    input->moveCursor(QTextCursor::MoveOperation::EndOfLine);
    QTextCursor cursor = input->textCursor();
    QString line = cursor.block().text().trimmed();
    cerr << line.toStdString() << endl;
    while (line.contains(":")) {
        cursor.deletePreviousChar();
        line = cursor.block().text().trimmed();
    }
    input->insertPlainText(": " + fontPicker->selectedFont().family());
}

void Editor::FileSelected() {
    input->moveCursor(QTextCursor::MoveOperation::EndOfLine);
    QTextCursor cursor = input->textCursor();
    QString line = cursor.block().text().trimmed();
    cerr << line.toStdString() << endl;
    while (line.contains(":")) {
        cursor.deletePreviousChar();
        line = cursor.block().text().trimmed();
    }
    input->insertPlainText(": " + filePicker->selectedFiles()[0]);
}

void Editor::InitVideoPreviewWidget() {
    if (video != nullptr) {
        return;
    }
    video = new MyVideoWidget(this);
    video->setMinimumSize(400, 150);
    player = new QtPlayer(video->GetRenderer());
    video->SetPlayer(player);
    player->SetQWidget(reinterpret_cast<uintptr_t>(video));
    player->Volume(50);
    player->Loading();

    previewGrid->addWidget(video);
    //previewGrid->addWidget(playPauseButton);
    previewGrid->addWidget(slider);
}

void Editor::OpenPreviewWindow() {
    previewWidget->show();
}
