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
    // Random generation
    std::mt19937_64 generator;
    std::random_device rd;
    std::uniform_int_distribution<> dist;

    void SeedRandom();
public:
    // Jackpot of this machine
    std::int64_t jackpot{};

    SlotMachine();
    explicit SlotMachine(const std::int64_t& jackpot);

    /**
     * \brief Play a game of the SlotMachine
     *
     * Side-effect: Will deduct supplied player's money and add it to the jackpot
     *
     * Side-effect: May empty the jackpot if the player wins
     * \param player Player that is to play the game
     * \return Result of a single game
     *  
     */
    GameResult Play(Player& player);
};
