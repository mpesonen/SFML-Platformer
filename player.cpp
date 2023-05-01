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
    velocity.y = -Constants::playerSpeed;
}

void Player::moveDown() noexcept
{
    velocity.y = Constants::playerSpeed;
}

void Player::moveLeft() noexcept
{
    velocity.x = -Constants::playerSpeed;
}

void Player::moveRight() noexcept
{
    velocity.x = Constants::playerSpeed;
}

void Player::processInput()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
    {
        if (!isCollidingFromLeft() && x() >=0)
        {
            moveLeft();
        }
        else
            velocity.x = 0;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
    {
        if (!isCollidingFromRight() && x() <= 94.f * Constants::tileDimension)
        {
            moveRight();
        }
        else
            velocity.x = 0;
    }
    else
    {
        velocity.x = 0;
    }
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
    {
        if (!isCollidingFromTop() && y() >= 0.f)
        {
            moveUp();
        }
        else
            velocity.y = 0;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
    {
        if (!isCollidingFromBottom() && y() <= 17.f * Constants::tileDimension)
        {
            moveDown();
        }
        else
            velocity.y = 0;
    }
    else
    {
        velocity.y = 0;
    }
}
