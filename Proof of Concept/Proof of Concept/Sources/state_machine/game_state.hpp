#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <algorithm>
#include <vector>
#include <math.h>

#include "state.h"
#include "scene.h"
#include "test_scene.hpp"
#include "state_machine.hpp"
#include "error_state.hpp"

class GameState: public State {
    
public:
    GameState(sf::RenderWindow *window);
    ~GameState();
    
    long run(long lag);
    void load();
    
private:
    void updateInfo(long lag);
    void handleEvent();
    
    sf::RenderWindow *window;
    sf::Font font;
    sf::Text info;
    
    Scene *scene;
    
};
