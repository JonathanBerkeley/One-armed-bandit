#include <iostream>
#include <string>

#include "SlotMachine.h"
#include "Player.h"

#include "../Lib/httplib.hpp"
#include "../Lib/json.hpp"

// Shorten namespace names
namespace http = httplib;
namespace json = nlohmann;


void GameApi() {
    // Set up server and SlotMachine
    std::cout << "[ ----- API launched ----- ]" << '\n';
    http::Server svr;
    SlotMachine game;

    // Create a dummy player to be reused for any request
    Player player;

    svr.Get("/play", [&game, &player](const http::Request& req, http::Response& res) {

        // Proof of concept, in a real world api this could represent a player account
        if (req.has_header("Money"))
            // Set player money to the money in the header
            player.money = std::stoi(req.get_header_value("Money"));

        json::json body{};
        auto [slots, victory, out_of_money] = game.Play(player);

        // Player had no money
        if (out_of_money) {
            res.status = 400;
            const json::json error_body{ {"Error", "Not enough money"}};
            res.set_content(error_body.dump(), "application/json");
            return;
        }

        // Convert results of slot machine into JSON representation
        for (Colour slot : slots) {
            body["Slots"] += {
                slot_mappings.at(slot)
            };
        }
        // Add result to JSON representation
        body["Result"] = victory ? "win" : "lose";

        // Add player's remaining money to JSON
        body["Money"] = player.money;

        // Add machine's jackpot to JSON
        body["Jackpot"] = game.jackpot;

        // Return JSON content to requester
        res.set_content(body.dump(), "application/json");
    });

    // Start the server
    svr.listen("localhost", 7250);
}
