#include "test_scene.hpp"

TestScene::TestScene() { }
TestScene::~TestScene() { }
TestScene::TestScene(sf::RenderWindow *window) {
    this->window = window;
}

void TestScene::input(sf::Event *event) {
    switch (event->type) {
        case sf::Event::KeyPressed:
            break;

        case sf::Event::KeyReleased:
            break;

        default:
            break;
    }

}

void TestScene::update() {

}

void TestScene::draw() {
}

}
