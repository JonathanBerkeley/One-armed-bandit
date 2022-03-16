#pragma once
#include <random>

#include "GameData.h"
#include "Player.h"


/**
 * \brief Represents a One Armed Bandit style slot machine with 4 slots and a random chance
 *        at a jackpot
 */
class SlotMachine {
private:
    // Jackpot of this machine
    std::int64_t jackpot{};

    // Random generation
    std::mt19937_64 generator;
    std::random_device rd;
    std::uniform_int_distribution<> dist;

    void SeedRandom();
public:
    SlotMachine();
    explicit SlotMachine(const std::int64_t& jackpot);
    GameResult Play(Player& player);
};
