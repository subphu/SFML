#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <algorithm>
#include <vector>
#include <math.h>

#include "settings.h"
#include "scene.h"

class TestScene: public Scene {

public:
    TestScene();
    TestScene(sf::RenderWindow *window);
    ~TestScene();

    void load();
    void draw();
    void update();
    void input(sf::Event *event);
    
    void handleKeyboardPress(sf::Event event);
    void handleKeyboardRelease(sf::Event event);
    std::string getName();
    
private:

    sf::RenderWindow *window;
    sf::Vector2f position, movement, size;
    sf::ConvexShape player;
    
    std::string name;
    bool w, a, s, d, q, e;
    float speed, rotation, rotSpeed;
    
};
