#include "game.hpp"

namespace poc {
    
    Game::Game() {
        window.create( sf::VideoMode(width, height), GAME_TITLE );
        run();
    }
    
    void Game::run() {
        while ( window.isOpen() ) {
            handleEvent();
            window.clear();
            window.display();
        }
    }
    
}
