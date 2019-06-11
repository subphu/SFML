#pragma once

#include "state.h"
#include <SFML/Graphics.hpp>

class MainState: public State {
    
public:
    MainState(sf::RenderWindow *window);
    ~MainState();
    
    void update(float dt);
    void draw(float dt);
    void input(sf::Event *event);
    
    sf::RenderWindow *window;
};
