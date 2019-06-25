#include "game.hpp"

namespace poc {
    
    Game::Game() {
        window.create(sf::VideoMode(DEFAULT_WIDTH, DEFAULT_HEIGHT), TITLE);
        run();
    }
    
    void Game::run() {
        using StateRef = std::shared_ptr<State>;
        
        sf::Clock clock;
        StateMachine state_machine = StateMachine(StateRef(new GameState(&window)));
        StateRef state = state_machine.getCurrentState();
        
        state->load();
        long lag = 0;
        
        while (window.isOpen()) {
            state = state_machine.getCurrentState();
            lag = state->run(lag);
            lag += clock.getElapsedTime().asMicroseconds();
            clock.restart();
        }
    }
}
