#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include "state.h"

class ErrorState: public State {
    
public:
    ErrorState(sf::RenderWindow *window, std::string message);
    ~ErrorState();
    
    void load();
    long run(long lag);
    
private:
    void handleEvent();
    
    sf::RenderWindow *window;
    sf::Font font;
    sf::Text text;
    std::string message;
};
