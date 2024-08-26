#ifndef PLAYER_H
#define PLAYER_H

#include <cstdint>
#include <string>

class Player {
private:
    std::string name;
    uint8_t health;

public:
    void debug();
};

#endif // !PLAYER_H
