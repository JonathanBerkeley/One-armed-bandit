#include <iostream>
#include <random>
#include <string>
#include <unordered_map>

constexpr int COST_TO_PLAY = 5;

// Possible slot results
enum class Colour : int {
    black = 0,
    white,
    green,
    yellow
};


// Holds the result of one game
struct GameResult {
    Colour slots[4];
    bool victory = true;
    bool error = false;
};


// Represent the player
class Player {
private:
public:
    std::int64_t money{};
    Player() = default;
    explicit Player(const int money) : money(money) {}
};


// Represent the one armed bandit
class SlotMachine {
private:
    std::int64_t jackpot = 1'000;

    // Random generation
    std::mt19937_64 generator;
    std::random_device rd;
    std::uniform_int_distribution<> dist;
public:
    SlotMachine() {
        // Initialise & seed random generator
        generator = std::mt19937_64{rd()};
        dist = std::uniform_int_distribution<>(0, 3);
    }

    GameResult play(Player& player) {
        
        GameResult result{};

        if (player.money < COST_TO_PLAY) {
            std::cout << "Not enough money to play!" << '\n';
            result.error = true;
            return result;
        }

        player.money -= COST_TO_PLAY;
        jackpot += COST_TO_PLAY;
        std::cout << "Jackpot: " << jackpot << " Rolling...\n";
        
        for (Colour& slot : result.slots) {
            // Fill a slot with a random colour
            slot = static_cast<Colour>(dist(generator));

            const Colour first_slot = result.slots[0];

            if (slot != first_slot) {
                result.victory = false;
                return result;
            }

        }

        // The player won!
        player.money += jackpot;
        jackpot = 0;

        result.victory = true;
        return result;
    }
    
};


int main() {
    SlotMachine game;
    Player player(1'000);

    const std::unordered_map<int, std::string> slot_mappings{
        {0, "Black"},
        {1, "White"},
        {2, "Green"},
        {3, "Yellow"}
    };

    while (player.money) {
        auto [slots, victory, error] = game.play(player);
        // Player didn't have enough money
        if (error)
            return error;

        // Output slot results
        for (Colour slot : slots) {
            auto colour_code = static_cast<int>(slot);
            std::cout << "Slot : " << slot_mappings.at(colour_code) << '\n';
        }

        std::cout << player.money << '\n';
        std::cout << (victory ? "Won!" : "Lost!") << "\n\n";
    }

    return 0;
}
