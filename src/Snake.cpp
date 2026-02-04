#include "../include/Snake.h"
#include <iostream>

Snake::Snake()
{
    SnakeBody.clear();
    for (int i = 0; i<3; ++i)
    {
        SnakeSegment segment;
        segment.y = 50;
        segment.x = 100 - i * 25;

        segment.shape.setSize(sf::Vector2f(25, 25));
        if (i==0) segment.shape.setFillColor(sf::Color::Green);
        else segment.shape.setFillColor(sf::Color(0, 180, 0));
        segment.shape.setPosition(segment.x, segment.y);

        SnakeBody.push_back(segment);
    }

    direction=RIGHT;
    newDirection=RIGHT;
    collision=false;
}



void Snake::eating(std::vector<Food> &foods) // можно будет улучшить логику поедания в SnakeBody.push_back({shape, tail.x, tail.y});
    {
        SnakeSegment tail= SnakeBody.back();
        for (int i = 0; i<foods.size(); ++i)
        {
            if (SnakeBody[0].x==foods[i].getX() && SnakeBody[0].y==foods[i].getY())
            {
                sf::RectangleShape shape;
                shape.setFillColor(sf::Color(0, 180, 0));
                shape.setSize(sf::Vector2f(TILE_SIZE, TILE_SIZE));
                shape.setPosition(tail.x, tail.y);

                SnakeSegment newSegment;
                newSegment.shape = shape;
                newSegment.x = tail.x;
                newSegment.y = tail.y;
                SnakeBody.push_back(newSegment);

                foods.erase(foods.begin()+i);
                --i;
                break;
            }
        }
        
    }



bool Snake::CheckWallCollision(int &LEFT_BORDER, int &RIGTH_BORDER, int &TOP_BORDER, int &DOWN_BORDER)
{
    int HeadX = SnakeBody[0].x;
    int HeadY = SnakeBody[0].y;

    if (HeadX<LEFT_BORDER+TILE_SIZE || HeadX>RIGTH_BORDER-TILE_SIZE || HeadY<TOP_BORDER+TILE_SIZE || HeadY>DOWN_BORDER-TILE_SIZE) return false;
    return true;
}


void Snake::move()
{
    // Обновляем направление
    direction = newDirection;
    
    // Проверяем, можно ли двигаться в этом направлении
    if (direction == NONE) return;
    

    std::vector<SnakeSegment> OldBody = SnakeBody;
    
    switch (direction)
    {
    case UP:    OldBody[0].y-=25; break;
    case DOWN:  OldBody[0].y+=25; break;
    case LEFT:  OldBody[0].x-=25; break;
    case RIGHT: OldBody[0].x+=25; break;
    default: break;
    }
        
    collision = false;
    for (int i = 1; i < SnakeBody.size(); i++) {
        //if ((OldBody[i].x - OldBody[0].x) == TILE_SIZE && (OldBody[i].y - OldBody[0].y) == TILE_SIZE) {
        if (OldBody[i].x == OldBody[0].x && OldBody[i].y == OldBody[0].y) {
            collision = true;
            break;
        }    
    }
                
    // 3. Если столкновения нет — двигаем
    if (!collision) {               
        for (int i = SnakeBody.size()-1; i>0; i--)
        {
            SnakeBody[i].x = SnakeBody[i-1].x;
            SnakeBody[i].y = SnakeBody[i-1].y;
            SnakeBody[i].shape.setPosition(SnakeBody[i].x, SnakeBody[i].y);
        }
        
        SnakeBody[0].x = OldBody[0].x;
        SnakeBody[0].y = OldBody[0].y;
        SnakeBody[0].shape.setPosition(SnakeBody[0].x, SnakeBody[0].y);
    }
        
    
}