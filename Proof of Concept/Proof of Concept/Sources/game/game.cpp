#include "game.hpp"

namespace poc {
    
    Game::Game() {
        window.create( sf::VideoMode(DEFAULT_WIDTH, DEFAULT_HEIGHT), GAME_TITLE );
        run();
    }
    
    void Game::run() {
        StateMachine state_machine = StateMachine(StateRef(new MainState(&window)));
 
        while ( window.isOpen() ) {
            const StateRef state = state_machine.get_current_state();
            handleEvent(state);
            window.clear();
            state->draw(0);
            
            window.display();
        }
    }
    
    void Game::handleEvent(const StateRef state) {
        sf::Event event;
        while ( window.pollEvent(event) ) {
            state->input(&event);
            if (event.type != sf::Event::Closed) return;
            window.close();
        }
    }
}
