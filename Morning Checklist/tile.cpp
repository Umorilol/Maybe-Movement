/*
JJ Gallucci
Defines the constructor */
#include "tile.h"
// tile constructor taking in a size, position, and color

tile::tile( sf::Vector2f dimensions, sf::Vector2f position, sf::Color shape_color )
{
	object_.setSize( dimensions );
	object_.setFillColor( shape_color );
	object_.setPosition( position );
	is_floor = false;
}

tile::~tile()
= default;

int tile::collision(sf::RectangleShape pBox, sf::RectangleShape object)
{
	// AABB Collision
	if ( pBox.getPosition().x < object.getPosition().x + object.getSize().x &&
		pBox.getPosition().x + pBox.getSize().x > object.getPosition().x &&
		pBox.getPosition().y < object.getPosition().y + object.getSize().y &&
		pBox.getPosition().y + pBox.getSize().y > object.getPosition().y )
	{
		return 1;
	}
	else
		return 0;
}

int tile::collision( sf::RectangleShape pBox, sf::RectangleShape object, bool floor )
{
	if ( floor )
	{
		if ( tile::collision( pBox, object ) == 1 )
		{
			return 2;
		}
		else
			return 0;
	}
}

void tile::draw(sf::RenderWindow & window)
{
	window.draw( object_ );
}

sf::Vector2f tile::get_position() const
{
	return object_.getPosition();
}

sf::Vector2f tile::get_size() const
{
	return object_.getSize();
}

