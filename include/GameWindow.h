#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>  // для unique_ptr
#include "Snake.h"
#include "Utils.h"
#include "segment.h"
#include "Food.h"

class GameWindow {
private:
    // 1. Окно и SFML объекты
    sf::RenderWindow window;
    gameState currentState;
    sf::Clock moveClock;
    sf::Clock foodClock;

    // 2. Ресурсы
    // (ResourceManager - singleton, не член класса)
    
    // 3. Игровые объекты - УКАЗАТЕЛИ для контроля времени создания
    std::unique_ptr<Snake> objSnake;  // указатель вместо объекта
    std::vector<Food> foods;          // вектор можно оставить

    void handleEvents();
    void drawBorder();
    void drawFoods();
    void drawSnake();
    void update();
    void render();
    
    // Методы для инициализации
    void loadResources();
    void initializeGameObjects();

public:
    GameWindow();
    void run();
};

#endif