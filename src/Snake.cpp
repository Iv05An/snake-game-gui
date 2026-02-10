#include "../include/Snake.h"
#include <iostream>

Snake::Snake()
{
    SnakeBody.clear();
    for (int i = 0; i<3; ++i)
    {
        SnakeSegment segment;
        segment.y = Constants::SNAKE_START_Y;
        segment.x = Constants::SNAKE_START_X - i * Constants::TILE_SIZE;

        segment.shape.setSize(sf::Vector2f(25, 25));
        if (i==0) segment.shape.setFillColor(Colors::SNAKE_HEAD);
        else segment.shape.setFillColor(Colors::SNAKE_BODY);
        segment.shape.setPosition(segment.x, segment.y);

        SnakeBody.push_back(segment);
    }

    direction=RIGHT;
    newDirection=RIGHT;
    collision=false;
}



void Snake::eating(std::vector<Food> &foods)
{
    // Получаем голову змейки
    int headX = SnakeBody[0].x;
    int headY = SnakeBody[0].y;
    
    // Проверяем все еды на поле
    for (size_t i = 0; i < foods.size(); ++i)
    {
        if (headX == foods[i].getX() && headY == foods[i].getY())
        {
            // Получаем хвост
            SnakeSegment tail = SnakeBody.back();
            
            // Создаем новый сегмент
            SnakeSegment newSegment;
            newSegment.x = tail.x;
            newSegment.y = tail.y;
            
            // Настраиваем графику нового сегмента
            newSegment.shape.setSize(sf::Vector2f(Constants::TILE_SIZE, Constants::TILE_SIZE));
            newSegment.shape.setFillColor(Colors::SNAKE_BODY);
            newSegment.shape.setPosition(newSegment.x, newSegment.y);
            
            // Добавляем новый сегмент
            SnakeBody.push_back(newSegment);
            
            // Удаляем съеденную еду
            foods.erase(foods.begin() + i);
            
            // Выходим, так как за один кадр съедаем только одну еду
            break;
        }
    }
}




bool Snake::CheckWallCollision()
{
    int HeadX = SnakeBody[0].x;
    int HeadY = SnakeBody[0].y;

    // if (HeadX<LEFT_BORDER+TILE_SIZE || HeadX>RIGTH_BORDER-TILE_SIZE || HeadY<TOP_BORDER+TILE_SIZE || HeadY>DOWN_BORDER-TILE_SIZE) return false;
    if (HeadX<Constants::LEFT_BORDER+Constants::TILE_SIZE || HeadX>Constants::RIGHT_BORDER-Constants::TILE_SIZE || HeadY<Constants::TOP_BORDER+Constants::TILE_SIZE || HeadY>Constants::BOTTOM_BORDER-Constants::TILE_SIZE) return false;

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
    case UP:    OldBody[0].y-=Constants::TILE_SIZE; break;
    case DOWN:  OldBody[0].y+=Constants::TILE_SIZE; break;
    case LEFT:  OldBody[0].x-=Constants::TILE_SIZE; break;
    case RIGHT: OldBody[0].x+=Constants::TILE_SIZE; break;
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