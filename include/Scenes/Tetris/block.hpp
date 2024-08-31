#ifndef BLOCK_H
#define BLOCK_H

#include "SFML/System/Vector2.hpp"
#include <map>
#include <vector>
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

class Block {
protected:
    Types blockType;
    std::map<int, std::vector<sf::Vector2u>> grids;
    int rotationState;
    sf::Vector2u offset;

public:
    Block();
    void rotate();
    void rotate_counter();
    void move(int x, int y);
    void Draw();
    // This returns the grid added with an offset.
    std::vector<sf::Vector2u> getGrid();
    void setOffset(int x, int y);
    Types getType();
};

#endif // !BLOCK_H
