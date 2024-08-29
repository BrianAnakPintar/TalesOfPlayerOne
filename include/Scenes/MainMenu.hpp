#ifndef MAINMENU_H
#define MAINMENU_H

#include "Engine/GameEngine.hpp"
#include <SFML/Graphics.hpp>
#include <vector>

class MainMenu : public State {
private:
    GameDataRef data;
    sf::Clock clock;

    std::vector<sf::Sprite> sprites;
    std::vector<sf::Text> texts;

    sf::Text playButton;
    sf::Text exitButton;

public:
    MainMenu(GameDataRef data);
    ~MainMenu();
    void Init() override;
    void HandleInput() override;
    void Update(float dt) override;
    void Draw(float dt) override;
    void Pause() override;
    void Resume() override;
};

#endif // !MAINMENU_H
