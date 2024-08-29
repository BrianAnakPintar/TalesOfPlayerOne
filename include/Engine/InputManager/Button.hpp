#ifndef BUTTON_H
#define BUTTON_H
#include <SFML/Graphics.hpp>

class Button {
public:
    Button(const std::string& text, const sf::Font& font, unsigned int characterSize, const sf::Vector2f& size, const sf::Color& textColor, const sf::Color& buttonColor);

    void setPosition(const sf::Vector2f& position);
    void setTextColor(const sf::Color& color);
    void setButtonColor(const sf::Color& color);
    void setHoverColor(const sf::Color& color);

    void draw(sf::RenderWindow& window);
    bool isMouseOver(const sf::RenderWindow& window) const;
    bool isClicked(const sf::RenderWindow& window) const;

private:
    sf::RectangleShape buttonShape;
    sf::Text buttonText;
    sf::Color buttonColor;
    sf::Color hoverColor;
};

#endif // !BUTTON_H
