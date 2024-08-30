#ifndef TETRIS_H
#define TETRIS_H

#include "Engine/GameEngine.hpp"
#include <SFML/Graphics.hpp>
#include <vector>
#include "block.hpp"
#include <queue>
#include "SFML/System/Vector2.hpp"
#include "SFML/Window/Keyboard.hpp"
#include "Scenes/Tetris/TetrisBlocks.hpp"


class Tetris : public State {
private:
    static constexpr int HEIGHT = 20 + 2;   // Add 2 as an additional space when spawning.
    static constexpr int WIDTH = 10;
    static constexpr int BLOCK_SIZE = 24;


    static constexpr int GRID_WIDTH = WIDTH * BLOCK_SIZE;
    static constexpr int GRID_HEIGHT = (HEIGHT - 2) * BLOCK_SIZE; // Subtract 2 for the extra rows added at the top.
    
    static constexpr float offsetX = ((float) GameEngine::WIDTH - GRID_WIDTH) / 4;
    static constexpr float offsetY = ((float) GameEngine::HEIGHT - GRID_HEIGHT) / 2;

    std::queue<Block> blockQueue;
    Block *currentBlock;
    Types grid[HEIGHT][WIDTH];              // Different types represent different colors.

    GameDataRef data;
    sf::Clock clock;

    sf::Sprite blockSprite;
    std::vector<sf::Sprite> sprites;
    std::vector<sf::Text> texts;

public:
    Tetris(GameDataRef data);
    ~Tetris();
    void Init() override;
    void HandleInput() override;
    void Update(float dt) override;
    void Draw(float dt) override;
    void Pause() override;
    void Resume() override;
};

#endif
