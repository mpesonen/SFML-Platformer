#pragma once

#include "entity.hpp"
#include "constants.hpp"

class Player : public MovingEntity
{
private:
  void processInput();
protected:
    static sf::Texture texture;
    static sf::IntRect textureRect;
    sf::Clock walkingClock;
    int direction = 1;
public:
    Player(float x, float y);

    void update() override;
    void draw(sf::RenderWindow& window) override;

    void jump() noexcept override;
    void moveDown() noexcept override;
    void moveLeft() noexcept override;
    void moveRight() noexcept override;

    void nudgeLeft(float amount) noexcept;
    void nudgeRight(float amount) noexcept;
    void nudgeUp(float amount) noexcept;
    void nudgeDown(float amount) noexcept;

    void setJumpingSprite(int direction) noexcept;
    void setWalkingSprite(int direction) noexcept;
    void setStandingSprite(int direction) noexcept;
};
