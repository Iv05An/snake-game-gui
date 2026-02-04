// GameWindow.cpp
#include "GameWindow.h"
#include <iostream>


void GameWindow::initializeSnake()
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
}
GameWindow:: GameWindow(): window(sf::VideoMode(800, 600), "Snake") 
{
    window.setFramerateLimit(60);
    initializeSnake();
    // width=800;
    // height=600;
    FIELD_WIDTH = 800;
    FIELD_HEIGHT = 600;

    LEFT_BORDER = 0;
    RIGTH_BORDER = FIELD_WIDTH - TILE_SIZE;
    TOP_BORDER = 0;
    DOWN_BORDER = FIELD_HEIGHT - TILE_SIZE;

    direction=RIGHT;
    newDirection=RIGHT;

}

bool GameWindow::CheckWallCollision()
{
    int HeadX = SnakeBody[0].x;
    int HeadY = SnakeBody[0].y;

    if (HeadX<LEFT_BORDER+TILE_SIZE || HeadX>RIGTH_BORDER-TILE_SIZE || HeadY<TOP_BORDER+TILE_SIZE || HeadY>DOWN_BORDER-TILE_SIZE) return false;
    return true;
}

void GameWindow::handleEvents() {
    sf::Event e;
    while(window.pollEvent(e)) {
        if(e.type == sf::Event::Closed) window.close();


        if (e.type==sf::Event::KeyPressed)
        {
            switch (e.key.code)
            {
            case sf::Keyboard::W:
            case sf::Keyboard::Up:
                if (direction!=DOWN)
                    {
                        newDirection=UP;
                    }
                // Snake.setDirection(UP);
                break;
            case sf::Keyboard::S:
            case sf::Keyboard::Down:
                if (direction!=UP)
                    {
                        newDirection=DOWN;
                    }
                // Snake.setDirection(DOWN);
                break;
            case sf::Keyboard::A:
            case sf::Keyboard::Left:
                if (direction!=RIGHT)
                    {
                        newDirection=LEFT;
                    }
                // Snake.setDirection(LEFT);
                break;
            case sf::Keyboard::D:
            case sf::Keyboard::Right:
                if (direction!=LEFT)
                    {
                        newDirection=RIGHT;
                    }
                // Snake.setDirection(RIGHT);
                break;
            default:
                break;
            }

        }
    }


}

void GameWindow::eating(std::vector<Food> &foods) // можно будет улучшить логику поедания в SnakeBody.push_back({shape, tail.x, tail.y});
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
                SnakeBody.push_back({shape, tail.x, tail.y});

                foods.erase(foods.begin()+i);
                --i;
                break;
            }
        }
        
    }

void GameWindow::move()
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



void GameWindow::update()
{
    if (moveClock.getElapsedTime().asSeconds()>=moveInterval)
    {
        move();
        eating(foods);
        moveClock.restart();
    }
    if (foodClock.getElapsedTime().asSeconds()>=foodInterval && foods.size()<LIMIT_FOODS)
    {
        Food cord_food = Food::generateFood(SnakeBody, foods, FIELD_WIDTH, FIELD_HEIGHT);
        foods.push_back(cord_food);
        foodClock.restart();
    }
}
void GameWindow::drawSnake()
{
    for (SnakeSegment &segment: SnakeBody)
    {
        window.draw(segment.shape);
    }
}

void GameWindow::drawBorder()
{
    sf::RectangleShape border;
    border.setFillColor(sf::Color::Red);
    border.setSize(sf::Vector2f(FIELD_WIDTH, TILE_SIZE));
    border.setPosition(0, 0);
    window.draw(border);

    border.setPosition(0, DOWN_BORDER);
    window.draw(border);

    border.setSize(sf::Vector2f(TILE_SIZE, FIELD_HEIGHT));
    border.setPosition(0, 0);
    window.draw(border);

    border.setPosition(RIGTH_BORDER, 0);
    window.draw(border);
}

void GameWindow::drawFoods()
{
    for (auto &food: foods)
    {
        sf::RectangleShape Shape = food.ShapeFood();
        window.draw(Shape);
    }
}

void GameWindow::render()
{
    window.clear(sf::Color::Black);
    drawSnake();
    drawBorder();
    drawFoods();
    window.display();
}



void GameWindow::run() {
    while(window.isOpen()) {
        handleEvents();
        if (CheckWallCollision() && !collision) update();
        else 
        {
            window.close();
            std::cout<<"GAME OVER";
            break;
        }
        render();
    }
}
