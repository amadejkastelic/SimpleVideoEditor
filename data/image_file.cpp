#include "image_file.h"
#include <utility>

ImageFile::ImageFile(string path, uint length, AudioFile *audio, vector<Text *> text) : File(std::move(path)) {
    m_length = length;
    m_audio = audio;
    m_text = std::move(text);
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
