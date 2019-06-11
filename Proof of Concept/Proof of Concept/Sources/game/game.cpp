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
    
    void Game::handleEvent() {
        sf::Event event;
        while ( window.pollEvent(event) ) {
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    
                case sf::Event::Resized:
                    width = event.size.width;
                    height = event.size.height;

                default:
                    break;
            }
        }
    }
}
