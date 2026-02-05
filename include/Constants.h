// Constants.h
#ifndef CONSTANTS_H
#define CONSTANTS_H

namespace Constants
{
    // Окно (известно при компиляции - используем constexpr)
    constexpr int WINDOW_WIDTH = 800;
    constexpr int WINDOW_HEIGHT = 600;
    
    // Игровой мир
    constexpr int TILE_SIZE = 25;           // Размер клетки
    constexpr int FIELD_WIDTH = 800;        // Ширина поля в пикселях
    constexpr int FIELD_HEIGHT = 600;       // Высота поля в пикселях
    
    // Вычисляемые границы (тоже constexpr)
    constexpr int LEFT_BORDER = 0;
    constexpr int RIGHT_BORDER = FIELD_WIDTH - TILE_SIZE;
    constexpr int TOP_BORDER = 0;
    constexpr int BOTTOM_BORDER = FIELD_HEIGHT - TILE_SIZE;
    
    // Змейка
    constexpr int INITIAL_SNAKE_LENGTH = 3;
    constexpr int SNAKE_START_X = 100;
    constexpr int SNAKE_START_Y = 50;
    
    // Еда
    constexpr int MAX_FOOD_COUNT = 5;       // Максимум еды на поле
    constexpr int FOOD_GENERATION_INTERVAL = 5; // Секунды между появлением
    
    // Время (не constexpr, т.к. float, но const)
    const float SNAKE_MOVE_INTERVAL = 0.2f; // Секунды между движениями
}

#endif