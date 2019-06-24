#include "game_state.hpp"

#define FRAME_DELAY 16500
#define SECOND 1000000

GameState::GameState(sf::RenderWindow *window) {
    this->window = window;
}
GameState::~GameState() {
    
}
long GameState::run(long lag) {
    while (lag > FRAME_DELAY) {
        handleEvent();
        lag -= FRAME_DELAY;
    }
    window->clear();
    window->display();
    return lag;
}
void GameState::handleEvent() {
    sf::Event event;
    while (window->pollEvent(event)) {
        if (event.type != sf::Event::Closed) return;
        window->close();
    }
}
