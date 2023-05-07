#pragma once
#include <SFML/System/Clock.hpp>

class SharedResources
{
private:
    SharedResources() = default;
    ~SharedResources() = default;
public:
    sf::Clock gameClock;

    SharedResources(SharedResources &other) = delete;
    SharedResources& operator=(const SharedResources &) = delete;
    SharedResources(SharedResources &&) = delete;
    SharedResources & operator=(SharedResources &&) = delete;

    static auto& Instance() {
        static SharedResources instance;
        return instance;
    }
};