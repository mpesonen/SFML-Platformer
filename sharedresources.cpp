#include "sharedresources.hpp"

sf::SoundBuffer SharedResources::coinBuffer;
sf::SoundBuffer SharedResources::jumpBuffer;
sf::SoundBuffer SharedResources::brickBuffer;

SharedResources::SharedResources()
{
    if (!coinBuffer.loadFromFile("./audio/smw_coin.wav"))
    {
        return;
    }
    coinSound.setBuffer(coinBuffer);

    if (!jumpBuffer.loadFromFile("./audio/smw_jump.wav"))
    {
        return;
    }
    jumpSound.setBuffer(jumpBuffer);

    if (!brickBuffer.loadFromFile("./audio/brick_break.wav"))
    {
        return;
    }
    brickSound.setBuffer(brickBuffer);
}

void SharedResources::playCoinSound() noexcept
{
    coinSound.play();
}

void SharedResources::playJumpSound() noexcept
{
    jumpSound.play();
}

void SharedResources::playBrickSound() noexcept
{
    brickSound.play();
}