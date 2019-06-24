#include "game.hpp"

namespace poc {
    
    Game::Game() {
        window.create(sf::VideoMode(DEFAULT_WIDTH, DEFAULT_HEIGHT), GAME_TITLE);
        run();
    }
    
    void Game::run() {
        using StateRef = std::shared_ptr<State>;
        StateRef state;
        StateMachine state_machine = StateMachine(StateRef(new GameState(&window)));
        sf::Clock clock;
        
        long lag = 0;
        
        while (window.isOpen()) {
            state = state_machine.getCurrentState();
            lag = state->run(lag);
            lag += clock.getElapsedTime().asMicroseconds();
            clock.restart();
        }
    }
}
