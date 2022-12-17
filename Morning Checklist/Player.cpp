#include "Player.h"

Player::Player()
{
	pBox.setSize( sf::Vector2f( 30.f, 30.f ) );
	pBox.setPosition( playerPos );
}

void Player::Update()
{
	//Player movement
	if ( sf::Keyboard::isKeyPressed( sf::Keyboard::D ) )
	{
		pBox.move( vel, 0.f );
	}

	if ( sf::Keyboard::isKeyPressed( sf::Keyboard::A ) )
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

GrappleHook::GrappleHook(Player &player)
{
	//Initialize Grappling Line
	grappleLine.setFillColor( sf::Color::Green);
	grappleLine.setSize( sf::Vector2f( hookX, hookY ) );

}

/* - Need to change the grappling hook so that it detects if a point or seperate entity at the end of grapple not the mouse pos
*  - Need to change the line length to shrink as the player moves towards it 
*/
void GrappleHook::Update(Player &player, sf::Window *window, sf::RectangleShape box)
{
	//Make sure the grappling hook moves with player
	grappleLine.setPosition( sf::Vector2f( player.pBox.getPosition().x, player.pBox.getPosition().y ) );

	/*  Get hook offsetand add it to the line position for hook ? ? ? ?
	* This needs to be changed so that the offset is added to the position and not sent there immediatly.
	* 
	*/
	sf::Vector2f hookPosition( hookOffset( rotation, grappleLength ) );
	gHook.setPosition( grappleLine.getPosition().x + hookPosition.x, grappleLine.getPosition().y + hookPosition.y );

	//Grappling Hook
	if ( sf::Mouse::isButtonPressed( sf::Mouse::Left) )
	{
		mousePosition = sf::Mouse::getPosition( *window );
		if ( hookActive == false )
		{
			//grappleHook.setOrigin( Vector2f( mousePos ) );
			rotation = setGrappleRotation( sf::Vector2f( mousePosition ), player.pBox.getPosition() );
			grappleLine.rotate( rotation + 270 );
			grappleLength = getGrappleLength( sf::Vector2f( mousePosition ), player.pBox.getPosition() );
			std::cout << grappleLine.getSize().y << std::endl;
			//gLine.setSize( sf::Vector2f( 2, grapLength ));
			hookActive = true;
			player.gravity = 0.f;
		}
	}
	
	//Check if hook hits
	if ( box.getGlobalBounds().contains( sf::Vector2f(mousePosition) ) ) 
	{
		hookHit = true;
		sf::Vector2f gSlope = setGrappleSlope( sf::Vector2f( mousePosition ), player.pBox.getPosition() );
		std::cout << gSlope.x << " " << gSlope.y << std::endl;
		player.pBox.move( gSlope.x, gSlope.y );

		hookHit = true;
	}
	//Retract grapple
	if ( grappleLength >= 3 && grappleLength <= grappleLine.getSize().y )
	{
		hookRetracting = true;
		grappleLength -= 5;
		grappleLine.setSize( sf::Vector2f( 2, grappleLength ) );
		if ( grappleLength < 3 )
		{
			grappleLine.setRotation( 0 );
			grappleLength = 3;
			grappleLine.setSize( sf::Vector2f( 2, 0 ) );
			grapMoving = 0;
			hookActive = false;
			hookRetracting = false;
		}
	}

	//Move grapple outwards
	if ( grappleLength >= grappleLine.getSize().y && hookRetracting == false && hookActive == true)
	{
		grapMoving += 3;
		grappleLine.setSize( sf::Vector2f( 2, grapMoving ) );
	}
}		

void GrappleHook::Collision(Player &player)
{
	//This can be to check if grapple hits a wall 

}

float GrappleHook::getGrappleLength( sf::Vector2f mPos, sf::Vector2f pPos )
{
	return sqrt( pow( pPos.x - mPos.x, 2 ) + pow( pPos.y - mPos.y, 2 ) * 1.0 );
}

float GrappleHook::setGrappleRotation( sf::Vector2f mPos, sf::Vector2f pPos )
{
	double pi = 3.14159265;
	float angle = atan2( mPos.y - pPos.y, mPos.x - pPos.x ) * 180 / pi;

	return angle;
}

//This function will get the x and y position to give the hook the correct position
sf::Vector2f GrappleHook::hookOffset(float grapplingRotation, float grapplingLength)
{
	float radianGrappleRotation = grapplingRotation * ( M_PI / 180 );
	sf::Vector2f offset ((cos(radianGrappleRotation) * grapplingLength), (sin( radianGrappleRotation ) * grapplingLength) );
	return offset;
}

/*Get the slope of the line between mouse positionand player positionand return x value as slope and y value as always 1 or negative 1
* based on position relative to mouse position */
sf::Vector2f GrappleHook::setGrappleSlope( sf::Vector2f mPos, sf::Vector2f pPos ) 
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
