#include <iostream>
#include <random>

#include "Player.h"
#include "GameData.h"
#include "SlotMachine.h"


// This example runs until player is out of money
int main() {
    SlotMachine game;
    Player player(1'000);

    // While the player has money left
    while (player.money) {
        auto [slots, victory, error] = game.Play(player);
        // Player didn't have enough money
        if (error)
            return error;

        // Output slot results
        for (Colour slot : slots) {
            auto colour_code = static_cast<int>(slot);
            std::cout << "Slot : " << slot_mappings.at(colour_code) << '\n';
        }
        
        std::cout << (victory ? "Won!" : "Lost!") << "\n\n";
    }

    return 0;
}
