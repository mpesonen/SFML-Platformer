#pragma once

#include "entity.hpp"
#include "constants.hpp"
#include "sharedresources.hpp"
#include <SFML/Audio.hpp>

class Coin : public Entity
{
protected:
    static sf::Texture texture;
public:
    Coin(float x, float y);
    void draw(sf::RenderWindow& window) override;
    void update() override;
    void playCoinSound() noexcept;
};
