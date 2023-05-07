#include "brick.hpp"

// Initialize static data
sf::Texture Brick::texture;

Brick::Brick(float x, float y) : Entity(texture)
{
    // TODO: file operations might be slow
    auto success = texture.loadFromFile("./textures/brick01.png");
    if (success)
    {
        sprite.setTexture(texture, true);
        sprite.setPosition(sf::Vector2f{x, y});
    }
}

void Brick::draw(sf::RenderWindow &window)
{
    window.draw(sprite);
}

void Brick::update()
{
}
