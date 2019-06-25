#include "test_scene.hpp"

TestScene::TestScene() { }
TestScene::~TestScene() { }
TestScene::TestScene(sf::RenderWindow *window) {
    this->window = window;
    this->load();
}

void TestScene::update() {
    player.rotate(d * rotSpeed - a * rotSpeed);
    rotation = player.getRotation();

    float sideRotation = (rotation - 90) * PI / 180.0;
    float frontRotation = rotation * PI / 180.0;

    movement.x = w * speed * sin(frontRotation) -
                 s * speed * sin(frontRotation) +
                 q * speed * sin(sideRotation) -
                 e * speed * sin(sideRotation);
    movement.y = s * speed * cos(frontRotation) -
                 w * speed * cos(frontRotation) +
                 e * speed * cos(sideRotation) -
                 q * speed * cos(sideRotation);

    player.move(movement.x, movement.y);

}

void TestScene::draw() {
    window->draw(player);
}

void TestScene::input(sf::Event *event) {
    switch (event->type) {
        case sf::Event::KeyPressed:
            handleKeyboardPress(*event);
            break;
            
        case sf::Event::KeyReleased:
            handleKeyboardRelease(*event);
            break;
            
        default:
            break;
    }
    
}

void TestScene::load() {
    name = "Testing Scene";
    speed = 5.f;
    rotSpeed = 2.f;
    rotation = 0.f;
    size = sf::Vector2f(30.f, 50.f);
    movement = sf::Vector2f(0.f, 0.f);
    position = sf::Vector2f(window->getSize().x/2, window->getSize().y/2);
    
    player = sf::ConvexShape(3);
    player.setPoint(0, sf::Vector2f(0.f      , -size.y/2));
    player.setPoint(1, sf::Vector2f(-size.x/2,  size.y/2));
    player.setPoint(2, sf::Vector2f( size.x/2,  size.y/2));
    player.setFillColor(sf::Color(128,160,192));
    player.setPosition(position);
}

std::string TestScene::getName() {
    return name;
}

void TestScene::handleKeyboardPress(sf::Event event) {
    w = event.key.code == sf::Keyboard::W || w;
    a = event.key.code == sf::Keyboard::A || a;
    s = event.key.code == sf::Keyboard::S || s;
    d = event.key.code == sf::Keyboard::D || d;
    q = event.key.code == sf::Keyboard::Q || q;
    e = event.key.code == sf::Keyboard::E || e;
}

void TestScene::handleKeyboardRelease(sf::Event event) {
    w = event.key.code != sf::Keyboard::W && w;
    a = event.key.code != sf::Keyboard::A && a;
    s = event.key.code != sf::Keyboard::S && s;
    d = event.key.code != sf::Keyboard::D && d;
    q = event.key.code != sf::Keyboard::Q && q;
    e = event.key.code != sf::Keyboard::E && e;
}

