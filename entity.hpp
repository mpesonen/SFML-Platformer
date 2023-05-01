#pragma once

#include <SFML/Graphics.hpp>
#include "constants.hpp"

class Entity {
protected:
    sf::Sprite sprite;
    bool destroyed{false};
    unsigned char collisionDirections = 0;
public:
    virtual void update() = 0;
    virtual void draw(sf::RenderWindow& window) = 0;

    sf::Vector2f getPosition() const noexcept;
    sf::FloatRect getGlobalBounds() const noexcept;

    void resetCollisionDirections() noexcept;
    void setCollisionDirections(unsigned char directions) noexcept;
    bool isCollidingFromRight();
    bool isCollidingFromBottom();
    bool isCollidingFromLeft();
    bool isCollidingFromTop();

    float x() const noexcept;
    float y() const noexcept;

    void destroy() noexcept;
    bool isDestroyed() const noexcept;

    virtual ~Entity() {}
};

class MovingEntity : public Entity {
protected:
    sf::Vector2f velocity;
public:
    virtual void jump() noexcept = 0;
    virtual void moveDown() noexcept = 0;
    virtual void moveLeft() noexcept = 0;
    virtual void moveRight() noexcept = 0;
};
