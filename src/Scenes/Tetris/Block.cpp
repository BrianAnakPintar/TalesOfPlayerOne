#include "Scenes/Tetris/block.hpp"

Block::Block() {}

std::vector<sf::Vector2u> Block::getGrid() {
    std::vector<sf::Vector2u> pos = this->grids[this->rotationState];
    std::vector<sf::Vector2u> res; 

    for (sf::Vector2u vec : pos) {
        res.emplace_back(sf::Vector2u(vec.x + offset.x, vec.y + offset.y));
    }

    return res;
}

void Block::rotate() {
    this->rotationState = (this->rotationState + 1)%this->grids.size();
}

void Block::rotate_counter() {
    this->rotationState = (this->rotationState - 1);
    if (this->rotationState < 0)
        this->rotationState = this->grids.size()-1;
}

void Block::setOffset(int x, int y) {
    this->offset.x = x;
    this->offset.y = y;
}

void Block::move(int x, int y) {
    this->offset.x += x;
    this->offset.y += y;
}

Types Block::getType() {
    return this->blockType;
}
