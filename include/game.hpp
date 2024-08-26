#ifndef GAME_H
#define GAME_H

#include "block.hpp"
#include <queue>
#include "cstdint"

enum Types {
    Empty,
    I_Shape,
    J_Shape,
    L_Shape,
    O_Shape,
    S_Shape,
    T_Shape,
    Z_Shape
};

// This class represents a current game of Tetris.
class Game {
private: 
    static const uint8_t HEIGHT = 20 + 2;   // Add 2 as an additional space when spawning.
    static const uint8_t WIDTH = 10;

    std::queue<Block> blockQueue;
    Types grid[HEIGHT][WIDTH];              // Different types represent different colors.
public:
    Game();
    
    // Represents a single tick in the game. Applying physics and line clears.
    void tick();
};

#endif // !GAME_H
