// ColorPalette.h
#ifndef COLOR_PALETTE_H
#define COLOR_PALETTE_H

#include <SFML/Graphics/Color.hpp>

namespace Colors
{
    // SFML уже делает цвета constexpr, но мы оборачиваем для единообразия
    
    // Змейка
    const sf::Color SNAKE_HEAD = sf::Color(0, 255, 0);      // #00FF00
    const sf::Color SNAKE_BODY = sf::Color(0, 180, 0);      // #00B400
    
    // Еда
    const sf::Color FOOD = sf::Color::Yellow;               // Альтернатива: sf::Color(255, 255, 0)
    
    // Границы
    const sf::Color BORDER = sf::Color::Red;                // #FF0000
    
    // Фон
    const sf::Color BACKGROUND = sf::Color(30, 30, 30);     // #1E1E1E
    
    // Для будущих улучшений
    const sf::Color GRID = sf::Color(50, 50, 50, 100);      // Полупрозрачный
    const sf::Color TEXT = sf::Color::White;
    const sf::Color SCORE = sf::Color(255, 215, 0);         // Золотой
}
#endif