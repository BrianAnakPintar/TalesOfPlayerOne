#include "Scenes/Tetris/Tetris.hpp"
#include "SFML/Graphics/Color.hpp"
#include "SFML/Graphics/Text.hpp"
#include "SFML/System/Vector2.hpp"
#include "Scenes/Tetris/TetrisBlocks.hpp"
#include "SFML/Window/Keyboard.hpp"
#include "Scenes/Tetris/block.hpp"
#include <cstdlib>
#include <string>

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

    // Load the texture for the book pages
    sf::Sprite book;
    this->data->assetManager.LoadTexture("book", ResourceDir + "/texture/book_page.png");
    book.setTexture(this->data->assetManager.GetTexture("book"));
    book.setScale(2.1, 2.1);

    // Load the second page (book2)
    sf::Sprite book2;
    book2.setTexture(this->data->assetManager.GetTexture("book"));
    book2.setScale(2.1, 2.1);

    // Calculate the combined width of both pages
    float combinedWidth = book.getGlobalBounds().width + book2.getGlobalBounds().width;

    // Position the first page (book) on the left side
    book.setPosition(
        ((float) GameEngine::WIDTH) / 2 - combinedWidth / 2,  // Centered horizontally
        ((float) GameEngine::HEIGHT) / 2 - book.getGlobalBounds().height / 2  // Centered vertically
    );

    // Position the second page (book2) on the right side, next to the first page
    book2.setPosition(
        book.getPosition().x + book.getGlobalBounds().width,  // Right next to the first page
        ((float) GameEngine::HEIGHT) / 2 - book2.getGlobalBounds().height / 2  // Centered vertically
    );

    this->scoreText.setFont(this->data->assetManager.GetFont("thaleah"));
    this->scoreText.setPosition(book2.getPosition().x + 50, book2.getPosition().y);
    this->scoreText.setString("Score: ");
    this->scoreText.setCharacterSize(48);
    this->scoreText.setFillColor(sf::Color::Black);

    // Add the sprites to the list
    this->sprites.emplace_back(std::move(book));
    this->sprites.emplace_back(std::move(book2));
    this->elapsedTime = 0;
    this->heldBlock = nullptr;
    this->startLockTimer = false;
    this->cooldownTime = 0;
    this->gameEnd = false;

    this->blockQueue.push(GetRandomBlock());
    this->blockQueue.push(GetRandomBlock());
    this->blockQueue.push(GetRandomBlock());
    GetNextBlock();
}

void Tetris::HandleInput() {
    sf::Event event;
    while (this->data->window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            this->data->window.close();
        }
        if (!gameEnd && event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::H) {
                MoveLeft();
            } else if (event.key.code == sf::Keyboard::J) {
                MoveDown();
            } else if (event.key.code == sf::Keyboard::K) {
                Rotate();
            } else if (event.key.code == sf::Keyboard::L) {
                MoveRight();
            } else if (event.key.code == sf::Keyboard::Space) {
                HardDrop();
            } else if (event.key.code == sf::Keyboard::V) {
                HoldBlock();
            }
        }
    }
}

void Tetris::Update(float dt) {
    if (gameEnd)
        return;
    this->elapsedTime += dt;
    if (!this->startLockTimer && this->elapsedTime >= this->FALL_TIME) {
        this->elapsedTime = 0;
        MoveDown();
    }
    if (this->startLockTimer) {
        this->cooldownTime += dt;
        if (this->cooldownTime >= this->FALL_TIME) {
            LockCurrentBlock();
            this->startLockTimer = false;
            this->cooldownTime = 0;
        }
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
                if (gameEnd) {
                    spr_block.setColor(sf::Color(100,100,100));
                }
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
        if (gameEnd) {
            spr_block.setColor(sf::Color(100,100,100));
        }
        spr_block.setPosition(offsetX + vec.x * BLOCK_SIZE, offsetY + vec.y  * BLOCK_SIZE);
        this->data->window.draw(spr_block);
    }
    DrawGhostBlock();

    // Render all the blocks in the queue on the side.

    float verticalOffset = 0.0f; // Initial vertical offset
    if (!this->blockQueue.empty()) {
        // Create a copy of the queue to preserve the original queue
        std::queue<Block*> tempQueue = this->blockQueue;

        while (!tempQueue.empty()) {
            Block* nextBlock = tempQueue.front(); // Get the next block
            tempQueue.pop(); // Remove it from the temporary queue

            std::vector<sf::Vector2u> nextBlockGrid = nextBlock->getGrid();
            for (sf::Vector2u vec : nextBlockGrid) {
                sf::Sprite spr_next_block = this->blockSprites[nextBlock->getType()];
                // Positioning next to the main grid with an additional vertical offset
                spr_next_block.setPosition(
                    offsetX + (WIDTH + .75) * BLOCK_SIZE + vec.x * BLOCK_SIZE,
                    offsetY + 2 * BLOCK_SIZE + vec.y * BLOCK_SIZE + verticalOffset
                );
                this->data->window.draw(spr_next_block);
            }

            // Increase the vertical offset for the next block in the queue
            verticalOffset += (4 * BLOCK_SIZE); // Adjust based on block size and desired spacing
        }

        verticalOffset = (4*BLOCK_SIZE)*4.5;
        if (this->heldBlock != nullptr) {
            std::vector<sf::Vector2u> blkGrid = this->heldBlock->getGrid();
            Types type = this->heldBlock->getType();
            for (sf::Vector2u vec : blkGrid) {
                sf::Sprite spr_next_block = this->blockSprites[type];
                spr_next_block.setPosition(
                    (WIDTH + 2.75) * BLOCK_SIZE + vec.x * BLOCK_SIZE,
                    2 * BLOCK_SIZE + vec.y * BLOCK_SIZE + verticalOffset
                );
                this->data->window.draw(spr_next_block);
            }

        }
    }

    this->scoreText.setString("Score: " + std::to_string((int)this->score));
    data->window.draw(this->scoreText);
    
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
        this->startLockTimer = true;
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


void Tetris::HardDrop() {
    int dropDistance = 0;
    bool canDrop = true;

    // Find the maximum drop distance
    while (canDrop) {
        for (sf::Vector2u vec : this->currentBlock->getGrid()) {
            int newY = vec.y + dropDistance + 1; // Check the next row down
            if (newY >= HEIGHT || grid[newY][vec.x] != Types::Empty) {
                canDrop = false; // Block can't drop further
                break;
            }
        }
        if (canDrop) {
            dropDistance++; // Increment drop distance
        }
    }

    // Move the block down by the drop distance
    this->currentBlock->move(0, dropDistance); // Assuming move(x, y) moves the block by x, y cells

    // Lock the block in place
    LockCurrentBlock();
}

bool Tetris::CheckRowClear(int row) {
    // Don't clear if row is not full.
    for (int i = 0; i < WIDTH; i++) {
        if (grid[row][i] == Types::Empty)
            return false;
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
    return true;

    // Clear the top row, as it has been "dropped" down.
    for (int i = 0; i < WIDTH; i++) {
        grid[0][i] = Types::Empty;
    }
}

void Tetris::LockCurrentBlock() {
    if (!isWithinBounds()) {
        gameEnd = true;
    }
    std::vector<sf::Vector2u> tiles = this->currentBlock->getGrid();
    for (sf::Vector2u tile : tiles) {
        this->grid[tile.y][tile.x] = this->currentBlock->getType();
    }
    int rowClears = 0;
    for (sf::Vector2u tile : tiles) {
        if (CheckRowClear(tile.y)) {
            rowClears++;
        }
    }
    switch (rowClears) {
        case 1:
            this->score += 100;
        case 2:
            this->score += 300;
        case 3:
            this->score += 500;
        case 4:
            this->score += 800;
    }

    free(currentBlock);
    GetNextBlock();
}

Block* Tetris::GetRandomBlock() {
    int next_block = (std::rand() % 7);
    switch (next_block) {
        case 0:
            return new IBlock();
        case 1:
            return new JBlock();
        case 2:
            return new ZBlock();
        case 3:
            return new SBlock();
        case 4:
            return new LBlock();
        case 5:
            return new OBlock();
        case 6:
            return new TBlock();
    }
    return nullptr;
}

void Tetris::GetNextBlock() {
    Block *new_block = GetRandomBlock(); 
    this->blockQueue.push(new_block);
    this->currentBlock = blockQueue.front();
    blockQueue.pop();
    this->currentBlock->setOffset(3, 0);
}


void Tetris::DrawGhostBlock() {
    int dropDistance = 0;
    bool canDrop = true;

    // Calculate the drop distance for the ghost block
    while (canDrop) {
        for (sf::Vector2u vec : this->currentBlock->getGrid()) {
            int newY = vec.y + dropDistance + 1;
            if (newY >= HEIGHT || grid[newY][vec.x] != Types::Empty) {
                canDrop = false;
                break;
            }
        }
        if (canDrop) {
            dropDistance++;
        }
    }

    // Draw the ghost block at the calculated position
    std::vector<sf::Vector2u> block = this->currentBlock->getGrid();
    for (sf::Vector2u vec : block) {
        sf::Sprite spr_ghost_block = this->blockSprites[currentBlock->getType()];
        spr_ghost_block.setPosition(offsetX + vec.x * BLOCK_SIZE, offsetY + (vec.y + dropDistance) * BLOCK_SIZE);
        sf::Color originalColor = spr_ghost_block.getColor();
        sf::Color transparentColor = originalColor;
        transparentColor.a = 100; // Set alpha value for transparency (0-255)
        spr_ghost_block.setColor(transparentColor);
        this->data->window.draw(spr_ghost_block);
    }
}

void Tetris::HoldBlock() {
    if (this->heldBlock == nullptr) {
        this->heldBlock = currentBlock;
        this->heldBlock->setOffset(3, 0);
        GetNextBlock();
    } else {
        // Swap the current block with the held block
        Block* tmp = this->heldBlock;
        this->heldBlock = this->currentBlock;
        this->currentBlock = tmp;

        // Reset the offset of the new current block (if needed)
        this->currentBlock->setOffset(3, 0);
        this->heldBlock->setOffset(3, 0);
    }
}
