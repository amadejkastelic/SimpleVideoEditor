#pragma once

#include "file.h"
#include "audio_file.h"

using namespace spv;

class ImageFile : public spv::File {

private:
    uint m_length;
    AudioFile *m_audio;
    vector<Text *> m_text;
    ScaleType m_scale;
    string m_animation;

public:
    ImageFile(string path, uint length, AudioFile *audio = nullptr, vector<Text *> text = vector<Text *>(), ScaleType scale = SCALE_NONE, string animation = "");
    uint GetLength() const;
    AudioFile* GetAudioFile();
    vector<Text *> GetText();
    ScaleType GetScale();
    string GetAnimation();
};
