#include "Scenes/Tetris/Tetris.hpp"
#include "SFML/Graphics/Color.hpp"
#include "SFML/System/Vector2.hpp"
#include "Scenes/Tetris/TetrisBlocks.hpp"
#include "SFML/Window/Keyboard.hpp"
#include "Scenes/Tetris/block.hpp"
#include <cstdlib>

Tetris::Tetris(GameDataRef data) : data(data) {
    this->name = "Tetris Game!";
}

Tetris::~Tetris() {}

void Tetris::Init() {
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            this->grid[y][x] = Types::Empty;
        }
    }
    std::string ResourceDir = std::string(RESOURCES_DIR);
    this->data->assetManager.LoadTexture("block", ResourceDir + "/texture/block.png");
    this->blockSprite.setTexture(this->data->assetManager.GetTexture("block"));

    float scaleFactor = static_cast<float>(BLOCK_SIZE) / this->blockSprite.getTexture()->getSize().x;
    this->blockSprite.setScale(scaleFactor, scaleFactor);

    sf::Text score;
    score.setFont(this->data->assetManager.GetFont("thaleah"));
    score.setString("Score: 0");
    score.setFillColor(sf::Color::Cyan);
    texts.push_back(score);
    
    // Create a new sprite for every blocks.
    sf::Sprite zBlock = this->blockSprite;
    zBlock.setColor(sf::Color::Red);
    this->blockSprites[Types::Z_Shape] = zBlock;

    sf::Sprite iBlock = this->blockSprite;
    iBlock.setColor(sf::Color::Cyan);
    this->blockSprites[Types::I_Shape] = iBlock;

    sf::Sprite jBlock = this->blockSprite;
    jBlock.setColor(sf::Color::Blue);
    this->blockSprites[Types::J_Shape] = jBlock;

    sf::Sprite sBlock = this->blockSprite;
    sBlock.setColor(sf::Color::Green);
    this->blockSprites[Types::S_Shape] = sBlock;

    sf::Sprite lBlock = this->blockSprite;
    lBlock.setColor(sf::Color(255, 127, 00));
    this->blockSprites[Types::L_Shape] = lBlock;

    sf::Sprite tBlock = this->blockSprite;
    tBlock.setColor(sf::Color(180,00,180));
    this->blockSprites[Types::T_Shape] = tBlock;

    sf::Sprite oBlock = this->blockSprite;
    oBlock.setColor(sf::Color::Yellow);
    this->blockSprites[Types::O_Shape] = oBlock;


    this->data->assetManager.LoadTexture("bg", ResourceDir + "/texture/table_background.png");
    this->background.setTexture(this->data->assetManager.GetTexture("bg"));
    sf::Vector2u windowSize = this->data->window.getSize();
    sf::Vector2u bgSize = this->data->assetManager.GetTexture("bg").getSize();
    float scaleX = static_cast<float>(windowSize.x) / bgSize.x;
    float scaleY = static_cast<float>(windowSize.y) / bgSize.y;
    this->background.setScale(scaleX, scaleY);

    sf::Sprite book;
    this->data->assetManager.LoadTexture("book", ResourceDir + "/texture/book_page.png");
    book.setTexture(this->data->assetManager.GetTexture("book"));
    book.setScale(2, 2);
    book.setPosition(((float) GameEngine::WIDTH/4) - (book.getGlobalBounds().width/4),
                    ((float) GameEngine::HEIGHT/2) - (book.getGlobalBounds().height/2));
    this->sprites.emplace_back(std::move(book));

    sf::Sprite book2;
    book.setTexture(this->data->assetManager.GetTexture("book"));
    book.setScale(2, 2);
    book.setPosition(((float) 3.45*GameEngine::WIDTH/4) - (3.45*book.getGlobalBounds().width/4),
                    ((float) GameEngine::HEIGHT/2) - (book.getGlobalBounds().height/2));
    this->sprites.emplace_back(std::move(book));
    this->elapsedTime = 0;
    GetNextBlock();
}

void Tetris::HandleInput() {
    sf::Event event;
    while (this->data->window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            this->data->window.close();
        }
        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::H) {
                MoveLeft();
            } else if (event.key.code == sf::Keyboard::J) {
                MoveDown();
            } else if (event.key.code == sf::Keyboard::K) {
                Rotate();
            } else if (event.key.code == sf::Keyboard::L) {
                MoveRight();
            }
        }
    }
}

void Tetris::Update(float dt) {
    this->elapsedTime = this->elapsedTime + 0.1 + dt;
    if (this->elapsedTime >= this->FALL_TIME) {
        this->elapsedTime = 0;
        MoveDown();
    }
}

void Tetris::Draw(float dt) {
    data->window.clear();
    this->data->window.draw(this->background);
    for (sf::Sprite s : this->sprites)
        this->data->window.draw(s);
    // Renders the grid and filled block.
    for (int y = 2; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            if (grid[y][x] != Types::Empty) {
                sf::Sprite spr_block = this->blockSprites[grid[y][x]];
                spr_block.setPosition(offsetX + x * BLOCK_SIZE, offsetY + y * BLOCK_SIZE);
                this->data->window.draw(spr_block);
            } else {
                blockSprite.setColor(sf::Color(80,80,80, 120));
                blockSprite.setPosition(offsetX + x * BLOCK_SIZE, offsetY + y * BLOCK_SIZE);
                this->data->window.draw(blockSprite);
            }
        }
    }

    // Renders the current falling block.
    std::vector<sf::Vector2u> block = this->currentBlock->getGrid();
    for (sf::Vector2u vec : block) {
        sf::Sprite spr_block = this->blockSprites[currentBlock->getType()];
        spr_block.setPosition(offsetX + vec.x * BLOCK_SIZE, offsetY + vec.y  * BLOCK_SIZE);
        this->data->window.draw(spr_block);
    }
    
    data->window.display();
}

void Tetris::Pause() {

}

void Tetris::Resume() {
    
}

bool Tetris::isValidTile(sf::Vector2u pos) {
    bool validX = (pos.x >= 0 && pos.x < this->WIDTH);
    bool validY = (pos.y >= 0 && pos.y < this->HEIGHT);
    
    return validX && validY;
}

// Checks whether the current block is within bounds of the grid.
bool Tetris::isWithinBounds() {
    std::vector<sf::Vector2u> grid = this->currentBlock->getGrid();
    for (sf::Vector2u vec : grid) {
        if (!isValidTile(vec) || this->grid[vec.y][vec.x] != Types::Empty) {
            return false;
        }
    }
    return true;
}

void Tetris::MoveLeft() {
    this->currentBlock->move(-1, 0);
    if (!isWithinBounds()) {
        this->currentBlock->move(1, 0);
    }
}

void Tetris::MoveDown() {
    this->currentBlock->move(0, 1);
    if (!isWithinBounds()) {
        this->currentBlock->move(0, -1);
        LockCurrentBlock();
    }
}

void Tetris::MoveRight() {
    this->currentBlock->move(1, 0);
    if (!isWithinBounds()) {
        this->currentBlock->move(-1, 0);
    }
}

void Tetris::Rotate() {
    this->currentBlock->rotate();
    if (!isWithinBounds()) {
        this->currentBlock->rotate_counter();
    }
}

void Tetris::CheckRowClear(int row) {
    // Don't clear if row is not full.
    for (int i = 0; i < WIDTH; i++) {
        if (grid[row][i] == Types::Empty)
            return;
    }
    
    // Clear the row by setting all its blocks to empty.
    for (int i = 0; i < WIDTH; i++) {
        grid[row][i] = Types::Empty;
    }

    // Drop all rows above the cleared row.
    for (int r = row; r > 0; r--) {
        for (int i = 0; i < WIDTH; i++) {
            grid[r][i] = grid[r-1][i];
        }
    }

    // Clear the top row, as it has been "dropped" down.
    for (int i = 0; i < WIDTH; i++) {
        grid[0][i] = Types::Empty;
    }
}

void Tetris::LockCurrentBlock() {
    std::vector<sf::Vector2u> tiles = this->currentBlock->getGrid();
    for (sf::Vector2u tile : tiles) {
        this->grid[tile.y][tile.x] = this->currentBlock->getType();

        // Check for collisions.
        CheckRowClear(tile.y);
    }
    free(currentBlock);
    GetNextBlock();
}

void Tetris::GetNextBlock() {
    int next_block = (std::rand() % 7);
    Block *new_block;
    switch (next_block) {
        case 0:
            new_block = new IBlock();
            break;
        case 1:
            new_block = new JBlock();
            break;
        case 2:
            new_block = new ZBlock();
            break;
        case 3:
            new_block = new SBlock();
            break;
        case 4:
            new_block = new LBlock();
            break;
        case 5:
            new_block = new OBlock();
            break;
        case 6:
            new_block = new TBlock();
            break;
    }

    this->blockQueue.push(new_block);
    this->currentBlock = blockQueue.front();
    blockQueue.pop();
    this->currentBlock->setOffset(3, 0);
}
