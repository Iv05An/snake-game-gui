// GameWindow.cpp
#include "GameWindow.h"
#include <iostream>

GameWindow:: GameWindow(): window(sf::VideoMode(800, 600), "Snake") 
{
    window.setFramerateLimit(60);

    FIELD_WIDTH = 800;
    FIELD_HEIGHT = 600;

    LEFT_BORDER = 0;
    RIGTH_BORDER = FIELD_WIDTH - TILE_SIZE;
    TOP_BORDER = 0;
    DOWN_BORDER = FIELD_HEIGHT - TILE_SIZE;

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
                if (ObjSnake.getDirection()!=DOWN)
                    {
                        ObjSnake.setNewDirection(UP);
                    }
                // Snake.setDirection(UP);
                break;
            case sf::Keyboard::S:
            case sf::Keyboard::Down:
                if (ObjSnake.getDirection()!=UP)
                    {
                        ObjSnake.setNewDirection(DOWN);
                    }
                // Snake.setDirection(DOWN);
                break;
            case sf::Keyboard::A:
            case sf::Keyboard::Left:
                if (ObjSnake.getDirection()!=RIGHT)
                    {
                        ObjSnake.setNewDirection(LEFT);
                    }
                // Snake.setDirection(LEFT);
                break;
            case sf::Keyboard::D:
            case sf::Keyboard::Right:
                if (ObjSnake.getDirection()!=LEFT)
                    {
                        ObjSnake.setNewDirection(RIGHT);
                    }
                // Snake.setDirection(RIGHT);
                break;
            default:
                break;
            }

        }
    }


}


void GameWindow::update()
{
    if (moveClock.getElapsedTime().asSeconds()>=moveInterval)
    {
        ObjSnake.move();
        ObjSnake.eating(foods);
        moveClock.restart();
    }
    if (foodClock.getElapsedTime().asSeconds()>=foodInterval && foods.size()<LIMIT_FOODS)
    {
        Food cord_food = Food::generateFood(ObjSnake.getBody(), foods, FIELD_WIDTH, FIELD_HEIGHT);
        foods.push_back(cord_food);
        foodClock.restart();
    }
}
void GameWindow::drawSnake()
{
    std::vector<SnakeSegment> SnakeBody = ObjSnake.getBody();
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
        if (ObjSnake.CheckWallCollision(LEFT_BORDER, RIGTH_BORDER, TOP_BORDER, DOWN_BORDER) && !ObjSnake.getCollision()) update();
        else 
        {
            window.close();
            std::cout<<"GAME OVER";
            break;
        }
        render();
    }
}
