#ifndef segment_h
#define segment_h
#include <SFML/Graphics.hpp>

struct segment
    {
        int x, y;
    };
struct SnakeSegment
{
    sf::RectangleShape shape;
    int x, y;

};
#endif