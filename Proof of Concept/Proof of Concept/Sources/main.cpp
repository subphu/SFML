//
//  main.cpp
//  Proof of Concept
//
//  Created by Subroto Prasetyo Hudiono on 5/21/19.
//  Copyright © 2019 Subph. All rights reserved.
//

#include <SFML/Graphics.hpp>
#include <iostream>

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Proof of Concept");
    while (window.isOpen()) {
        sf::Event event;
        
        while (window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    std::cout << "Closed\n";
                    window.close();
                    break;
                    
                default:
                    break;
            }
        }
        window.clear();
        
        window.display();
    }
    return EXIT_SUCCESS;
}
