#pragma once

#include "player.hpp"
#include "brick.hpp"
#include "coin.hpp"
#include <cmath>

void handle_collision(Player& player, Brick& brick);
void handle_collision(Player& player, Coin& coin);