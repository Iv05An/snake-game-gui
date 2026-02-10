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
        // sf::RectangleShape ElemFood;
        sf::Sprite sprite;
        std::string textureName;
    public:
        Food(int xPos, int yPos, const std::string& texName="apple");

        static bool isFoodAt(const std::vector<Food> &foods, int checkX, int checkY);

        static Food generateFood(const std::vector<SnakeSegment> &SnakeBody, const std::vector<Food> &foods, const int& width, const int& height);
        // Food generateFood(const std::vector<SnakeSegment> &SnakeBody, const std::vector<Food> &foods, const int& width, const int& height);

        sf::RectangleShape ShapeFood();

        // Отрисовка
        void draw(sf::RenderWindow& window);
        
        int getX() const {return x;}
        int getY() const {return y;}
        sf::Sprite& getSprite() { return sprite; }
        const sf::Sprite& getSprite() const { return sprite; }
        // Обновление позиции спрайта
        void updateSpritePosition();
        
        // Установка текстуры (можно менять тип еды)
        void setTexture(const std::string& texName);
};

// bool isFoodAt(const std::vector<Food> &foods, int checkX, int checkY);

#endif