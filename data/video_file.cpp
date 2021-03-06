#include "video_file.h"
#include <utility>

VideoFile::VideoFile(string path, uint start, uint end, AudioFile *audio, vector<Text *> text, ScaleType scale): File(std::move(path)) {
    m_start = start;
    m_end = end;
    m_audio = audio;
    m_text = std::move(text);
    m_scale = scale;
}

uint VideoFile::GetStart() const {
    return m_start;
}

uint VideoFile::GetEnd() const {
    return m_end;
}

vector<Text *> VideoFile::GetText() {
    return m_text;
}

AudioFile *VideoFile::GetAudioFile() {
    return m_audio;
}

ScaleType VideoFile::GetScale() {
    return m_scale;
}
