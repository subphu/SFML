#include "game_state.hpp"

#define FRAME_DELAY 16500
#define SECOND 1000000

GameState::GameState(sf::RenderWindow *window) {
    this->window = window;
    scene = new TestScene(window);
    loadResources();
}

GameState::~GameState() {
    
}

long GameState::run(long lag) {
    if (lag > FRAME_DELAY) updateInfo(lag);
    while (lag > FRAME_DELAY) {
        handleEvent();
        scene->update();
        lag -= FRAME_DELAY;
    }
    
    window->clear();
    scene->draw();
    window->draw(info);
    window->display();
    return lag;
}

void GameState::handleEvent() {
    sf::Event event;
    while (window->pollEvent(event)) {
        scene->input(&event);
        if (event.type != sf::Event::Closed) return;
        window->close();
    }
}

void GameState::updateInfo(long lag) {
    std::string text = "Fps: " + std::to_string(SECOND / lag) + "\n" + "Scene: game";
    info.setString(text);
}

void GameState::loadResources() {
    if (!font.loadFromFile("Resources/GillSans.ttc")) {
        std::cout << "Unable to load Font" << std::endl;
        // Push error state
        return;
    }
    info.setFont(font);
    info.setCharacterSize(24);
    info.setFillColor(sf::Color::White);
    info.move(8, 0);
}

