#pragma once

#include "file.h"

using namespace spv;

class AudioFile : public spv::File {

private:
    uint m_start;
    uint m_end;

public:
    AudioFile(string path, uint start, uint end);
    uint GetStart() const;
    uint GetEnd() const;
};
