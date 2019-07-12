#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <list>
#include <vector>

#include "object.hpp"
#include "settings.h"

class Character: public Object {
    
public:
    Character();
    
    void move(float directionX, float directionY);
    void rotate(float angle);
    
    sf::Vector2f getDirection();
    sf::Vector2f getPositionWithOffset();
    std::vector<sf::Vector2f> getVisiblePoints(std::vector<Object> objects);
    
private:
    
    float speed, rot_speed, view_angle;
    
    bool inViewAngle(sf::Vector2f pt);
    sf::Vector2f raycast(sf::Vector2f target, std::vector<Object> obstacles);
    std::vector<sf::Vector2f> sortPoints(std::list<sf::Vector2f> points);
    
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};
