// C++ standard library
#include <iostream>
#include <string>

// Project headers
#include "GameApi.h"
#include "Player.h"
#include "GameData.h"
#include "SlotMachine.h"


// Entry point
int main() {

    // Set the USE_API bool to false to use console I/O instead of networked API
    if constexpr (USE_API) {
        GameApi();
        return 0;
    }

    SlotMachine game;      // Create slot machine
    Player player(1'000);  // Create player with $1,000 to spend

    // While the player has money left
    while (player.money) {

        // Extract results from a game of the slot machine
        auto [slots, victory, out_of_money] = game.Play(player);

        // Player tried to play without having enough money
        if (out_of_money)
            return 0;
        std::cout << "Player has: $" << player.money << " left\n";

        // Output slot results
        for (Colour slot : slots)
            std::cout << "Slot : " << slot_mappings.at(slot) << '\n';

        // Output whether or not the player won
        std::cout << (victory ? "Won!" : "Lost!") << "\n\n";
    }

    return 0;
}
