#include "interactions.hpp"
#include "constants.hpp"

// Resolve potential collision between the ball and a brick
void handle_collision(Player& player, Brick& brick) {
    auto collision = player.getGlobalBounds().findIntersection(brick.getGlobalBounds());
  if (collision.has_value()) {
    
    sf::Vector2f collisionCenter {collision->left + (collision->width / 2.f), collision->top + (collision->height / 2.f)};
    sf::Vector2f playerCenter {player.getGlobalBounds().left + (player.getGlobalBounds().width / 2.f), player.getGlobalBounds().top + (player.getGlobalBounds().height / 2.f)};

    float angle = atan2(collisionCenter.y - playerCenter.y, collisionCenter.x - playerCenter.x) * 180.f / M_PI;

    if (angle >= 45.f && angle < 135.f)
    {
      player.setCollisionDirections(Constants::DIRECTION_BOTTOM);
      player.nudgeUp(collision->height);
    }
    else if (angle >= -45.f && angle < 45.f)
    {
      player.setCollisionDirections(Constants::DIRECTION_RIGHT);
      player.nudgeLeft(collision->width);
    }
    else if (angle >= -135.f && angle < -45.f)
    {
      SharedResources::Instance().playBrickSound();
      brick.destroy();
      player.setCollisionDirections(Constants::DIRECTION_TOP);
      player.nudgeDown(collision->height);
    }
    else if (angle >= 135.f || angle < -135.f)
    {
      player.setCollisionDirections(Constants::DIRECTION_LEFT);
      player.nudgeRight(collision->width);
    }
  }
}

void handle_collision(Player& player, Coin& coin) {
    auto collision = player.getGlobalBounds().findIntersection(coin.getGlobalBounds());
  if (collision.has_value()) {
    coin.playCoinSound();
    coin.destroy();
  }
}