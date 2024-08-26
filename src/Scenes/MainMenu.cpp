#include "Scenes/MainMenu.hpp"
#include "SFML/Graphics/Text.hpp"
#include <iostream>

MainMenu::MainMenu(GameDataRef data): data(data) {
    this->name = "Main Menu";
}

MainMenu::~MainMenu() {}

// Load all our assets!
void MainMenu::Init() {
    // Load Assets.
    std::string ResourceDir = std::string(RESOURCES_DIR);
    this->data->assetManager.LoadFont("thaleah", ResourceDir + "/fonts/ThaleahFat.ttf");
    this->data->assetManager.LoadTexture("paper_menu", ResourceDir + "/texture/paper_menu.png");
    this->data->assetManager.LoadTexture("table_bg", ResourceDir + "/texture/table_background.png");

    // Apply Assets.

    // TITLE
    sf::Text game_title;
    game_title.setFont(this->data->assetManager.GetFont("thaleah"));
    game_title.setString("Tales of Player 1.");
    game_title.setCharacterSize(48);
    game_title.setFillColor(sf::Color::Black);
    game_title.setPosition(((float) GameEngine::WIDTH/2) - (game_title.getGlobalBounds().width/2),
                           ((float) GameEngine::HEIGHT/5) - (game_title.getGlobalBounds().height/5));
    this->texts.emplace_back(std::move(game_title));

    // Background
    sf::Sprite background;
    background.setTexture(this->data->assetManager.GetTexture("table_bg"));
    background.setScale(1.35f, 1.35f);
    background.setPosition(((float) GameEngine::WIDTH/2) - (background.getGlobalBounds().width/2),
                           ((float) GameEngine::HEIGHT/2) - (background.getGlobalBounds().height/2));
    sprites.emplace_back(std::move(background));
    
    sf::Sprite paper;
    paper.setTexture(this->data->assetManager.GetTexture("paper_menu"));
    paper.setPosition(((float) GameEngine::WIDTH/2) - (paper.getGlobalBounds().width/2),
                      ((float) GameEngine::HEIGHT/2) - (paper.getGlobalBounds().height/2));
    sprites.emplace_back(std::move(paper));

    this->playButton.setFont(this->data->assetManager.GetFont("thaleah"));
    this->playButton.setString("Play Game");
    this->playButton.setCharacterSize(48);
    this->playButton.setFillColor(sf::Color::Black);
    this->playButton.setPosition(((float) GameEngine::WIDTH/2) - (playButton.getGlobalBounds().width/2),
                                 ((float) GameEngine::HEIGHT/3) - (playButton.getGlobalBounds().height/3));

}

void MainMenu::HandleInput() {
    sf::Event event;
    while (this->data->window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            this->data->window.close();
        } 

        if (this->data->inputManager.isTextClicked(this->playButton, sf::Mouse::Left, this->data->window)) {
            std::cout << "Heading to game screen" << std::endl;
        }
    }
}

void MainMenu::Update(float dt) {
    
}

void MainMenu::Draw(float dt) {
    this->data->window.clear(sf::Color::White);

    for (sf::Sprite sprite : this->sprites) {
        this->data->window.draw(sprite);
    }
    for (sf::Text text : this->texts) {
        this->data->window.draw(text);
    }
    this->data->window.draw(playButton);

    this->data->window.display();
}

void MainMenu::Pause() {
    
}

void MainMenu::Resume() {
    
}

