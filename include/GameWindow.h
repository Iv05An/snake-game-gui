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
// struct SnakeSegment
// {
//     sf::RectangleShape shape;
//     int x, y;
// };
private:
    gameState currentState;
    // int width, height;
    bool collision;

    Direction direction;
    Direction newDirection;

    sf::Clock moveClock;
    sf::Clock foodClock;
    const float foodInterval = 5.0;
    const float moveInterval = 0.2;



    std::vector<SnakeSegment> SnakeBody;

    //food
    std::vector<Food> foods;
    //border
    const int TILE_SIZE = 25;
    int FIELD_WIDTH;
    int FIELD_HEIGHT;

    int LEFT_BORDER;
    int RIGTH_BORDER;
    int TOP_BORDER;
    int DOWN_BORDER;

    bool CheckWallCollision();
    void drawBorder();

    void drawFoods();
    void initializeSnake();
    void drawSnake();
    void render();
    void move();
    
public:
    GameWindow();
    void run();
    void eating(std::vector<Food> &foods);
    const bool truthCollision() const {return collision;};
private:
    void handleEvents();
    // int gameLoop(gameState &currentState);
    void update();
    
};
#endif