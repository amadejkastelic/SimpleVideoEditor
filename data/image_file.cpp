#include "image_file.h"
#include <utility>

ImageFile::ImageFile(string path, uint length, AudioFile *audio, vector<Text *> text, ScaleType scale, string animation) : File(std::move(path)) {
    m_length = length;
    m_audio = audio;
    m_text = std::move(text);
    m_scale = scale;
    m_animation = std::move(animation);
}

uint ImageFile::GetLength() const {
    return m_length;
}

AudioFile *ImageFile::GetAudioFile() {
    return m_audio;
}

vector<Text *> ImageFile::GetText() {
    return m_text;
}

string ImageFile::GetAnimation() {
    return m_animation;
}

ScaleType ImageFile::GetScale() {
    return m_scale;
}
