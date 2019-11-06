#include "object.hpp"
#include "../settings.h"

Object::Object() {}

void Object::createBox(float width, float height) {
    points.assign(4, sf::Vector2f());
    points[3] = sf::Vector2f(-width, height)/2.f;
    points[2] = sf::Vector2f( width, height)/2.f;
    points[1] = -points[3];
    points[0] = -points[2];
    vertices.setPrimitiveType(sf::Quads);
    createVertices();
}

void Object::createTriangle(float width, float height) {
    points.assign(3, sf::Vector2f());
    points[0] = sf::Vector2f( 0.f,  -height)/2.f;
    points[1] = sf::Vector2f( width, height)/2.f;
    points[2] = sf::Vector2f(-width, height)/2.f;
    vertices.setPrimitiveType(sf::Triangles);
    createVertices();
}

void Object::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= transformable.getTransform();
    target.draw(vertices, states);
}

void Object::move(float offsetX, float offsetY) {
    float rotation = transformable.getRotation();
    float side_rotation = (rotation - 90) * PI / 180.0;
    float front_rotation = rotation * PI / 180.0;
    transformable.move(-offsetX * sin(side_rotation) - offsetY * sin(front_rotation),
                       offsetX * cos(side_rotation) + offsetY * cos(front_rotation));
}

void Object::rotate(float angle) {
    transformable.rotate(angle);
}

void Object::createVertices() {
    vertices.clear();
    for (int i = 0; i < points.size(); i++) {
        vertices.append(sf::Vertex(points[i], color));
    }
    calculatePoints();
}

void Object::calculatePoints() {
    for (int i = 0; i < points.size(); i++) {
        sf::Transform transform = transformable.getTransform();
        sf::Vector2f position = vertices[i].position;
        points[i] = transform.transformPoint(position.x, position.y);
    }
}

void Object::setColor(sf::Color color) {
    this->color = color;
    for (int i = 0; i < points.size(); i++) {
        vertices[i].color = color;
    }
}

void Object::setPosition(float x, float y) {
    transformable.setPosition(x, y);
    calculatePoints();
}

void Object::setRotation(float angle) {
    transformable.setRotation(angle);
    calculatePoints();
}

void Object::setName(std::string name) {
    this->name = name;
}

std::string  Object::getName()      { return name; }
float        Object::getRotation()  { return transformable.getRotation(); }
sf::Vector2f Object::getPosition()  { return transformable.getPosition(); }
std::vector<sf::Vector2f> Object::getPoints() { return points; }
