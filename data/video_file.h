#pragma once

#include <vector>
#include "file.h"
#include "audio_file.h"

using namespace spv;

class VideoFile : public spv::File {

private:
    uint m_start;
    uint m_end;
    AudioFile *m_audio;
    vector<Text *> m_text;

public:
    VideoFile(string path, uint start, uint end, AudioFile *audio = nullptr, vector<Text *> text = vector<Text *>());
    uint GetStart() const;
    uint GetEnd() const;
    AudioFile* GetAudioFile();
    vector<Text *> GetText();
};
