#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <vector>
#include <iostream>
#include "tile.h"

class Player
{
public:
	sf::RectangleShape pBox;
	float x { 40.f };
	float y { 349.f };
	float movement_speed { 100 };
	float gravity_value { 70 };
	float jump_velocity { -80 };
	float jump_timer { 0 };
	bool colliding {false};
	bool gravity_on{ true };
	sf::Vector2f player_pos {x, y};
	sf::Vector2f player_size{ 30.f, 30.f };

	Player();

	void update(float );
	void collision(tile& object);
};

class GrappleHook
{
public:
	sf::Vector2f mouse_pos;
	//Grapple Hook and Grapple Line
	sf::RectangleShape g_line;
	float hook_x{ 10 };
	float hook_y{ 5 };
	bool hook_active{ false };
	bool hook_hit { false };
	float rotation {0};
	float grap_length { 1 };

	GrappleHook( Player &player );
	void Update( Player &player, sf::Vector2f mouse_position, tile box );
	void Collision( Player &player );
	float GrappleRotation( sf::Vector2f m_pos, sf::Vector2f p_pos );
	float grappleLength( sf::Vector2f m_pos, sf::Vector2f p_pos );
	sf::Vector2f grappleSlope(sf::Vector2f m_pos, sf::Vector2f p_pos);
	void RetractGrapple();
};

