#pragma once

#include "text.h"

using namespace std;

namespace spv {

    class File {

    private:
        string m_path;

    public:
        explicit File(string path);
        string GetPath();
        virtual ~File();
    };

}