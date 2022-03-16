// Disable random security warning:
// ReSharper disable CppClangTidyCertMsc51Cpp
#include <iostream>
#include <random>

#include "SlotMachine.h"
#include "GameData.h"
#include "Player.h"


// Seeds the Pseudo-Random Number Generator
void SlotMachine::SeedRandom() {
    // Initialise & seed random generator
    generator = std::mt19937_64{ rd() };
    dist = std::uniform_int_distribution<>(0, 3);
}


// Create a SlotMachine with a default jackpot of 1'000
SlotMachine::SlotMachine() : jackpot(1'000) {
    SeedRandom();
}


// Create a SlotMachine with supplied jackpot amount
SlotMachine::SlotMachine(const std::int64_t& jackpot) : jackpot(jackpot) {
    SeedRandom();
}


// Runs a single game of the SlotMachine
GameResult SlotMachine::Play(Player& player) {
    GameResult result{};

    // Check that the player has enough to play
    if (player.money < COST_TO_PLAY) {
        std::cout << "Not enough money to play!" << '\n';
        result.error = true;
        return result;
    }

    // Decrease player money, increase jackpot
    player.money -= COST_TO_PLAY;
    jackpot += COST_TO_PLAY;
    std::cout << "Jackpot: " << jackpot << " Rolling...\n";

    // Fill each slot with a random colour
    for (Colour& slot : result.slots) {
        // Generates a random result for the slot
        slot = static_cast<Colour>(dist(generator));

        // If the first slot is not the same as the rest, player didn't win
        // Doing it this way saves needing to loop again after the game finishes
        const Colour first_slot = result.slots[0];
        if (slot != first_slot) {
            result.victory = false;
            return result;
        }
    }

    // The player won, as the first slot was always the same as the following slots 
    player.money += jackpot;
    jackpot = 0;

    result.victory = true;
    return result;
}
