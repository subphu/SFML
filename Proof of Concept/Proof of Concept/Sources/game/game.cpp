#include "game.hpp"

namespace poc {
    
    Game::Game() {
        sf::ContextSettings settings;
        settings.antialiasingLevel = 8;
        window.create(sf::VideoMode(DEFAULT_WIDTH, DEFAULT_HEIGHT), TITLE, sf::Style::Default, settings);
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
