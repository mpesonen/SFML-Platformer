#pragma once

#include <SFML/Graphics.hpp>

class Entity {
protected:
    sf::Sprite sprite;
    bool destroyed{false};
public:
    virtual void update() = 0;
    virtual void draw(sf::RenderWindow& window) = 0;

    sf::Vector2f getPosition() const noexcept;

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
    virtual void moveUp() noexcept = 0;
    virtual void moveDown() noexcept = 0;
    virtual void moveLeft() noexcept = 0;
    virtual void moveRight() noexcept = 0;
};
