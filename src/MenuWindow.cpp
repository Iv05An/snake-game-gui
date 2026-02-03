#include "MenuWindow.h"
#include "GameWindow.h"
#include <iostream>

MenuWindow::MenuWindow(sf::RenderWindow &_window)
    : window(_window)
    , startBtn("../../assets/textures/start_default.png",
               "../../assets/textures/start_hovered.png")
    , settingBtn("../../assets/textures/setting_default.png",
                 "../../assets/textures/setting_hovered.png")
    , exitBtn("../../assets/textures/exit_default.png",
                 "../../assets/textures/exit_hovered.png")
{
    if (!backgroundTexture.loadFromFile("../../assets/textures/menu_background.png")) {
        std::cerr << "ERROR: Failed to load menu_background.png" << std::endl;
        createFallbackBackground();
    } else {
        backgroundSprite.setTexture(backgroundTexture, true);
    }

    setupButtons();
}

void MenuWindow::createFallbackBackground() {
    window.clear(sf::Color(0, 0, 0, 0));
}

void MenuWindow::setupButtons() {
    auto surface = window.getSize();

    startBtn.getSprite().setScale(0.1f, 0.1f);
    sf::FloatRect startBtnBounds = startBtn.getSprite().getGlobalBounds();
    startBtn.getSprite().setPosition(
        surface.x / 2 - startBtnBounds.width / 2,
        surface.y / 2 - startBtnBounds.height / 2
    );

    settingBtn.getSprite().setScale(0.1f, 0.1f);
    sf::FloatRect settingBtnBounds = settingBtn.getSprite().getGlobalBounds();
    settingBtn.getSprite().setPosition(
        surface.x / 2 - settingBtnBounds.width / 2,
        surface.y / 2 - settingBtnBounds.height / 2 + 75
    );

    exitBtn.getSprite().setScale(0.1f, 0.1f);
    sf::FloatRect exitBtnBounds = exitBtn.getSprite().getGlobalBounds();
    exitBtn.getSprite().setPosition(
        surface.x / 2 - exitBtnBounds.width / 2,
        surface.y / 2 - exitBtnBounds.height / 2 + 150
        );
}

void MenuWindow::launchGame() {
    GameWindow game(window);
    game.run();
    window.close();
}

void MenuWindow::handleEvents() {
    sf::Event e;
    while(window.pollEvent(e)) {
        if(e.type == sf::Event::Closed) window.close();

        if(e.type == sf::Event::MouseButtonPressed) {
            if(e.mouseButton.button == sf::Mouse::Left) {
                if(startBtn.isMouseOver(window)) {
                    std::cout << "Launching game..." << std::endl;
                    launchGame();
                }
                if(exitBtn.isMouseOver(window)) {
                    std::cout << "Stoping game..." << std::endl;
                    window.close();
                }
            }

        }
    }
}

void MenuWindow::update() {
    startBtn.update(window);
    settingBtn.update(window);
    exitBtn.update(window);
}

void MenuWindow::draw() {
    window.clear(sf::Color(0, 0, 0, 0));
    /////
    window.draw(backgroundSprite);
    window.draw(startBtn.getSprite());
    window.draw(settingBtn.getSprite());
    window.draw(exitBtn.getSprite());
    /////
    window.display();
}

void MenuWindow::run() {
    while (window.isOpen()) {
        handleEvents();
        update();
        draw();
    }
}
