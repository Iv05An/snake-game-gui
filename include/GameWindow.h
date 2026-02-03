// GameWindow.h
#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H
#include <SFML/Graphics.hpp>
#include <vector>

#include <iostream>
#include <windows.h>
#include "Snake.h"
#include "Utils.h"

class GameWindow {
    sf::RenderWindow window;
struct SnakeSegment
{
    sf::RectangleShape shape;
    int x, y;
};
private:
    gameState currentState;
    // int width, height;

    Direction direction;
    Direction newDirection;

    sf::Clock moveClock;
    const float moveInterval = 0.2;



    std::vector<SnakeSegment> SnakeBody;

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



    void initializeSnake();
    void drawSnake();
    void render();
    void move();
public:
    GameWindow();
    void run();
private:
    void handleEvents();
    int gameLoop(gameState &currentState);
    void update();
    
};
#endif