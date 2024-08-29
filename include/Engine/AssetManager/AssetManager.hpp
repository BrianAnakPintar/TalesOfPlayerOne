#ifndef ASSET_MANAGER_H
#define ASSET_MANAGER_H

#include <SFML/Graphics.hpp>
#include <string>
#include <map>

class AssetManager {

private:
    std::map<std::string, sf::Texture> textures;
    std::map<std::string, sf::Font> fonts;

public:
    void LoadTexture(const std::string& name, const std::string& fileName);
    const sf::Texture& GetTexture(const std::string& name);

    void LoadFont(const std::string& name, const std::string& fileName);
    const sf::Font& GetFont(const std::string& name);
};

#endif // !ASSET_MANAGER_H
