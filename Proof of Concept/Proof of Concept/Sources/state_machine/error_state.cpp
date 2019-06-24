#include "error_state.hpp"

ErrorState::ErrorState(sf::RenderWindow *window, std::string message) {
    this->window = window;
    this->message = message;
    std::cout << message << std::endl;
}

ErrorState::~ErrorState() {
    
}

long ErrorState::run(long lag) {
    handleEvent();
    return 0;
}

void ErrorState::handleEvent() {
    sf::Event event;
    while (window->pollEvent(event)) {
        if (event.type != sf::Event::Closed) return;
        window->close();
    }
}

void ErrorState::load() {
    
}
