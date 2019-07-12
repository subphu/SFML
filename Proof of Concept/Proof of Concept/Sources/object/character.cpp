#include "character.hpp"

#define FACING_ANGLE -90
#define SIGHT_LENGTH 200.f

Character::Character() {
    speed = 8.f;
    rot_speed = 4.f;
    view_angle = 120;
}

void Character::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= transformable.getTransform();
    target.draw(vertices, states);
}

void Character::move(float directionX, float directionY) {
    float movement_x = directionX * speed;
    float movement_y = directionY * speed;
    float rotation = transformable.getRotation();
    float side_rotation = (rotation - 90) * M_PI / 180.0;
    float front_rotation = rotation * M_PI / 180.0;
    transformable.move(-movement_x * sin(side_rotation) - movement_y * sin(front_rotation),
                        movement_x * cos(side_rotation) + movement_y * cos(front_rotation));
}

void Character::rotate(float angle) {
    transformable.rotate(angle * rot_speed);
}

std::vector<sf::Vector2f> Character::getVisiblePoints(std::vector<Object> objects) {
    std::list<sf::Vector2f> output;
    sf::Vector2f position = getPositionWithOffset();
    
    for (int i = 0; i < objects.size(); i++) {
        std::vector<sf::Vector2f> points = objects[i].getPoints();
        for (int j = 0; j < points.size(); j++) {
            sf::Vector2f direction = points[j] - position;
            if (inViewAngle(direction)) {
                sf::Vector2f delta = Helper::pointDirection(0.001f);
                output.push_back(raycast(direction - delta, objects));
                output.push_back(raycast(direction, objects));
                output.push_back(raycast(direction + delta, objects));
            }
        }
    }
    
    float start_angle = transformable.getRotation() + FACING_ANGLE - view_angle/2;
    output.push_front(raycast(Helper::pointDirection(start_angle), objects));
    output.push_back(raycast(Helper::pointDirection(start_angle + view_angle), objects));
    return sortPoints(output);
}

sf::Vector2f Character::raycast(sf::Vector2f direction, std::vector<Object> obstacles) {
    sf::Vector2f position = getPositionWithOffset();
    
    sf::Vector2f intersection = sf::Vector2f(MAXFLOAT, MAXFLOAT);
    for (int i = 0; i < obstacles.size(); i++) {
        std::vector<sf::Vector2f> points = obstacles[i].getPoints();
        for (int j = 0; j < points.size(); j++) {
            sf::Vector2f pt1 = points[j];
            sf::Vector2f pt2 = j+1 < points.size() ? points[j+1] : points[0];
            sf::Vector2f pti = Helper::pointIntersection(direction, pt1 - position, pt2 - position);
            intersection = Helper::shortestDistance(pti, intersection);
        }
    }
    return intersection;
}

std::vector<sf::Vector2f> Character::sortPoints(std::list<sf::Vector2f> points) {
    struct PointDetail {
        float rotation;
        sf::Vector2f position;
        PointDetail(sf::Vector2f position) : position(position) { }
    };
    
    std::vector<PointDetail> detail { std::begin(points), std::end(points) };
    sf::Vector2f position = getPositionWithOffset();
    sf::Transform transform;
    transform.rotate(view_angle - transformable.getRotation());
    
    for (int i = 0; i < detail.size(); i++) {
        sf::Vector2f temp = transform.transformPoint(detail[i].position.x, detail[i].position.y);
        detail[i].rotation = Helper::anglePoint(temp);
    }
    
    auto compare = [](PointDetail v1, PointDetail v2) { return v1.rotation > v2.rotation; };
    std::sort (detail.begin(), detail.end(), compare);
    std::vector<sf::Vector2f> output(detail.size(), sf::Vector2f());
    
    for (int i = 0; i < output.size(); i++) {
        output[i] = detail[i].position + position;
    }
    return output;
}

bool Character::inViewAngle(sf::Vector2f pt) {
    float deg = Helper::anglePoint(pt) - transformable.getRotation() - FACING_ANGLE + view_angle/2;
    deg = deg < 0 ? deg + 360 : deg;
    return 0 <= deg && deg <= view_angle;
}

sf::Vector2f Character::getDirection() {
    return Helper::pointDirection(transformable.getRotation() + FACING_ANGLE);
}

sf::Vector2f Character::getPositionWithOffset() {
    sf::Vector2f offset = getDirection() * 16.f;
    return transformable.getPosition() + offset;
}
