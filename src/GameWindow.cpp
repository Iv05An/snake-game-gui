#include "GameWindow.h"
#include "ResourceManager.h"
#include <iostream>
#include <fstream>

GameWindow::GameWindow() : 
    window(sf::VideoMode(Constants::WINDOW_WIDTH, Constants::WINDOW_HEIGHT), "Snake"),
    currentState(gameState::PLAYING)
{    
    // 1. Настройка окна
    window.setFramerateLimit(60);
    // 2. Загрузка всех ресурсов ПЕРВЫМ делом
    loadResources();
    // 3. Инициализация игровых объектов ПОСЛЕ загрузки ресурсов
    initializeGameObjects();
}

void GameWindow::loadResources()
{
    auto& rm = ResourceManager::getInstance();

    std::vector<std::pair<std::string, std::string>> assets = {
        {"apple", "assets/textures/apple.png"},
        {"snake_head", "assets/textures/snake_head.png"},
        {"snake_body", "assets/textures/snake_body.png"}
    };
    
    for (const auto& [name, path] : assets) {
        std::ifstream file(path);
        if (file.good()) {
            std::cout << "  ✓ Found: " << path << std::endl;
        } else {
            std::cout << "  ✗ MISSING: " << path << std::endl;
            std::cout << "    Current dir: ";
            system("cd"); //показывает текущую дирректорию в консоли
        }
        file.close();
    }

    // загрузка текстур
    bool allTexturesLoaded = true;
    
    for (const auto& [name, path] : assets) {
        if (rm.loadTexture(name, path)) {
            std::cout << "  ✓ Loaded: " << name << std::endl;

        } else {
            std::cout << "  ✗ FAILED: " << name << std::endl;
            allTexturesLoaded = false;
        }
    }
    
    if (!allTexturesLoaded) {
        std::cout << "WARNING: Some textures failed to load!" << std::endl;
        std::cout << "Using placeholder textures instead." << std::endl;
    }
    
}

void GameWindow::initializeGameObjects()
{    
    // 3.1 Создаем змейку ПОСЛЕ загрузки ресурсов
    objSnake = std::make_unique<Snake>();
    // 3.2 Генерируем первую еду
    if (foods.empty()) {
        Food newFood = Food::generateFood(objSnake->getBody(), foods,
                                         Constants::FIELD_WIDTH, Constants::FIELD_HEIGHT);
        foods.push_back(newFood);
    }
}

void GameWindow::handleEvents() {
    sf::Event e;
    while(window.pollEvent(e)) {
        if(e.type == sf::Event::Closed) {
            window.close();
        }

        if (e.type == sf::Event::KeyPressed)
        {
            Direction currentDir = objSnake->getDirection();
            Direction newDir = NONE;
            
            switch (e.key.code)
            {
            case sf::Keyboard::W:
            case sf::Keyboard::Up:
                newDir = UP;
                break;
            case sf::Keyboard::S:
            case sf::Keyboard::Down:
                newDir = DOWN;
                break;
            case sf::Keyboard::A:
            case sf::Keyboard::Left:
                newDir = LEFT;
                break;
            case sf::Keyboard::D:
            case sf::Keyboard::Right:
                newDir = RIGHT;
                break;
            case sf::Keyboard::Escape:
                window.close();
                break;
            default:
                break;
            }
            
            // Проверяем, можно ли сменить направление
            if (newDir != NONE) {
                bool canChange = true;
                
                if ((newDir == UP && currentDir == DOWN) ||
                    (newDir == DOWN && currentDir == UP) ||
                    (newDir == LEFT && currentDir == RIGHT) ||
                    (newDir == RIGHT && currentDir == LEFT)) {
                    canChange = false;
                }
                
                if (canChange) {
                    objSnake->setNewDirection(newDir);
                }
            }
        }
    }
}

void GameWindow::update()
{
    if (moveClock.getElapsedTime().asSeconds() >= Constants::SNAKE_MOVE_INTERVAL)
    {
        objSnake->move();
        objSnake->eating(foods);
        moveClock.restart();
    }
    
    if (foodClock.getElapsedTime().asSeconds() >= Constants::FOOD_GENERATION_INTERVAL && 
        foods.size() < Constants::MAX_FOOD_COUNT)
    {
        Food cord_food = Food::generateFood(objSnake->getBody(), foods, 
                                           Constants::FIELD_WIDTH, Constants::FIELD_HEIGHT);
        foods.push_back(cord_food);
        foodClock.restart();
    }
}

void GameWindow::drawSnake()
{
    const auto& snakeBody = objSnake->getBody();
    
    static bool debugPrinted = false;
    if (!debugPrinted && !snakeBody.empty()) {
        for (size_t i = 0; i < snakeBody.size(); ++i) {
            const auto& segment = snakeBody[i];
        }
        debugPrinted = true;
    }
    
    for (const SnakeSegment &segment: snakeBody)
    {
        window.draw(segment.shape);
    }
}

void GameWindow::drawBorder()
{
    sf::RectangleShape border;
    border.setFillColor(Colors::BORDER);
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
        window.draw(food.getSprite());
    }
}

void GameWindow::render()
{
    window.clear(Colors::BACKGROUND);
    drawSnake();
    drawBorder();
    drawFoods();
    window.display();
}

void GameWindow::run()
{
    while(window.isOpen()) {
        handleEvents();
        // Проверяем коллизию со стенами
        bool wallOk = objSnake->CheckWallCollision();
        bool selfOk = !objSnake->getCollision();
        
        if (wallOk && selfOk) {
            update();
            render();
        } else {
            window.close();
            break;
        }
    }
}