#include "Engine/AssetManager.hpp"

void AssetManager::LoadTexture(const std::string& name, const std::string& fileName) {
    sf::Texture texture;    
    if (texture.loadFromFile(fileName)) {
        this->textures[name] = texture;
    }
}

const sf::Texture& AssetManager::GetTexture(const std::string& name) {
    return this->textures.at(name);
}

void AssetManager::LoadFont(const std::string& name, const std::string& fileName) {
    sf::Font font;
    if (font.loadFromFile(fileName)) {
        this->fonts[name] = font;
    }
}

const sf::Font& AssetManager::GetFont(const std::string& name) {
    return this->fonts.at(name);
}
