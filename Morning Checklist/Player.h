#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <vector>
#include <iostream>

class Player
{
public:
	sf::RectangleShape pBox;
	float x { 40.f };
	float y { 500.f };
	float vel { 5 };
	float gravity { 5 };
	float jump_velocity { -10 };
	float jump_timer { 0 };
	sf::Vector2f player_pos {x, y};

	Player();

	void update();
	void collision(sf::RectangleShape floor);
};

class GrappleHook
{
public:
	sf::Vector2i mouse_pos;
	//Grapple Hook and Grapple Line
	sf::RectangleShape g_line;
	float hook_x{ 10 };
	float hook_y{ 5 };
	bool hook_active{ false };
	bool hook_hit { false };
	float rotation {0};
	float grap_length { 1 };

	GrappleHook( Player &player );
	void Update( Player &player, sf::Window *window, sf::RectangleShape box );
	void Collision( Player &player );
	float GrappleRotation( sf::Vector2f m_pos, sf::Vector2f p_pos );
	float grappleLength( sf::Vector2f m_pos, sf::Vector2f p_pos );
	sf::Vector2f grappleSlope(sf::Vector2f m_pos, sf::Vector2f p_pos);
	void RetractGrapple();
};

