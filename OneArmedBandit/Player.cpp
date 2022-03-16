#include <iostream>

#include "Player.h"


Player::Player() : money(0) {
    std::cout << "New player create that has $" << money << " to spend" << '\n';
}

Player::Player(const int money) : money(money) {
    std::cout << "New player create that has $" << money << " to spend" << '\n';
}
