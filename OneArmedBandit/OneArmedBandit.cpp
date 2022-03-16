#include <iostream>
#include <random>


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
    int money{};
    Player() = default;
    explicit Player(const int money) : money(money) {}
};

// Represent the one armed bandit
class SlotMachine {
private:

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
        
        for (Colour& slot : result.slots) {
            // Fill a slot with a random colour
            slot = static_cast<Colour>(dist(generator));

            const Colour first_slot = result.slots[0];

            if (slot != first_slot) {
                result.victory = false;
                return result;
            }

        }
        
        result.victory = true;
        return result;
    }
    
};


int main() {
    SlotMachine game;
    Player player(1'000);

    while (player.money) {
        auto [slots, victory, error] = game.play(player);


        std::cout << (victory ? "Won!" : "Lost!") << '\n';

        // Player didn't have enough money
        if (error) {
            return error;
        }
    }


}
