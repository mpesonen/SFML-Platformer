#include "brick.hpp"


// Initialize static data
sf::Texture Brick::texture;

Brick::Brick(float x, float y) : Entity()
{
    // TODO: file operations might be slow
    texture.loadFromFile("./textures/brick01.png");
    sprite.setTexture(texture);
    sprite.setPosition(x, y);
}

void Brick::draw(sf::RenderWindow &window)
{
    window.draw(sprite);
}

void Brick::update()
{
}
