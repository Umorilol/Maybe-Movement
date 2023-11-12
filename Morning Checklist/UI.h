#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <vector>
#include <iostream>

class UI {
public:
    sf::Time fps_update_time;
    sf::Text fps_text;
    sf::Font font;
    unsigned int frame_count = 0;

    int initialize();
    void update(sf::Time dt);
};
