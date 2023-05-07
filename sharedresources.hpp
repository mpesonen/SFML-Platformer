#pragma once
#include <SFML/System/Clock.hpp>
#include <SFML/Audio.hpp>

class SharedResources
{
private:
    static sf::SoundBuffer coinBuffer;
    sf::Sound coinSound;

    static sf::SoundBuffer jumpBuffer;
    sf::Sound jumpSound;

    static sf::SoundBuffer brickBuffer;
    sf::Sound brickSound;

    SharedResources();
    ~SharedResources() = default;
public:
    sf::Clock gameClock;

    SharedResources(SharedResources &other) = delete;
    SharedResources& operator=(const SharedResources &) = delete;
    SharedResources(SharedResources &&) = delete;
    SharedResources & operator=(SharedResources &&) = delete;

    static SharedResources& Instance() {
        static SharedResources instance;
        return instance;
    }

    void playCoinSound() noexcept;
    void playJumpSound() noexcept;
    void playBrickSound() noexcept;
};