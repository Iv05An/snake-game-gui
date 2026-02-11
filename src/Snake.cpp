#include "Snake.h"
#include "ResourceManager.h"
#include <iostream>

Snake::Snake()
{    
    SnakeBody.clear();
    
    // Получаем менеджер ресурсов
    auto& rm = ResourceManager::getInstance();
    
    for (int i = 0; i < Constants::INITIAL_SNAKE_LENGTH; ++i)
    {
        SnakeSegment segment;
        segment.y = Constants::SNAKE_START_Y;
        segment.x = Constants::SNAKE_START_X - i * Constants::TILE_SIZE;

        // Создаем прямоугольник
        segment.shape.setSize(sf::Vector2f(Constants::TILE_SIZE, Constants::TILE_SIZE));
        segment.shape.setPosition(segment.x, segment.y);
        
        // Устанавливаем текстуру
        if (i == 0) {
            // Голова
            if (rm.hasTexture("snake_head")) {
                segment.shape.setTexture(&rm.getTexture("snake_head"));
            } else {
                segment.shape.setFillColor(Colors::SNAKE_HEAD);
                std::cout << "    WARNING: Using color for head (texture not found)" << std::endl;
            }
        } else {
            // Тело
            if (rm.hasTexture("snake_body")) {
                segment.shape.setTexture(&rm.getTexture("snake_body"));
            } else {
                segment.shape.setFillColor(Colors::SNAKE_BODY);
                std::cout << "    WARNING: Using color for body (texture not found)" << std::endl;
            }
        }
        
        SnakeBody.push_back(segment);
    }

    direction = RIGHT;
    newDirection = RIGHT;
    collision = false;
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
            
            // Устанавливаем текстуру для нового сегмента
            auto& rm = ResourceManager::getInstance();
            if (rm.hasTexture("snake_body")) {
                newSegment.shape.setTexture(&rm.getTexture("snake_body"));
            } else {
                newSegment.shape.setFillColor(Colors::SNAKE_BODY);
            }
            
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
    if (SnakeBody.empty()) {
        std::cout << "WARNING: Snake body is empty in CheckWallCollision!" << std::endl;
        return false;
    }
    
    int HeadX = SnakeBody[0].x;
    int HeadY = SnakeBody[0].y;

    // Проверяем, вышла ли голова за границы
    if (HeadX < Constants::LEFT_BORDER + Constants::TILE_SIZE || 
        HeadX > Constants::RIGHT_BORDER - Constants::TILE_SIZE || 
        HeadY < Constants::TOP_BORDER + Constants::TILE_SIZE || 
        HeadY > Constants::BOTTOM_BORDER - Constants::TILE_SIZE) 
    {
        std::cout << "WALL COLLISION DETECTED!" << std::endl;
        std::cout << "  Head position: (" << HeadX << ", " << HeadY << ")" << std::endl;
        std::cout << "  Valid range: X[" << Constants::LEFT_BORDER + Constants::TILE_SIZE 
                  << " - " << Constants::RIGHT_BORDER - Constants::TILE_SIZE << "]" << std::endl;
        std::cout << "  Valid range: Y[" << Constants::TOP_BORDER + Constants::TILE_SIZE 
                  << " - " << Constants::BOTTOM_BORDER - Constants::TILE_SIZE << "]" << std::endl;
        return false;
    }

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
    case UP:    OldBody[0].y -= Constants::TILE_SIZE; break;
    case DOWN:  OldBody[0].y += Constants::TILE_SIZE; break;
    case LEFT:  OldBody[0].x -= Constants::TILE_SIZE; break;
    case RIGHT: OldBody[0].x += Constants::TILE_SIZE; break;
    default: break;
    }
        
    collision = false;
    for (int i = 1; i < SnakeBody.size(); i++) {
        if (OldBody[i].x == OldBody[0].x && OldBody[i].y == OldBody[0].y) {
            collision = true;
            std::cout << "SELF COLLISION DETECTED!" << std::endl;
            break;
        }    
    }
                
    // Если столкновения нет — двигаем
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

    //поворот головы
    switch (direction)
    {
    case UP:
        SnakeBody[0].shape.setRotation(180);
        SnakeBody[0].shape.setPosition(SnakeBody[0].shape.getPosition().x+Constants::TILE_SIZE, SnakeBody[0].shape.getPosition().y+Constants::TILE_SIZE);
        break;
    case DOWN:
        SnakeBody[0].shape.setRotation(0);
        SnakeBody[0].shape.setPosition(SnakeBody[0].shape.getPosition().x, SnakeBody[0].shape.getPosition().y);
        break;
    case LEFT:
        SnakeBody[0].shape.setRotation(90);
        SnakeBody[0].shape.setPosition(SnakeBody[0].shape.getPosition().x+Constants::TILE_SIZE, SnakeBody[0].shape.getPosition().y);
        break;
    case RIGHT:
        SnakeBody[0].shape.setRotation(270);
        SnakeBody[0].shape.setPosition(SnakeBody[0].shape.getPosition().x, SnakeBody[0].shape.getPosition().y+Constants::TILE_SIZE);
        break;
    default:
        break;
    }
}