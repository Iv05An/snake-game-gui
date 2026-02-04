
#include "../include/Food.h"
#include <cstdlib>

Food::Food(int xPos, int yPos): x(xPos), y(yPos) {}

bool Food::isFoodAt(const std::vector<Food> &foods, int checkX, int checkY) //временно как вспомогательная функция
{
    for (const Food &FoodPos: foods)
    {
        if (FoodPos.x==checkX && FoodPos.y==checkY) return true;
        // if (FoodPos.getX()==checkX && FoodPos.getY()==checkY) return true;
    }
    return false;
}

Food Food::generateFood(const std::vector<SnakeSegment> &SnakeBody, const std::vector<Food> &foods, const int& width, const int& height)
{
    int foodX, foodY;
    bool valid = false;
    while (!valid)
    {
        const int TILE_SIZE = 25; //временно (из-за static)
        valid = true;
        foodX = TILE_SIZE + TILE_SIZE*(rand() % ((width - 2 * TILE_SIZE) / TILE_SIZE));   // от 1 до width-2
        foodY = TILE_SIZE + TILE_SIZE*(rand() % ((height - 2 * TILE_SIZE) / TILE_SIZE));  // от 1 до height-2
            
        for (int j=0; j<SnakeBody.size(); j++)
        {
            if (foodX == SnakeBody[j].x && foodY == SnakeBody[j].y) 
            {
                valid = false;
                continue;
            }
        }

        if (valid)
        {
            for (const auto &food: foods)
            {
                if (food.x == foodX && food.y == foodY) valid = false;
            }
        }
    }   
    return  Food(foodX, foodY);   
}

sf::RectangleShape Food::ShapeFood()
{
    ElemFood.setFillColor(sf::Color::Yellow);
    ElemFood.setSize(sf::Vector2f(TILE_SIZE, TILE_SIZE));
    ElemFood.setPosition(x, y);

    return ElemFood;
}
