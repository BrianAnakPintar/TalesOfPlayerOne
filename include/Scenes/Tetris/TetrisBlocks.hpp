#ifndef TETRISBLOCK_H
#define TETRISBLOCK_H
#include "block.hpp"

class LBlock : public Block {
public:
    LBlock() {
        this->blockType = Types::L_Shape;
        this->rotationState = 0;

        this->grids[0] = {sf::Vector2u(0, 1), sf::Vector2u(1, 1), sf::Vector2u(2, 1), sf::Vector2u(2, 0)};
        this->grids[1] = {sf::Vector2u(1, 0), sf::Vector2u(1, 1), sf::Vector2u(1, 2), sf::Vector2u(2, 2)};
        this->grids[2] = {sf::Vector2u(0, 1), sf::Vector2u(1, 1), sf::Vector2u(2, 1), sf::Vector2u(0, 2)};
        this->grids[3] = {sf::Vector2u(0, 0), sf::Vector2u(1, 0), sf::Vector2u(1, 1), sf::Vector2u(1, 2)};
    }
};

class IBlock : public Block {
public:
    IBlock() {
        this->blockType = Types::I_Shape;
        this->rotationState = 0;

        this->grids[0] = {sf::Vector2u(0, 1), sf::Vector2u(1, 1), sf::Vector2u(2, 1), sf::Vector2u(3, 1)};
        this->grids[1] = {sf::Vector2u(2, 0), sf::Vector2u(2, 1), sf::Vector2u(2, 2), sf::Vector2u(2, 3)};
        this->grids[2] = {sf::Vector2u(0, 2), sf::Vector2u(1, 2), sf::Vector2u(2, 2), sf::Vector2u(3, 2)};
        this->grids[3] = {sf::Vector2u(1, 0), sf::Vector2u(1, 1), sf::Vector2u(1, 2), sf::Vector2u(1, 3)};
    }
};

class JBlock : public Block {
public:
    JBlock() {
        this->blockType = Types::J_Shape;
        this->rotationState = 0;

        this->grids[0] = {sf::Vector2u(0, 0), sf::Vector2u(0, 1), sf::Vector2u(1, 1), sf::Vector2u(2, 1)};
        this->grids[1] = {sf::Vector2u(1, 0), sf::Vector2u(1, 1), sf::Vector2u(1, 2), sf::Vector2u(2, 0)};
        this->grids[2] = {sf::Vector2u(0, 1), sf::Vector2u(1, 1), sf::Vector2u(2, 1), sf::Vector2u(2, 2)};
        this->grids[3] = {sf::Vector2u(1, 0), sf::Vector2u(1, 1), sf::Vector2u(1, 2), sf::Vector2u(0, 2)};
    }
};

class OBlock : public Block {
public:
    OBlock() {
        this->blockType = Types::O_Shape;
        this->rotationState = 0;

        this->grids[0] = {sf::Vector2u(0, 0), sf::Vector2u(0, 1), sf::Vector2u(1, 0), sf::Vector2u(1, 1)};
        this->grids[1] = this->grids[0];
        this->grids[2] = this->grids[0];
        this->grids[3] = this->grids[0];
    }
};

class SBlock : public Block {
public:
    SBlock() {
        this->blockType = Types::S_Shape;
        this->rotationState = 0;

        this->grids[0] = {sf::Vector2u(1, 0), sf::Vector2u(2, 0), sf::Vector2u(0, 1), sf::Vector2u(1, 1)};
        this->grids[1] = {sf::Vector2u(1, 0), sf::Vector2u(1, 1), sf::Vector2u(2, 1), sf::Vector2u(2, 2)};
        this->grids[2] = {sf::Vector2u(1, 1), sf::Vector2u(2, 1), sf::Vector2u(0, 2), sf::Vector2u(1, 2)};
        this->grids[3] = {sf::Vector2u(0, 0), sf::Vector2u(0, 1), sf::Vector2u(1, 1), sf::Vector2u(1, 2)};
    }
};

class TBlock : public Block {
public:
    TBlock() {
        this->blockType = Types::T_Shape;
        this->rotationState = 0;

        this->grids[0] = {sf::Vector2u(1, 0), sf::Vector2u(0, 1), sf::Vector2u(1, 1), sf::Vector2u(2, 1)};
        this->grids[1] = {sf::Vector2u(1, 0), sf::Vector2u(1, 1), sf::Vector2u(2, 1), sf::Vector2u(1, 2)};
        this->grids[2] = {sf::Vector2u(0, 1), sf::Vector2u(1, 1), sf::Vector2u(2, 1), sf::Vector2u(1, 2)};
        this->grids[3] = {sf::Vector2u(1, 0), sf::Vector2u(0, 1), sf::Vector2u(1, 1), sf::Vector2u(1, 2)};
    }
};

class ZBlock : public Block {
public:
    ZBlock() {
        this->blockType = Types::Z_Shape;
        this->rotationState = 0;

        this->grids[0] = {sf::Vector2u(0, 0), sf::Vector2u(1, 0), sf::Vector2u(1, 1), sf::Vector2u(2, 1)};
        this->grids[1] = {sf::Vector2u(2, 0), sf::Vector2u(1, 1), sf::Vector2u(2, 1), sf::Vector2u(1, 2)};
        this->grids[2] = {sf::Vector2u(0, 1), sf::Vector2u(1, 1), sf::Vector2u(1, 2), sf::Vector2u(2, 2)};
        this->grids[3] = {sf::Vector2u(1, 0), sf::Vector2u(0, 1), sf::Vector2u(1, 1), sf::Vector2u(0, 2)};
    }
};

#endif // !TETRISBLOCK_H

