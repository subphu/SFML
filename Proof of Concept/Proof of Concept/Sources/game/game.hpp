#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include "main_state.hpp"
#include "state_machine.hpp"

#define GAME_TITLE "Proof of Concept"
#define DEFAULT_WIDTH 1280
#define DEFAULT_HEIGHT 960
#define FRAME_DELAY 16000


namespace poc {
    
    using StateRef = std::shared_ptr<State>;
    
    class Game {
        
    public:
        Game();
        
    private:
        sf::RenderWindow window;
        
        void run();
        void handleEvent(const std::shared_ptr<State> state);
    };
}

