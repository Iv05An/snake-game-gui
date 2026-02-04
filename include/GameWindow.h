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
    const float foodInterval = 5.0;
    const float moveInterval = 0.2;

    //food
    std::vector<Food> foods;

    //snake
    Snake ObjSnake;
    //border
    const int TILE_SIZE = 25;
    int FIELD_WIDTH;
    int FIELD_HEIGHT;

    int LEFT_BORDER;
    int RIGTH_BORDER;
    int TOP_BORDER;
    int DOWN_BORDER;

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