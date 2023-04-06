#pragma once

#include "entity.hpp"
#include "constants.hpp"

class Brick : public Entity
{
protected:
    static sf::Texture texture;
public:
    Brick(float x, float y);
    void draw(sf::RenderWindow& window) override;
    void update() override;
};
