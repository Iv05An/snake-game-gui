#ifndef MENUBUTTON_H
#define MENUBUTTON_H
#include <SFML/Graphics.hpp>

class MenuButton {
private:
    sf::Sprite sprite;
    sf::Texture texture;
    sf::Texture hoverTexture;
    bool isHovered = false;

public:
    MenuButton(const std::string& normalPath, const std::string& hoverPath);

    void update(const sf::RenderWindow& window);

    sf::Sprite& getSprite();
    const sf::Sprite& getSprite() const;

    bool isMouseOver(const sf::RenderWindow& window) const;
};

#endif // MENUBUTTON_H
