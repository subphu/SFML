#include "game.hpp"

namespace poc {
    
    Game::Game() {
        window.create(sf::VideoMode(DEFAULT_WIDTH, DEFAULT_HEIGHT), GAME_TITLE);
        run();
    }
    
    void Game::run() {
        StateMachine state_machine = StateMachine(StateRef(new MainState(&window)));
        sf::Clock clock;
        float lag = 0.f;
        
        while (window.isOpen()) {
            const StateRef state = state_machine.get_current_state();
            lag += clock.getElapsedTime().asMicroseconds();
            clock.restart();
            
            while (lag > FRAME_DELAY) {
                handleEvent(state);
                state->update();
                lag -= FRAME_DELAY;
            }
            
            window.clear();
            state->draw(lag / FRAME_DELAY);
            window.display();
        }
    }
    
    void Game::handleEvent(const StateRef state) {
        sf::Event event;
        while (window.pollEvent(event)) {
            state->input(&event);
            if (event.type != sf::Event::Closed) return;
            window.close();
        }
    }
}
