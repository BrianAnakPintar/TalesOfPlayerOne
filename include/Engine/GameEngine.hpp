#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H

#include "AssetManager/AssetManager.hpp"
#include "InputManager/InputManager.hpp"
#include "StateMachine/StateMachine.hpp"
#include <SFML/Graphics.hpp>
#include <string>
#include <memory>

struct GameData {
    StateMachine stateMachine;
    AssetManager assetManager;
    InputManager inputManager;
    sf::RenderWindow window;
};

typedef std::shared_ptr<GameData> GameDataRef;

class GameEngine {
private:
    GameDataRef data = std::make_shared<GameData>();
    const float dt = 1.0f/60.0f;
    sf::Clock clock;
    void Run();

public:
    static const int WIDTH = 1360;
    static const int HEIGHT = 720;
    GameEngine(int width, int height, const std::string& title);
};

#endif // !GAME_ENGINE_H
