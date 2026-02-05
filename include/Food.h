#ifndef FOOD_H
#define FOOD_H
#include <vector>
#include "segment.h"
#include <SFML/Graphics.hpp>
#include "Constants.h" 
#include "ColorPalette.h"
// #define LIMIT_FOODS 5 // временно

class Food
{
    private:
        int x, y;
        // int TILE_SIZE = 25;
        sf::RectangleShape ElemFood;
    public:
        Food(int xPos, int yPos);

        static bool isFoodAt(const std::vector<Food> &foods, int checkX, int checkY);

        static Food generateFood(const std::vector<SnakeSegment> &SnakeBody, const std::vector<Food> &foods, const int& width, const int& height);
        // Food generateFood(const std::vector<SnakeSegment> &SnakeBody, const std::vector<Food> &foods, const int& width, const int& height);

        sf::RectangleShape ShapeFood();

        
        int getX() const {return x;}
        int getY() const {return y;}

};

// bool isFoodAt(const std::vector<Food> &foods, int checkX, int checkY);

#endif