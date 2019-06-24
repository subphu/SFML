#include "game.hpp"

namespace poc {
    
    Game::Game() {
        window.create(sf::VideoMode(DEFAULT_WIDTH, DEFAULT_HEIGHT), GAME_TITLE);
        loadResources();
        run();
    }
    
    void Game::run() {
        StateRef state;
        StateMachine state_machine = StateMachine(StateRef(new GameState(&window)));
        sf::Clock clock;
        sf::Text fpsText;
        fpsText.setFont(font);
        fpsText.setCharacterSize(24);
        fpsText.setFillColor(sf::Color::White);
        fpsText.move(8, 0);
        
        int lag = 0.f;
        int fps = 0;
        
        while (window.isOpen()) {
            state = state_machine.getCurrentState();
            lag += clock.getElapsedTime().asMicroseconds();
            clock.restart();
            
            fps = lag > FRAME_DELAY ? SECOND / lag : fps;
            while (lag > FRAME_DELAY) {
                handleEvent(state);
                state->update();
                lag -= FRAME_DELAY;
            }
            
            window.clear();
            state->draw(lag / FRAME_DELAY);
            fpsText.setString(std::to_string(fps));
            window.draw(fpsText);
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
    
    void Game::loadResources() {
        if (!font.loadFromFile("Resources/GillSans.ttc")) {
            std::cout << "Unable to load Font" << std::endl;
            window.close();
        }
    }
}
