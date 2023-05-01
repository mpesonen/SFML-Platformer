#include "entity.hpp"

sf::Vector2f Entity::getPosition() const noexcept
{
    return sprite.getPosition();
}

sf::FloatRect Entity::getGlobalBounds() const noexcept
{
    return sprite.getGlobalBounds();
}

void Entity::resetCollisionDirections() noexcept
{
    this->collisionDirections = Constants::DIRECTION_NONE;
}

void Entity::setCollisionDirections(unsigned char directions) noexcept
{
    this->collisionDirections |= directions;
}

bool Entity::isCollidingFromRight()
{
    return (this->collisionDirections & Constants::DIRECTION_RIGHT) == Constants::DIRECTION_RIGHT;
}

bool Entity::isCollidingFromBottom()
{
    return (this->collisionDirections & Constants::DIRECTION_BOTTOM) == Constants::DIRECTION_BOTTOM;
}

bool Entity::isCollidingFromLeft()
{
    return (this->collisionDirections & Constants::DIRECTION_LEFT) == Constants::DIRECTION_LEFT;
}

bool Entity::isCollidingFromTop()
{
    return (this->collisionDirections & Constants::DIRECTION_TOP) == Constants::DIRECTION_TOP;
}

float Entity::x() const noexcept
{
    return sprite.getPosition().x;
}

float Entity::y() const noexcept
{
    return sprite.getPosition().y;
}

void Entity::destroy() noexcept
{
    destroyed = true;
}

bool Entity::isDestroyed() const noexcept
{
    return destroyed;
}
