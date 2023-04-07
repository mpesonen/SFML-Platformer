#pragma once

#include <map>
#include <utility>
#include <string>
#include <fstream>
#include <type_traits>
#include <vector>
#include <nlohmann/json.hpp>

class Map {
private:
    std::map<std::tuple<int, int>, int> mapTiles;
    int width;
    int height;
public:
    enum class TileType { empty, player, brick, surprise_box };

    // Enum to e.g. int conversion
    template<typename T>
    constexpr auto to_underlying(T e) noexcept
    {
        return static_cast<std::underlying_type_t<T>>(e);
    }

    Map(std::string path);

    int getWidth();
    int getHeight();
    int getTileAt(int x, int y);
};