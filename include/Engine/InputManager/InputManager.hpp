#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include <SFML/Graphics.hpp>

class InputManager {
public:
    bool isSpriteClicked(sf::Sprite object, sf::Mouse::Button button, sf::RenderWindow& window);
    bool isTextClicked(sf::Text object, sf::Mouse::Button button, sf::RenderWindow& window);
    sf::Vector2<int> GetMousePosition(sf::RenderWindow& window);
};

#endif // !INPUT_MANAGER_H
