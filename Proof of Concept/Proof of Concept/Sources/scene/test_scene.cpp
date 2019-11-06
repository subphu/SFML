#include "test_scene.hpp"

TestScene::TestScene() { }
TestScene::~TestScene() { }
TestScene::TestScene(sf::RenderWindow *window) {
    this->window = window;
    this->load();
}

void TestScene::update() {
    player.rotate(d - a);
    player.move(e - q, s - w);
}

void TestScene::draw() {
    window->draw(objects[0]);
    
    std::vector<Object> visible(objects);
    sf::Vector2f offset = player.getDirection() * 3.f;
    sf::Vector2f position = player.getPositionWithOffset();
    
    std::vector<sf::Vector2f> points = player.getVisiblePoints(visible);
    std::vector<sf::Vertex> vertices { std::begin(points), std::end(points) };
    
    for (int i = 0; i < vertices.size(); i++) {
        sf::Vector2f pt = vertices[i].position - position;
        float distance = sqrt((pt.x * pt.x) + (pt.y * pt.y));
        float alpha = ((player.getViewDistance() - distance) / player.getViewDistance()) * 160;
        vertices[i].color = sf::Color(192, 192, 160, alpha);
        vertices[i].position += offset;
    }
    vertices.insert(vertices.begin(), position + offset);
    vertices[0].color = sf::Color(192, 192, 160, 160);
    
    for (int i = 0; i < visible.size(); i++) {
        window->draw(visible[i]);
    }
    window->draw(player);
    window->draw(&vertices[0], vertices.size(), sf::TriangleFan);
}

void TestScene::input(sf::Event *event) {
    switch (event->type) {
        case sf::Event::KeyPressed:
            handleKeyboardPress(*event);
            break;
                
        case sf::Event::KeyReleased:
            handleKeyboardRelease(*event);
            break;
                
        case sf::Event::MouseMoved:
            handleMouseMoved(*event);
            break;
            
        default:
            break;
    }
    
}

void TestScene::load() {
//    camera = sf::View(sf::Vector2f(450.f, 300.f), sf::Vector2f(900.f, 600.f));
//    window->setView(camera);
    float width = window->getSize().x;
    float height = window->getSize().y;
    w = false; a = false; s = false; d = false; q = false; e = false;
    name = "Testing Scene";
    
    player = Character();
    player.createTriangle(30.f, 50.f);
    player.setColor(sf::Color(128, 160, 192));
    player.setPosition(window->getSize().x/2, window->getSize().y/2);
    player.setViewDistance(sqrt((width * width) + (height * height)));
    
    objects.assign(12, Object());
    objects[0].createBox(window->getSize().x, window->getSize().y);
    objects[0].setPosition(window->getSize().x/2, window->getSize().y/2);
    objects[0].setColor(sf::Color(32, 32, 32));
    
    for (int i = 1; i < objects.size(); i++) {
        objects[i].createBox(100 + rand() % 100, 100 + rand() % 100);
        objects[i].setRotation(rand() % 180);
        objects[i].setPosition(rand() % (int)(window->getSize().x - 200), rand() % (int)(window->getSize().y - 200));
        objects[i].setColor(sf::Color(32, 96, 96));
    }
}

std::string TestScene::getName() {
    return name;
}

void TestScene::handleMouseMoved(sf::Event event) {
    player.lookAt(sf::Vector2f(event.mouseMove.x, event.mouseMove.y));
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

