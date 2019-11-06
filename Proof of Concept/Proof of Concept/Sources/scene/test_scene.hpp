#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <algorithm>
#include <vector>
#include <math.h>

#include "../settings.h"
#include "../object/object.hpp"
#include "../object/character.hpp"
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
    
    void handleMouseMoved(sf::Event event);
    void handleKeyboardPress(sf::Event event);
    void handleKeyboardRelease(sf::Event event);
    std::string getName();
    bool compare(sf::Vertex v1, sf::Vertex v2);
    
private:
    std::string name;
    bool w, a, s, d, q, e;

    sf::RenderWindow *window;
    sf::View camera;
    Character player;
    std::vector<Object> objects;
        
};
