#include "game.hpp"

Game::Game() {
    // Clear the board.
    for (int i = 0; i < Game::HEIGHT; i++) {
        for (int j = 0; j < Game::WIDTH; j++) {
            grid[i][j] = Empty;
        }
    }
}

void Game::tick() {
    return;
}
