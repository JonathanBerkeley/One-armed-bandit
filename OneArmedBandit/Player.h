#pragma once

#include <cstdint> // int64_t

/**
 * \brief Represents a player of the slot machine game
 */
class Player {
private:
public:
    std::int64_t money{};
    Player() = default;
    explicit Player(const int money) : money(money) {}
};