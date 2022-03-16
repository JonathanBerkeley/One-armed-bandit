#include <iostream>
#include <random>
#include <vector>

// Possible slot results
enum class Colour : int {
    black = 0,
    white,
    green,
    yellow
};

// Holds the result of one game
struct GameResult {
    std::vector<Colour> slots;
    bool victory = true;
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

    GameResult play(const Player& player) {

        // todo: Check money of player before allowing play
        // todo: Deduct player money

        GameResult result{};
        
        for (Colour& slot : result.slots) {
            // Fill a slot with a random colour
            slot = static_cast<Colour>(dist(generator));

            const Colour first_slot = result.slots[0];

            if (slot != first_slot) {
                result.victory = false;
                return result;
            }

        }
        
        result.victory = false;
        return result;
    }
    
};


int main() {
    SlotMachine game;
    const Player player(100);


    while (player.money)
        std::cout << game.play(player).victory << '\n';
}
