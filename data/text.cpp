#include "text.h"

#include <utility>

Text::Text(string value, uint size, string font, string color, string position) {
    m_value = std::move(value);
    m_size = size;
    m_font = std::move(font);
    m_color = std::move(color);

    if (boost::iequals(position, "top_left")) {
        m_position = GRAVITY_TOP_LEFT;
    } else if (boost::iequals(position, "top")) {
        m_position = GRAVITY_TOP;
    } else if (boost::iequals(position, "top_right")) {
        m_position = GRAVITY_TOP_RIGHT;
    } else if (boost::iequals(position, "left")) {
        m_position = GRAVITY_LEFT;
    } else if (boost::iequals(position, "right")) {
        m_position = GRAVITY_RIGHT;
    } else if (boost::iequals(position, "bottom_left")) {
        m_position = GRAVITY_BOTTOM_LEFT;
    } else if (boost::iequals(position, "bottom")) {
        m_position = GRAVITY_BOTTOM;
    } else if (boost::iequals(position, "bottom_right")) {
        m_position = GRAVITY_BOTTOM_RIGHT;
    } else {
        m_position = GRAVITY_CENTER;
    }
}

string Text::GetValue() {
    return m_value;
}

uint Text::GetSize() {
    return m_size;
}

string Text::GetFont() {
    return m_font;
}

string Text::GetColor() {
    return m_color;
}

GravityType Text::GetPosition() {
    return m_position;
}
