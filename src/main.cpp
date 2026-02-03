// #include <iostream>
// #include "../include/Game.h"

// int main() {
//     Game SnakeGame(20, 10);
//     SnakeGame.Run();
//     return 0;
// }

#include "GameWindow.h"
#include "MenuWindow.h"
#include <iostream>


int main() {
    //GameWindow game;
    //game.run();

    try {
        sf::RenderWindow window(sf::VideoMode({800, 600}), "Snake Game");

        sf::Image icon;
        if (icon.loadFromFile("../../assets/textures/logo.png")) {
            window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
        }

        MenuWindow menu(window);
        menu.run();

    } catch (const std::exception& e) {
        std::cerr << "Fatal error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
