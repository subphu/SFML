#include "error_state.hpp"

ErrorState::ErrorState(sf::RenderWindow *window, std::string message) {
    this->window = window;
    this->message = message;
    this->load();
    std::cout << message << std::endl;
}

ErrorState::~ErrorState() {
    
}

long ErrorState::run(long lag) {
    handleEvent();
    window->clear();
    window->draw(text);
    window->display();
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
    if (!font.loadFromFile("Resources/GillSans.ttc")) return;
    text.setFont(font);
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::Red);
    text.move(8, 0);
    text.setString(message);
}
