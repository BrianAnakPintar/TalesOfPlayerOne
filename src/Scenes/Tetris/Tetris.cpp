#include "Scenes/Tetris/Tetris.hpp"
#include "SFML/Window/Keyboard.hpp"

Tetris::Tetris(GameDataRef data) : data(data) {
    this->name = "Tetris Game!";
}

Tetris::~Tetris() {}

void Tetris::Init() {
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            this->grid[y][x] = Types::Empty;
            if (y == 10)
                this->grid[y][x] = Types::Z_Shape;
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
}

void Tetris::HandleInput() {
    sf::Event event;
    while (this->data->window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            this->data->window.close();
        }
        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::H) {
                // Move left.
            } else if (event.key.code == sf::Keyboard::J) {
                // Soft Drop.
            } else if (event.key.code == sf::Keyboard::K) {
                // Rotate.
            } else if (event.key.code == sf::Keyboard::L) {
                // Move right
            }
        }
    }
}

void Tetris::Update(float dt) {
    
}

void Tetris::Draw(float dt) {
    data->window.clear();
    for (int y = 2; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            if (grid[y][x] != Types::Empty) {
                blockSprite.setColor(sf::Color::Green);
                blockSprite.setPosition(offsetX + x * BLOCK_SIZE, offsetY + (y - 2) * BLOCK_SIZE);
                this->data->window.draw(blockSprite);
            } else {
                blockSprite.setColor(sf::Color(80,80,80));
                blockSprite.setPosition(offsetX + x * BLOCK_SIZE, offsetY + (y - 2) * BLOCK_SIZE);
                this->data->window.draw(blockSprite);
            }
        }
    }
    data->window.display();
}

void Tetris::Pause() {

}

void Tetris::Resume() {

}
