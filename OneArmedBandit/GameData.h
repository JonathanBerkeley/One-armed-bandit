#pragma once

#include <string>
#include <unordered_map>

constexpr int COST_TO_PLAY = 5;

/**
 * \brief Possible slot results
 */
enum class Colour : int {
    black = 0,
    white,
    green,
    yellow
};


/**
 * \brief Holds the result of one game
 */
struct GameResult {
    Colour slots[4]{};
    bool victory = true;
    bool error = false;
};


const static std::unordered_map<int, std::string> slot_mappings{
    {0, "Black"},
    {1, "White"},
    {2, "Green"},
    {3, "Yellow"}
};
