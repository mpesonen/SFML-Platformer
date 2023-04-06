#pragma once

#include "entity.hpp"
#include "constants.hpp"

class Player : public MovingEntity
{
private:
  void processInput();
protected:
    static sf::Texture texture;
public:
    Player(float x, float y);

    void update() override;
    void draw(sf::RenderWindow& window) override;

    void moveUp() noexcept override;
    void moveDown() noexcept override;
    void moveLeft() noexcept override;
    void moveRight() noexcept override;
};
