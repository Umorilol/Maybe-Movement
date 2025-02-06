#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <vector>
#include <iostream>
#include "tile.h"
/* Need to merge instead of two seperate classes have grapplehook be apart of Player, polymorphism? */

class Player
{
public:
    sf::RectangleShape p_box_;
    float x{40.f};
    float y{450.f};
    float multiplier{40.f};
    sf::Vector2f velocity{50.f, 0.f};
    float gravity = 15.f;
    float friction = 15.f;
    float jump_velocity{-25.f};
    float player_speed{40.f};
    float delta_time;
    bool colliding{false};
    sf::Vector2f player_pos{x, y};
    sf::Vector2f player_size{30.f, 30.f};

    Player();

    void update(float);
    void collision(tile& object);
};

class GrappleHook
{
public:
    sf::Vector2f mouse_pos;
    //Grapple Hook and Grapple Line
    sf::RectangleShape g_line;
    float hook_x{10.f};
    float hook_y{5.f};
    bool hook_active{false};
    bool hook_hit{false};
    float rotation{0.f};
    float grap_length{1.f};
    float dt_ = 0;

    GrappleHook() = default;
    GrappleHook(Player& player);
    void Update(Player&, sf::Vector2f, tile, float);
    static void Collision(Player& player);
    float GrappleRotation(sf::Vector2f m_pos, sf::Vector2f p_pos);
    float GrappleLength(sf::Vector2f m_pos, sf::Vector2f p_pos);
    sf::Vector2f GrappleSlope(sf::Vector2f m_pos, sf::Vector2f p_pos);
    void RetractGrapple();
};