#pragma once

#include <iostream>
#include <boost/algorithm/string/predicate.hpp>
#include "libopenshot/OpenShot.h"

using namespace std;
using namespace openshot;

class Text {

private:
    string m_value;
    uint m_size;
    string m_font;
    string m_color;
    GravityType m_position;

public:
    Text(string value, uint size, string font, string color, string position);
    string GetValue();
    uint GetSize();
    string GetFont();
    string GetColor();
    GravityType GetPosition();
};