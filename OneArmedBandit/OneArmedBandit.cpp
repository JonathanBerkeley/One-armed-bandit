// C++ standard library
#include <iostream>
#include <string>

// Project headers
#include "Player.h"
#include "GameData.h"
#include "SlotMachine.h"

#include "../Lib/httplib.hpp"
#include "../Lib/json.hpp"

// Shorten namespace names
namespace http = httplib;
namespace json = nlohmann;


void GameApi() {

    // Set up server and SlotMachine
    http::Server svr;
    SlotMachine game;

    // Create a dummy player to be reused for any request
    Player player;

    svr.Post("/play", [&game, &player](const http::Request& req, http::Response& res) {

        // Proof of concept, in a real world api this could represent a player account
        if (req.has_header("Money"))
            // Set player money to the money in the header
            player.money = std::stoi(req.get_header_value("Money"));

        json::json body{};
        auto [slots, victory, out_of_money] = game.Play(player);

        if (out_of_money) {
            res.status = 400;
            return;
        }

        for (Colour slot : slots) {
            body["Slots"] += {
                slot_mappings.at(slot)
            };
        }
        body["Result"] = victory ? "win" : "lose";

        res.set_content(body.dump(), "application/json");
    });

    // Start the server
    std::cout << "[ ----- API launched ----- ]" << '\n';
    svr.listen("localhost", 7250);
}


// This example runs until player is out of money
int main() {

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
