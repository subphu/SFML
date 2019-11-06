#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

#include "../settings.h"
#include "../state_machine/game_state.hpp"
#include "../state_machine/state_machine.hpp"

namespace poc {
    
    class Game {
        
    public:
        Game();
        
    private:
        sf::RenderWindow window;
        
        void run();
    };
}

