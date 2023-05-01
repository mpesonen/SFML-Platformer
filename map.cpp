#include "map.hpp"
#include <iostream>

using json = nlohmann::json;

Map::Map(std::string path) {
    std::ifstream ifs(path);
    auto mapJson = json::parse(ifs);

    auto dataVector = mapJson["layers"][0]["data"].get<std::vector<int>>();
    height = mapJson["layers"][0]["height"].get<int>();
    width = mapJson["layers"][0]["width"].get<int>();

    for (int idxH = 0; idxH < height; idxH++)
    {
        for (int idxW = 0; idxW < width; idxW++)
        {
            int unWrapped = idxH * width + idxW;
            if (unWrapped != 0)
            {
                this->mapTiles.insert({std::make_tuple(idxW, idxH), dataVector[unWrapped]});
            }
        }
    }
}

int Map::getWidth()
{
    return this->width;
}

int Map::getHeight()
{
    return this->height;
}

int Map::getTileAt(int x, int y)
{
    return this->mapTiles[std::make_tuple(x, y)];
}

std::map<std::tuple<int, int>, int> Map::getMapTiles()
{
    return this->mapTiles;
};