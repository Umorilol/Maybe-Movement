#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <vector>
#include <iostream>
#include "tile.h"
/* Need to merge instead of two seperate classes have grapplehook be apart of Player, polymorphism? */
class Player {
public:
	sf::RectangleShape p_box_;
	float x{40.f};
	float y{349.f};
    float multiplier{40.f};
	float movement_speed{10.f};
	float gravity_value{10.f};
	float jump_velocity{-15.f};
	float jump_timer{0.f};
    float delta_time;
	bool colliding{false};
	bool gravity_on{true};
	sf::Vector2f player_pos{x, y};
	sf::Vector2f player_size{30.f, 30.f};

	Player();

	void update(float);
	void collision(tile& object);
};

class GrappleHook {
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

    GrappleHook() = default;
    GrappleHook(Player& player);
	void Update(Player& player, sf::Vector2f mouse_position, tile box);
    static void Collision(Player& player);
	float GrappleRotation(sf::Vector2f m_pos, sf::Vector2f p_pos);
	float GrappleLength(sf::Vector2f m_pos, sf::Vector2f p_pos);
	sf::Vector2f GrappleSlope(sf::Vector2f m_pos, sf::Vector2f p_pos);
	void RetractGrapple();
};
