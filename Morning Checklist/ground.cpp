/*
* ground constructor taking size, position, color, and if it is a floor
*/
#include "ground.h"

ground::ground( sf::Vector2f size, sf::Vector2f position, sf::Color color, bool floor ) : tile( size, position, color )
{
	object_.setSize( size );
	object_.setFillColor( color );
	object_.setPosition( position );
	isFloor = floor;
}

int ground::collision( sf::RectangleShape pBox, sf::RectangleShape object, bool floor )
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