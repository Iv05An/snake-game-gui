// GameWindow.h
#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H
#include <SFML/Graphics.hpp>
#include <vector>

#include <iostream>
#include <windows.h>
#include "Snake.h"
#include "Utils.h"
#include "segment.h"
#include "Food.h"

class GameWindow {
    sf::RenderWindow window;

private:
    gameState currentState;

    sf::Clock moveClock;
    sf::Clock foodClock;


    //food
    std::vector<Food> foods;

    //snake
    Snake ObjSnake;

    void handleEvents();

    void drawBorder();
    void drawFoods();
    void drawSnake();
    void update();
    void render();

    
public:
    GameWindow();
    void run();
    
};
#endif