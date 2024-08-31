#ifndef TETRIS_H
#define TETRIS_H

#include "Engine/GameEngine.hpp"
#include <SFML/Graphics.hpp>
#include <vector>
#include "SFML/Graphics/Sprite.hpp"
#include "block.hpp"
#include <queue>
#include "SFML/System/Vector2.hpp"


class Tetris : public State {
public:
    Tetris(GameDataRef data);
    ~Tetris();
    void Init() override;
    void HandleInput() override;
    void Update(float dt) override;
    void Draw(float dt) override;
    void Pause() override;
    void Resume() override;

private:
    static constexpr int HEIGHT = 20 + 2;   // Add 2 as an additional space when spawning.
    static constexpr int WIDTH = 10;
    static constexpr int BLOCK_SIZE = 24;

    static constexpr int GRID_WIDTH = WIDTH * BLOCK_SIZE;
    static constexpr int GRID_HEIGHT = (HEIGHT - 2) * BLOCK_SIZE; // Subtract 2 for the extra rows added at the top.
    
    static constexpr float offsetX = ((float) GameEngine::WIDTH - GRID_WIDTH) / 4;
    static constexpr float offsetY = ((float) GameEngine::HEIGHT - GRID_HEIGHT) / 3;

    std::queue<Block*> blockQueue;
    Block *currentBlock;
    Types grid[HEIGHT][WIDTH];              // Different types represent different colors.

    GameDataRef data;

    sf::Sprite blockSprite;
    sf::Sprite background;
    std::map<Types, sf::Sprite> blockSprites;
    std::vector<sf::Sprite> sprites;
    std::vector<sf::Text> texts;

    static constexpr float FALL_TIME = 1.25;
    float elapsedTime;

    bool isWithinBounds();
    bool isValidTile(sf::Vector2u pos);

    void MoveLeft();
    void MoveDown();
    void MoveRight();
    void Rotate();
    void LockCurrentBlock();
    void GetNextBlock();
    void CheckRowClear(int row); 
};

#endif
