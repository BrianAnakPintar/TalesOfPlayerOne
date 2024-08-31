#include "Engine/GameEngine.hpp"
#include "Scenes/MainMenu.hpp"

GameEngine::GameEngine(int width, int height, const std::string& title) {
    this->data->window.create(sf::VideoMode(width, height), title);
    this->data->stateMachine.AddState(StateRef(new MainMenu(this->data)));
    this->Run();
}

void GameEngine::Run() {
    float newTime, frameTime, interpolation;
    float currentTime = this->clock.getElapsedTime().asSeconds();
    float accumulator = 0.0f;

    while (this->data->window.isOpen()) {
        this->data->stateMachine.ProcessStateChanges();
        newTime = this->clock.getElapsedTime().asSeconds();
        frameTime = newTime - currentTime;
        if (frameTime > 0.25f) {
            frameTime = 0.25f;
        }
        currentTime = newTime;
        accumulator += frameTime;
        while (accumulator >= this->dt) {
            this->data->stateMachine.GetActiveState()->HandleInput();
            this->data->stateMachine.GetActiveState()->Update(this->dt);
            accumulator -= dt;
        }
        interpolation = accumulator/dt;
        this->data->stateMachine.GetActiveState()->Draw(interpolation);
    }
}
