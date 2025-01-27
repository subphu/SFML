#pragma once

#include <math.h>
#include <SFML/Graphics.hpp>

#define TITLE "Proof of Concept"
#define DEFAULT_WIDTH   1500
#define DEFAULT_HEIGHT  1000
#define FRAME_DELAY 16500
#define SECOND      1000000
#define MAXFLOAT    0x1.fffffep+127f
#define PI          3.14159265358979323846264338327950288


namespace Helper {
    float anglePoint(sf::Vector2f pt);
    sf::Vector2f normalize(sf::Vector2f direction);
    sf::Vector2f pointDirection(float angle);
    sf::Vector2f shortestDistance(sf::Vector2f pt1, sf::Vector2f pt2);
    sf::Vector2f pointIntersection(sf::Vector2f dir, sf::Vector2f pt1, sf::Vector2f pt2);
}
