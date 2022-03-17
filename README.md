[![forthebadge](https://forthebadge.com/images/badges/made-with-c-plus-plus.svg)](https://forthebadge.com)

# One armed bandit
Gambling slot machine game, coding challenge for Phorest

# Building
Requires C++20    
Project set up for Visual Studio    

- Open Visual Studio solution file (One-armed-bandit/OneArmedBandit/OneArmedBandit.sln)    
- Build project OneArmedBandit    

# Testing
UnitTests project in the same solution contains the unit tests    

# GameAPI Get requests
Supports a networked API mode to expose the game functionality    
```
/play       -> Plays a round of the game
/play       -> With header "Money" and integer value of money, sets player's available money
```

### Example output
```json
{
    "Jackpot": 1095,
    "Money": 95,
    "Result": "lose",
    "Slots": [
        [
            "Black"
        ],
        [
            "Yellow"
        ],
        [
            "Green"
        ],
        [
            "Black"
        ]
    ]
}
```
