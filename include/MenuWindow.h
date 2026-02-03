#ifndef MENUWINDOW_H
#define MENUWINDOW_H
#include "MenuButton.h"
#include <SFML/Graphics.hpp>

class MenuWindow {
private:
    sf::RenderWindow& window;
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
    MenuButton startBtn;
    MenuButton settingBtn;
    MenuButton exitBtn;

public:
    explicit MenuWindow(sf::RenderWindow &_window);

private:
    void createFallbackBackground();
    void setupButtons();
    void launchGame();

public:
    void handleEvents();
    void update();
    void draw();
    void run();
};

#endif // MENUWINDOW_H
