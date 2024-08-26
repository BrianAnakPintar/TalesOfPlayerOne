#include "Engine/InputManager.hpp"

bool InputManager::isSpriteClicked(sf::Sprite object, sf::Mouse::Button button, sf::RenderWindow& window) {
    if (sf::Mouse::isButtonPressed(button)) {
        sf::IntRect buttonRect(object.getPosition().x, object.getPosition().y, 
                               object.getGlobalBounds().width, object.getGlobalBounds().height);
        if (buttonRect.contains(sf::Mouse::getPosition(window)))
            return true;
    }
    return false;
}

bool InputManager::isTextClicked(sf::Text object, sf::Mouse::Button button, sf::RenderWindow& window) {
    if (sf::Mouse::isButtonPressed(button)) {
        sf::FloatRect buttonRect = object.getGlobalBounds();
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        // Convert the mouse position from window coordinates to world coordinates
        sf::Vector2f worldPos = window.mapPixelToCoords(mousePos);
        if (buttonRect.contains(worldPos)) {
            return true;
        }
    }
    return false;
}

sf::Vector2<int> InputManager::GetMousePosition(sf::RenderWindow& window) {
    return sf::Mouse::getPosition(window);
}

