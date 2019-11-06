#include "character.hpp"

#define FACING_ANGLE -90
#define SIGHT_LENGTH 200.f

Character::Character() {
    speed = 8.f;
    rot_speed = 4.f;
    view_angle = 120;
    view_distance = 0;
}

void Character::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= transformable.getTransform();
    target.draw(vertices, states);
}

void Character::move(float side, float front) {
    sf::Vector2f distance = attention - transformable.getPosition();
    sf::Vector2f direction = Helper::normalize(distance);
    float movement_x = side * speed;
    float movement_y = front * speed;
    transformable.move(-movement_x * direction.y - movement_y * direction.x,
                        movement_x * direction.x - movement_y * direction.y);
    
}

void Character::rotate(float angle) {
    transformable.rotate(angle * rot_speed);
}

void Character::lookAt(sf::Vector2f position) {
    attention = position;
    sf::Vector2f direction = Helper::normalize(attention - transformable.getPosition());
    transformable.setRotation(Helper::anglePoint(direction) + 90);
}

void Character::setViewDistance(float distance) {
    view_distance = distance;
}

float Character::getViewDistance() {
    return view_distance;
}

std::vector<sf::Vector2f> Character::getVisiblePoints(std::vector<Object> &objects) {
    std::vector<sf::Vector2f> output;
    std::vector<int> unseenIdx;
    std::vector<int> seenIdx;
    sf::Vector2f position = getPositionWithOffset();
    
    for (int i = 0; i < objects.size(); i++) {
        std::vector<sf::Vector2f> corners = objects[i].getPoints();
        for (int j = 0; j < corners.size(); j++) {
            sf::Vector2f direction = corners[j] - position;
            if (inViewAngle(direction)) {
                sf::Vector2f delta = Helper::pointDirection(0.001f);
                output.push_back(raycast(direction - delta, &objects, seenIdx));
                output.push_back(raycast(direction + delta, &objects, seenIdx));
                output.push_back(raycast(direction, &objects, seenIdx));
            }
        }
    }
    
    float start_angle = transformable.getRotation() + FACING_ANGLE - view_angle/2;
    output.push_back(raycast(Helper::pointDirection(start_angle), &objects, seenIdx));
    output.push_back(raycast(Helper::pointDirection(start_angle + view_angle), &objects, seenIdx));

    std::sort(seenIdx.begin(), seenIdx.end());
    seenIdx.erase(std::unique(seenIdx.begin(), seenIdx.end()), seenIdx.end());

    std::vector<Object> seenObjects;
    for (long i = 0; i < seenIdx.size(); i++) {
        seenObjects.push_back(objects[seenIdx[i]]);
    }
    objects = seenObjects;
    
    return sortPoints(output);
}

sf::Vector2f Character::raycast(sf::Vector2f direction, std::vector<Object> *obstacles, std::vector<int> &hitIdx) {
    sf::Vector2f position = getPositionWithOffset();
    sf::Vector2f intersection = sf::Vector2f(MAXFLOAT, MAXFLOAT);
    int index = 0;
    
    for (int i = 0; i < obstacles->size(); i++) {
        Object object = (*obstacles)[i];
        std::vector<sf::Vector2f> corners = object.getPoints();
        for (int j = 0; j < corners.size(); j++) {
            sf::Vector2f pt1 = corners[j];
            sf::Vector2f pt2 = j+1 < corners.size() ? corners[j+1] : corners[0];
            sf::Vector2f pti = Helper::pointIntersection(direction, pt1 - position, pt2 - position);
            intersection = Helper::shortestDistance(pti, intersection);
            index = intersection == pti ? i : index;
        }
    }
    hitIdx.push_back(index);
    return intersection;
}

std::vector<sf::Vector2f> Character::sortPoints(std::vector<sf::Vector2f> points) {
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
