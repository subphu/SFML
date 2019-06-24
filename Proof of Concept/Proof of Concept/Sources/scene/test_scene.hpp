#pragma once

#include "scene.h"
#include <iostream>
#include <SFML/Graphics.hpp>

class TestScene: public Scene {

public:
    TestScene();
    TestScene(sf::RenderWindow *window);
    ~TestScene();

    void draw();
    void update();
    void input(sf::Event *event);

    sf::RenderWindow *window;
    
};
