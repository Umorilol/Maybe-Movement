#pragma once
/*
 * JJ Gallucci
 * This file defines a parent shape that can be used to create objects with collision 
 */
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <vector>
#include <iostream>

class tile
{
public:
	// constructor taking size. position, and color
	tile( sf::Vector2f, sf::Vector2f, sf::Color );
	~tile();
	static int collision(sf::RectangleShape, sf::RectangleShape );
	static int collision( sf::RectangleShape, sf::RectangleShape, bool floor );
	sf::Vector2f get_position() const;
	sf::Vector2f get_size() const;
	void draw( sf::RenderWindow& window );

	sf::RectangleShape object_;
	bool is_floor;

};

