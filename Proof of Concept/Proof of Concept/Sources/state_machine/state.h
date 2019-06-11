#pragma once

#include <SFML/Graphics.hpp>

class State {
    
public:
    virtual ~State() = default;
    virtual void draw(float dt) = 0;
    virtual void update(float dt) = 0;
    virtual void input(sf::Event *event) = 0;
    
    sf::RenderWindow *window;
};
