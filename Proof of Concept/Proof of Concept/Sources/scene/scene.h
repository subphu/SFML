#pragma once

class Scene {
    
public:
    virtual ~Scene() = default;
    
    virtual void draw() = 0;
    virtual void update() = 0;
    virtual void input(sf::Event *event) = 0;
    virtual std::string getName() = 0;
};
