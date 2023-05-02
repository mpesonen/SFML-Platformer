#include "player.hpp"

// Initialize static data
sf::Texture Player::texture;
sf::IntRect Player::textureRect;
sf::Clock walkingClock;

static const float jumpPower = 1.9f;
static const float jetPackPower = 0.8f;

Player::Player(float x, float y) : MovingEntity() {
    textureRect = sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(72, 72));
    // TODO: file operations might be slow
    auto success = texture.loadFromFile("./textures/mariosheet.png");
    if (success)
    {
        sprite.setTexture(texture);
        sprite.setTextureRect(textureRect);
        sprite.setPosition(sf::Vector2f{x, y});
    }
}

void Player::update()
{
    float startVelX = velocity.x;

    if (!isCollidingFromBottom())
    {
        velocity.y += 2.f;
    }
    else
    {
        velocity.y = 0.f;
    }
    
    processInput();

    if (velocity.x != 0)
    {
        direction = velocity.x > 0.f ? 1 : -1;
    }

    int width = sprite.getGlobalBounds().width;
    int height = sprite.getGlobalBounds().height;

    // Change sprites
    if (velocity.y < 0)
    {
        setJumpingSprite(direction);
    }
    else
    {
        if (velocity.x == 0)
        {
            setStandingSprite(direction);
        }
        else
        {
            if (startVelX == 0)
            {
                walkingClock.restart();
            }

            setWalkingSprite(direction);
        }
    }

    // Move the position of the player
    sprite.move(velocity);
}

void Player::setJumpingSprite(int direction) noexcept
{
    const int jumpingSpriteIndex = 5;
    int leftOffset = direction == 1 ? 0 : Constants::playerSize;

    sprite.setTextureRect(
        sf::IntRect(
            sf::Vector2i((jumpingSpriteIndex * Constants::playerSize + leftOffset), 0),
            sf::Vector2i(direction * Constants::playerSize, Constants::playerSize))
    );
}

void Player::setStandingSprite(int direction) noexcept
{
    const int standingSpriteIndex = 0;
    int leftOffset = direction == 1 ? 0 : Constants::playerSize;

    sprite.setTextureRect(
        sf::IntRect(
            sf::Vector2i((standingSpriteIndex * Constants::playerSize + leftOffset), 0),
            sf::Vector2i(direction * Constants::playerSize, Constants::playerSize))
    );
}

void Player::setWalkingSprite(int direction) noexcept
{
    const int walkingSpriteIndexStart = 1;
    const float walkingFramesCount = 3.f;
    const float animationSpeed = 3.f;
    int leftOffset = direction == 1 ? 0 : Constants::playerSize;

    // Scale seconds by animationspeed
    float seconds = walkingClock.getElapsedTime().asSeconds() * animationSpeed;

    // Only use fractional part
    float onlyFractionalPart = (seconds - (long)seconds);
    // Walk through number of frames
    int spriteIndex = static_cast<int>(onlyFractionalPart * walkingFramesCount);
    int walkingSpriteIndex = spriteIndex + walkingSpriteIndexStart;

    sprite.setTextureRect(
        sf::IntRect(
            sf::Vector2i((walkingSpriteIndex * Constants::playerSize + leftOffset), 0),
            sf::Vector2i(direction * Constants::playerSize, Constants::playerSize))
    );
}

void Player::draw(sf::RenderWindow& window)
{
    window.draw(sprite);
}

void Player::jump() noexcept
{
    velocity.y += jumpPower * -Constants::playerSpeed;
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
        if (!isCollidingFromTop() && isCollidingFromBottom() && velocity.y == 0 && y() >= 0.f)
        {
            jump();
        }
        else if (velocity.y < 0.f)
        {
            velocity.y += -jetPackPower;
        }
    }
}

void Player::nudgeLeft(float amount) noexcept
{
    sprite.move(sf::Vector2f{-amount, 0});
}

void Player::nudgeRight(float amount) noexcept
{
    sprite.move(sf::Vector2f{amount, 0});
}

void Player::nudgeUp(float amount) noexcept
{
    sprite.move(sf::Vector2f{0, -amount});
}

void Player::nudgeDown(float amount) noexcept
{
    velocity.y = 0.f;
    sprite.move(sf::Vector2f{0, amount});
}
