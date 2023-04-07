#include "player.hpp"

// Initialize static data
sf::Texture Player::texture;

Player::Player(float x, float y) : MovingEntity() {
    // TODO: file operations might be slow
    auto success = texture.loadFromFile("./textures/mario1.png");
    if  (success)
    {
        sprite.setTexture(texture);
        sprite.setPosition(sf::Vector2f{x, y});
    }
}

void Player::update()
{
    processInput();

    // Move the position of the player
    sprite.move(velocity);
}

void Player::draw(sf::RenderWindow& window)
{
    window.draw(sprite);
}

void Player::moveUp() noexcept
{
}

void Player::moveDown() noexcept
{
}

void Player::moveLeft() noexcept
{
    velocity.x = -constants::playerSpeed;
}

void Player::moveRight() noexcept
{
    velocity.x = constants::playerSpeed;
}

void Player::processInput()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
    {
        if (x() >=0)
        {
            moveLeft();
        }
        else
            velocity.x = 0;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
    {
        if (x() <= constants::window_width)
        {
            moveRight();
        }
        else
            velocity.x = 0;
    }
    else
        velocity.x = 0;
}
