
// Food.cpp
#include "Food.h"
#include "ResourceManager.h"  // <-- Важно!
#include <cstdlib>
#include <iostream>

// Конструктор
Food::Food(int xPos, int yPos, const std::string& texName) : 
    x(xPos), y(yPos), textureName(texName)
{
    // Получаем менеджер ресурсов
    auto& rm = ResourceManager::getInstance();
    
    // Устанавливаем текстуру спрайту
    sprite.setTexture(rm.getTexture(textureName));
    
    // Настраиваем спрайт
    sf::Vector2u texSize = sprite.getTexture()->getSize();
    
    // Масштабируем под размер клетки
    float scaleX = static_cast<float>(Constants::TILE_SIZE) / texSize.x;
    float scaleY = static_cast<float>(Constants::TILE_SIZE) / texSize.y;
    sprite.setScale(scaleX, scaleY);
    
    // Устанавливаем позицию
    updateSpritePosition();
    
    // Центрируем (если текстура не точно 25x25)
    sprite.setOrigin(texSize.x / 2.0f, texSize.y / 2.0f);
    sprite.setPosition(x + Constants::TILE_SIZE / 2.0f, 
                       y + Constants::TILE_SIZE / 2.0f);
}

// Обновление позиции спрайта
void Food::updateSpritePosition()
{
    // Простая установка позиции (без центрирования)
    sprite.setPosition(static_cast<float>(x), static_cast<float>(y));
}

// Отрисовка еды
void Food::draw(sf::RenderWindow& window)
{
    window.draw(sprite);
}

// Установка новой текстуры
void Food::setTexture(const std::string& texName)
{
    textureName = texName;
    auto& rm = ResourceManager::getInstance();
    
    if (!rm.hasTexture(textureName))
    {
        rm.loadTexture(textureName, "assets/textures/" + textureName + ".png");
    }
    
    sprite.setTexture(rm.getTexture(textureName));
    updateSpritePosition();
}

// Статические методы (остаются как были, но с небольшими изменениями)
bool Food::isFoodAt(const std::vector<Food>& foods, int checkX, int checkY)
{
    for (const Food& food : foods)
    {
        if (food.x == checkX && food.y == checkY)
            return true;
    }
    return false;
}

Food Food::generateFood(const std::vector<SnakeSegment>& SnakeBody, 
                       const std::vector<Food>& foods, 
                       const int& width, const int& height)
{
    int foodX, foodY;
    bool valid = false;
    
    // Защита от бесконечного цикла
    int maxAttempts = 1000;
    int attempts = 0;
    
    // Генерация случайной позиции
    while (!valid && attempts < maxAttempts)
    {
        attempts++;
        valid = true;
        
        // Генерируем позицию в клетках
        int gridWidth = (width - 2 * Constants::TILE_SIZE) / Constants::TILE_SIZE;
        int gridHeight = (height - 2 * Constants::TILE_SIZE) / Constants::TILE_SIZE;
        
        int gridX = rand() % gridWidth;
        int gridY = rand() % gridHeight;
        
        foodX = Constants::TILE_SIZE + gridX * Constants::TILE_SIZE;
        foodY = Constants::TILE_SIZE + gridY * Constants::TILE_SIZE;
        
        // Проверяем столкновение со змейкой
        for (const auto& segment : SnakeBody)
        {
            if (segment.x == foodX && segment.y == foodY)
            {
                valid = false;
                break;
            }
        }
        
        // Проверяем столкновение с другой едой
        if (valid)
        {
            for (const auto& food : foods)
            {
                if (food.getX() == foodX && food.getY() == foodY)
                {
                    valid = false;
                    break;
                }
            }
        }
    }
    
    // Если не нашли свободную позицию за maxAttempts попыток
    if (!valid)
    {
        // Возвращаем еду в начальную позицию или обрабатываем ошибку
        std::cerr << "WARNING: Could not find free spot for food!" << std::endl;
        foodX = Constants::TILE_SIZE;
        foodY = Constants::TILE_SIZE;
    }
    
    // Можно добавить случайный выбор текстуры для разнообразия
    std::string textureName = "apple";
    
    return Food(foodX, foodY, textureName);
}

// sf::RectangleShape Food::ShapeFood()
// {
//     ElemFood.setFillColor(Colors::FOOD);
//     ElemFood.setSize(sf::Vector2f(Constants::TILE_SIZE, Constants::TILE_SIZE));
//     ElemFood.setPosition(x, y);

//     return ElemFood;
// }
