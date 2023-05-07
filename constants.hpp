#pragma once

class Constants {
public:
    static constexpr unsigned int frameRate{60};
    static constexpr unsigned int window_width {1024};
    static constexpr unsigned int window_height {786};

    static constexpr float tileDimension {48.f};

    static constexpr float playerHorizontalSpeed{10.0f};
    static const int playerPixelSize = 72;
    static constexpr float playerSpeed {12.0f};
    static const int coinPixelWidth = 39;
    static const int coinPixelHeight = 32;

    // Bitmask for directions. Allows multiple collision directions.
    static const unsigned char DIRECTION_NONE = 0;
    static const unsigned char DIRECTION_TOP = 1;
    static const unsigned char DIRECTION_RIGHT = 2;
    static const unsigned char DIRECTION_BOTTOM = 4;
    static const unsigned char DIRECTION_LEFT = 8;

    static const int TILE_NONE = 0;
    static const int TILE_PLAYER = 1;
    static const int TILE_BRICK = 2;
    static const int TILE_BOX = 3;
    static const int TILE_COIN = 4;
};
