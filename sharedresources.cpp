#include "sharedresources.hpp"

sf::SoundBuffer SharedResources::coinBuffer;
sf::SoundBuffer SharedResources::jumpBuffer;

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
}

void SharedResources::playCoinSound() noexcept
{
    coinSound.play();
}

void SharedResources::playJumpSound() noexcept
{
    jumpSound.play();
}