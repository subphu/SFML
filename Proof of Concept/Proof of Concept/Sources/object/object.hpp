#pragma once

#include <iostream>
#include <math.h>
#include <vector>
#include <SFML/Graphics.hpp>

class Object: public sf::Drawable {
    
public:
    Object();
    
    void createBox(float width, float height);
    void createTriangle(float width, float height);
    
    void rotate(float angle);
    void move(float offsetX, float offsetY);
    
    void setName(std::string name);
    void setColor(sf::Color color);
    void setPosition(float x, float y);
    void setRotation(float angle);
    
    std::string getName();
    float getRotation();
    sf::Vector2f getPosition();
    std::vector<sf::Vector2f> getPoints();
    
protected:
    std::string name = "object";
    sf::Transformable transformable;
    
    std::vector<sf::Vector2f> points;
    sf::VertexArray vertices;
    sf::Color color = sf::Color(128, 128, 128);;
    
    void createVertices();
    void calculatePoints();
    
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    
};
