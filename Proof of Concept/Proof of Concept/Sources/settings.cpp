#include "settings.h"

namespace Helper {
    
    float anglePoint(sf::Vector2f pt) {
        return atan2(pt.y, pt.x) * (180 / PI);
    }
    
    sf::Vector2f pointDirection(float angle) {
        float rad = angle * PI / 180.0;
        return sf::Vector2f(cos(rad), sin(rad));
    }

    sf::Vector2f shortestDistance(sf::Vector2f pt1, sf::Vector2f pt2) {
        float d1 = (pt1.x * pt1.x) + (pt1.y * pt1.y);
        float d2 = (pt2.x * pt2.x) + (pt2.y * pt2.y);
        return d1 > d2 ? pt2 : pt1;
    }
    
    sf::Vector2f pointIntersection(sf::Vector2f dir, sf::Vector2f pt1, sf::Vector2f pt2) {
        float x3 = 0;
        float x4 = dir.x;
        float x1 = pt1.x;
        float x2 = pt2.x;
        float y3 = 0;
        float y4 = dir.y;
        float y1 = pt1.y;
        float y2 = pt2.y;
        
        float den = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);
        float t  = ((x1 - x3) * (y3 - y4) - (y1 - y3) * (x3 - x4)) / den;
        float u = -((x1 - x2) * (y1 - y3) - (y1 - y2) * (x1 - x3)) / den;
        
        return (0 <= t && t <= 1 && 0 <= u) ? sf::Vector2f(x1 + t * (x2 - x1), y1 + t * (y2 - y1)) : sf::Vector2f(MAXFLOAT, MAXFLOAT);
    }
}
