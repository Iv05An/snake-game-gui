// GameWindow.cpp
#include "GameWindow.h"
#include <iostream>

GameWindow:: GameWindow(): window(sf::VideoMode(Constants::WINDOW_WIDTH, Constants::WINDOW_HEIGHT), "Snake") 
{
    window.setFramerateLimit(60);

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
    if (moveClock.getElapsedTime().asSeconds()>=Constants::SNAKE_MOVE_INTERVAL)
    {
        ObjSnake.move();
        ObjSnake.eating(foods);
        moveClock.restart();
    }
    if (foodClock.getElapsedTime().asSeconds()>=Constants::FOOD_GENERATION_INTERVAL && foods.size()<Constants::FOOD_GENERATION_INTERVAL)
    {
        Food cord_food = Food::generateFood(ObjSnake.getBody(), foods, Constants::FIELD_WIDTH, Constants::FIELD_HEIGHT);
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
    border.setSize(sf::Vector2f(Constants::FIELD_WIDTH, Constants::TILE_SIZE));
    border.setPosition(0, 0);
    window.draw(border);

    border.setPosition(0, Constants::BOTTOM_BORDER);
    window.draw(border);

    border.setSize(sf::Vector2f(Constants::TILE_SIZE, Constants::FIELD_HEIGHT));
    border.setPosition(0, 0);
    window.draw(border);

    border.setPosition(Constants::RIGHT_BORDER, 0);
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
        if (ObjSnake.CheckWallCollision() && !ObjSnake.getCollision()) update();
        else 
        {
            window.close();
            std::cout<<"GAME OVER";
            break;
        }
        render();
    }
}
