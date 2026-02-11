#ifndef SNAKE_H
#define SNAKE_H
#include "segment.h"
#include "Food.h"
#include "Constants.h"
#include "ColorPalette.h" 
#include <vector>
#include <conio.h>
#include <windows.h>

enum Direction
{
    UP, DOWN, LEFT, RIGHT, NONE
};

class Snake
{
private:
    std::vector<SnakeSegment> SnakeBody;
    bool collision;
    Direction direction;
    Direction newDirection;

public:
    Snake();
    void move();
    void eating(std::vector<Food> &foods);
    const std::vector<SnakeSegment>& getBody() const {return SnakeBody;};
    bool CheckWallCollision();
    const bool truthCollision() const {return collision;};
    Direction getDirection() const {return direction;}
    Direction getNewDirection() const {return newDirection;}
    void setDirection(Direction inpDirection) {direction=inpDirection;}
    void setNewDirection(Direction inpNewDirection) {newDirection=inpNewDirection;}
    bool getCollision() const {return collision;}
};

#endif