#include "file.h"

using namespace spv;

spv::File::File(string path) {
    m_path = move(path);
}

string spv::File::GetPath() {
    return m_path;
}

spv::File::~File() = default;
