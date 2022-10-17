#include "Player.h"

Player::Player()
{
	pBox.setSize( sf::Vector2f( 30.f, 30.f ) );
	pBox.setPosition( playerPos );
}

void Player::Update()
{
	//Player movement
	if ( sf::Keyboard::isKeyPressed( sf::Keyboard::D ) )  //Right
	{
		pBox.move( vel, 0.f );
	}

	if ( sf::Keyboard::isKeyPressed( sf::Keyboard::A ) )  //Left
	{
		pBox.move( -vel, 0.f );
	}
	
	//Jump
	if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Space ) && jumpTimer <= 15 )
	{
		pBox.move( 0, jumpVel );
		jumpTimer += 1;
	}
	if ( pBox.getPosition().y >= 500 )
		jumpTimer = 0;

	//"Gravity"
	pBox.move( 0, gravity );
}

void Player::Collision(sf::RectangleShape floor)
{
	if ( pBox.getPosition().y >= floor.getPosition().y - pBox.getSize().y )
		pBox.setPosition( pBox.getPosition().x, floor.getPosition().y - pBox.getSize().y );
}

//--------------------------------------------------------------------------------------------------------------------------------------
//GrapplingHook
GrappleHook::GrappleHook(Player &player)
{
	//Initialize Grappling Line
	gLine.setFillColor( sf::Color::Green);
	gLine.setSize( sf::Vector2f( hookX, hookY ) );

	//Initialize grapple hook
	gHook.setFillColor( sf::Color::Yellow );
	gHook.setSize( sf::Vector2f(10.f, 10.f ));
}

/* - Need to change the grappling hook so that it detects of a point or seperate entity at the end of grapple not the mouse pos
*  - Need to change the line length to shrink as the player moves towards it 
*/
void GrappleHook::Update(Player &player, sf::Window *window, sf::RectangleShape box)
{
	std::cout << grapMoving << std::endl;
	std::cout << grapLength << std::endl;
	//Make sure the grappling hook moves with player
	gLine.setPosition( sf::Vector2f( player.pBox.getPosition().x, player.pBox.getPosition().y ) );

	//Get hook offset and add it to the line position for hook
	sf::Vector2f hookPos( hookOffset( rotation, grapLength ) );
	gHook.setPosition( gLine.getPosition().x + hookPos.x, gLine.getPosition().y + hookPos.y );

	//Grappling Hook
	if ( sf::Mouse::isButtonPressed( sf::Mouse::Left) )
	{
		mousePos = sf::Mouse::getPosition( *window );
		if ( hookActive == false )
		{
			//grappleHook.setOrigin( Vector2f( mousePos ) );
			rotation = grappleRotation( sf::Vector2f( mousePos ), player.pBox.getPosition() );
			gLine.rotate( rotation + 270 );
			grapLength = grappleLength( sf::Vector2f( mousePos ), player.pBox.getPosition() );
			std::cout << gLine.getSize().y << std::endl;
			//gLine.setSize( sf::Vector2f( 2, grapLength ));
			hookActive = true;
		}
	}

	//Check if hook hits
	if ( box.getGlobalBounds().contains( sf::Vector2f(mousePos) ) ) 
	{
		hookHit = true;
		sf::Vector2f gSlope = grappleSlope( sf::Vector2f( mousePos ), player.pBox.getPosition() );
		std::cout << gSlope.x << " " << gSlope.y << std::endl;
		player.pBox.move( gSlope.x, gSlope.y );

		player.gravity = 0;
	}
	
	//Retract grapple
	if ( grapLength >= 3 && grapLength <= gLine.getSize().y )
	{
		hookRetracting = true;
		grapLength -= 5;
		gLine.setSize( sf::Vector2f( 2, grapLength ) );
		if ( grapLength < 3 )
		{
			gLine.setRotation( 0 );
			grapLength = 3;
			gLine.setSize( sf::Vector2f( 2, 0 ) );
			grapMoving = 0;
			hookActive = false;
			hookRetracting = false;
		}
	}

	//Move grapple outwards
	if ( grapLength >= gLine.getSize().y && hookRetracting == false && hookActive == true)
	{
		grapMoving += 3;
		gLine.setSize( sf::Vector2f( 2, grapMoving ) );
	}

}
		

void GrappleHook::Collision(Player &player)
{
	//This can be to check if grapple hits a wall 

}

float GrappleHook::grappleLength( sf::Vector2f mPos, sf::Vector2f pPos )
{
	return sqrt( pow( pPos.x - mPos.x, 2 ) + pow( pPos.y - mPos.y, 2 ) * 1.0 );
}

float GrappleHook::grappleRotation( sf::Vector2f mPos, sf::Vector2f pPos )
{
	float angle = atan2( mPos.y - pPos.y, mPos.x - pPos.x ) * (180 / M_PI);

	return angle;
}

//This function will get the x and y position to give the hook the correct position
sf::Vector2f GrappleHook::hookOffset(float grapRotat, float grapLength)
{
	float radGrapRotat = grapRotat * ( M_PI / 180 );
	sf::Vector2f offset ((cos(radGrapRotat) * grapLength), (sin( radGrapRotat ) * grapLength) );
	return offset;
}

/*Get the slope of the line between mouse positionand player positionand return x value as slope and y value as always 1 or negative 1
* based on position relative to mouse position */
sf::Vector2f GrappleHook::grappleSlope( sf::Vector2f mPos, sf::Vector2f pPos ) 
{
	float xSlope = abs(( pPos.x - mPos.x ) / ( pPos.y - mPos.y ));
	float ySlope = 0;

	if ( mPos.y > pPos.y )
		 ySlope = 1;
	else
		ySlope = -1;

	if ( mPos.x > pPos.x )
		xSlope = xSlope;
	else
		xSlope = -xSlope;

	return sf::Vector2f( xSlope, ySlope );
}
