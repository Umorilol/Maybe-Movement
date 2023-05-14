#include "shape.h"

shape::shape( sf::Vector2f dimensions, sf::Vector2f position, sf::Color shape_color )
{
	object_.setSize( dimensions );
	object_.setFillColor( shape_color );
	object_.setPosition( position );
}

shape::~shape()
= default;

bool shape::collision(sf::RectangleShape pBox, sf::RectangleShape object)
{
	// Attempted AABB Collision
	if ( pBox.getPosition().x < object.getPosition().x + object.getSize().x &&
		pBox.getPosition().x + pBox.getSize().x > object.getPosition().x &&
		pBox.getPosition().y < object.getPosition().y + object.getSize().y &&
		pBox.getPosition().y + pBox.getSize().y > object.getPosition().y )
	{
		return true;
	}
	else
		return false;
}

sf::Vector2f shape::get_position() const
{
	return object_.getPosition();
}

sf::Vector2f shape::get_size() const
{
	return object_.getSize();
}


