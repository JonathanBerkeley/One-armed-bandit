#pragma once

#include <string>
#include <unordered_map>


// The cost to play the slot machine game
constexpr int COST_TO_PLAY = 5;
// Determines if networked API should be used for I/O or console
constexpr bool USE_API = true;

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
 * \brief Maps colour codes to string representations
 */
const static std::unordered_map<Colour, std::string> slot_mappings{
    {Colour::black, "Black"},
    {Colour::white, "White"},
    {Colour::green, "Green"},
    {Colour::yellow, "Yellow"}
};

/**
 * \brief Holds the result of one game
 */
struct GameResult {
    Colour slots[4]{};
    bool victory = true;
    bool error = false;
};
