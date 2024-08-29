#include "Engine/InputManager/Button.hpp"

Button::Button(const std::string& text, const sf::Font& font, unsigned int characterSize, const sf::Vector2f& size, const sf::Color& textColor, const sf::Color& buttonColor) {
    buttonShape.setSize(size);
    buttonShape.setFillColor(buttonColor);

    buttonText.setFont(font);
    buttonText.setString(text);
    buttonText.setCharacterSize(characterSize);
    buttonText.setFillColor(textColor);
    
    sf::FloatRect textRect = buttonText.getLocalBounds();
    buttonText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);

    this->buttonColor = buttonColor;
    this->hoverColor = buttonColor;  // Default hover color is the same as button color
}

void Button::setPosition(const sf::Vector2f& position) {
    buttonShape.setPosition(position);
    buttonText.setPosition(
        position.x + buttonShape.getSize().x / 2.0f,
        position.y + buttonShape.getSize().y / 2.0f
    );
}

void Button::setTextColor(const sf::Color& color) {
    buttonText.setFillColor(color);
}

void Button::setButtonColor(const sf::Color& color) {
    buttonShape.setFillColor(color);
    buttonColor = color;
}

void Button::setHoverColor(const sf::Color& color) {
    hoverColor = color;
}

void Button::draw(sf::RenderWindow& window) {
    if (isMouseOver(window)) {
        buttonShape.setFillColor(hoverColor);
    } else {
        buttonShape.setFillColor(buttonColor);
    }

    window.draw(buttonShape);
    window.draw(buttonText);
}

bool Button::isMouseOver(const sf::RenderWindow& window) const {
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    sf::FloatRect buttonBounds = buttonShape.getGlobalBounds();

    return buttonBounds.contains(static_cast<sf::Vector2f>(mousePos));
}

bool Button::isClicked(const sf::RenderWindow& window) const {
    return isMouseOver(window) && sf::Mouse::isButtonPressed(sf::Mouse::Left);
}
