#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

#define GAME_TITLE "Proof of Concept"
#define DEFAULT_WIDTH 1280
#define DEFAULT_HEIGHT 960


namespace poc {
    class Game {
        
    public:
        Game();
        
    private:
        int width = DEFAULT_WIDTH;
        int height = DEFAULT_HEIGHT;
        sf::RenderWindow window;
        
        void run();
        void handleEvent();
    };
}

