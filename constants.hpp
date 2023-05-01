#pragma once

class Constants {
public:
    static constexpr unsigned int frameRate{60};
    static constexpr float playerHorizontalSpeed{10.0f};
    static constexpr unsigned int window_width {1024};
    static constexpr unsigned int window_height {786};
    static constexpr float playerSpeed {12.0f};
    static constexpr float tileDimension {48.f};

    static const unsigned char DIRECTION_NONE = 0;
    static const unsigned char DIRECTION_TOP = 1;
    static const unsigned char DIRECTION_RIGHT = 2;
    static const unsigned char DIRECTION_BOTTOM = 4;
    static const unsigned char DIRECTION_LEFT = 8;
};
