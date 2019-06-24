#pragma once

#include "state.h"
#include "scene.h"
#include "test_scene.hpp"

#include <iostream>
#include <SFML/Graphics.hpp>
#include <algorithm>
#include <vector>
#include <math.h>

class GameState: public State {
    
public:
    GameState(sf::RenderWindow *window);
    ~GameState();
    
    long run(long lag);
    void handleEvent();
    
    sf::RenderWindow *window;
    sf::Font font;
    sf::Text info;
    
    Scene *scene;
};
