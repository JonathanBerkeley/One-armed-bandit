#include <iostream>
#include <random>

// Possible slot results
enum class Colours : int {
    black = 0,
    white,
    green,
    yellow
};

// Holds the result of one game
struct GameResult {
    Colours colours[4]{};
    bool victory = false;
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
    // todo: Implement random generation of numbers
public:
    SlotMachine() {
        
    }

    GameResult play(const Player& player) {
        GameResult result{};

        // todo: Game logic

        return result;
    }
    
};


int main() {
    SlotMachine game;
    const Player player(100);


    while (player.money)
        std::cout << game.play(player).victory << '\n';
}