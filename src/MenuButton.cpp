#include <MenuButton.h>
#include <iostream>

MenuButton::MenuButton(const std::string& normalPath, const std::string& hoverPath) {
    if (!texture.loadFromFile(normalPath)) {
        throw std::runtime_error("Failed to load texture: " + normalPath);
    }

    if (!hoverTexture.loadFromFile(hoverPath)) {
        std::cout << "Warning: Hover texture not found: " << hoverPath << std::endl;
        hoverTexture = texture;
    }

    sprite.setTexture(texture);
}

void MenuButton::update(const sf::RenderWindow& window) {
    sf::Vector2i mousePixelPos = sf::Mouse::getPosition(window);
    sf::Vector2f mouseWorldPos = window.mapPixelToCoords(mousePixelPos);

    bool wasHovered = isHovered;
    isHovered = sprite.getGlobalBounds().contains(mouseWorldPos);

    if (isHovered != wasHovered) {
        if (isHovered) {
            sprite.setTexture(hoverTexture, true);
        } else {
            sprite.setTexture(texture, true);
        }
    }
}

sf::Sprite& MenuButton::getSprite() { return sprite; }
const sf::Sprite& MenuButton::getSprite() const { return sprite; }

bool MenuButton::isMouseOver(const sf::RenderWindow& window) const {
    sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
    return sprite.getGlobalBounds().contains(mousePos);
}
