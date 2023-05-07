#include "coin.hpp"

// Initialize static data
sf::Texture Coin::texture;

Coin::Coin(float x, float y) : Entity(texture)
{
    auto success = texture.loadFromFile("./textures/coinsheet1.png");
    if (success)
    {
        sprite.setTexture(texture, true);
        sprite.setTextureRect(sf::IntRect(
            sf::Vector2i(0, 0),
            sf::Vector2i(Constants::coinPixelWidth, Constants::coinPixelHeight)));
        sprite.setPosition(sf::Vector2f{x, y});
    }
}

void Coin::draw(sf::RenderWindow &window)
{
    window.draw(sprite);
}

void Coin::update()
{
    const int coinSpriteIndexStart = 0;
    const float coinFramesCount = 6.f;
    const float animationSpeed = 1.f;

    // Scale seconds by animationspeed
    float seconds = SharedResources::Instance().gameClock.getElapsedTime().asSeconds() * animationSpeed;

    // Only use fractional part
    float onlyFractionalPart = (seconds - (long)seconds);
    // Animate through number of frames
    int spriteIndex = static_cast<int>(onlyFractionalPart * coinFramesCount);
    int coinSpriteIndex = spriteIndex + coinSpriteIndexStart;

    sprite.setTextureRect(
        sf::IntRect(
            sf::Vector2i((coinSpriteIndex * Constants::coinPixelWidth), 0),
            sf::Vector2i(Constants::coinPixelWidth, Constants::coinPixelHeight))
    );
}
