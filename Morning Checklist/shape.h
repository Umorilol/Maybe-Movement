#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <vector>
#include <iostream>

/*
 * JJ Gallucci
 * This file defines a parent shape that can be used to create objects with collision 
 */
class shape
{
public:
	// Constructor for a shape taking two integers (width, height)
	shape( sf::Vector2f, sf::Vector2f, sf::Color );
	~shape();
	static bool collision(sf::RectangleShape, sf::RectangleShape );
	sf::Vector2f get_position() const;
	sf::Vector2f get_size() const;

	sf::RectangleShape object_;

};
