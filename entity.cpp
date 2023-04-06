#include "entity.hpp"

sf::Vector2f Entity::getPosition() const noexcept
{
    return sprite.getPosition();
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
