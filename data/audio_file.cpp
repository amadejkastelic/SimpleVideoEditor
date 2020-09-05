#include "audio_file.h"
#include <utility>

AudioFile::AudioFile(string path, uint start, uint end) : File(std::move(path)) {
    m_start = start;
    m_end = end;
}

uint AudioFile::GetStart() const {
    return m_start;
}

uint AudioFile::GetEnd() const {
    return m_end;
}
