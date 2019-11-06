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
    
    void move(float side, float front);
    void rotate(float angle);
    void lookAt(sf::Vector2f position);
    void setViewDistance(float distance);
    
    float getViewDistance();
    sf::Vector2f getDirection();
    sf::Vector2f getPositionWithOffset();
    std::vector<sf::Vector2f> getVisiblePoints(std::vector<Object> &objects);
    
    
    
private:
    
    float speed, rot_speed, view_angle, view_distance;
    sf::Vector2f focus_position;
    
    bool inViewAngle(sf::Vector2f pt);
    sf::Vector2f raycast(sf::Vector2f target, std::vector<Object> *obstacles, std::vector<int> &hit_idx);
    std::vector<sf::Vector2f> sortPoints(std::vector<sf::Vector2f> points);
    
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};
