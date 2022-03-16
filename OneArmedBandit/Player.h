#pragma once

#include <cstdint> // int64_t


/**
 * \brief Represents a player of the slot machine game
 */
class Player {
public:
    std::int64_t money;
    /**
     * \brief Create a blank player with no money
     */
    Player();
    
    /**
     * \brief Create player with supplied amount of money
     * \param money Amount of money available for the player to spend in the slot machine game
     */
    explicit Player(int money);
};
