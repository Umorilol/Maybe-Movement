#include "Player.h"

Player::Player()
{
	playerBox.setSize( sf::Vector2f( 30.f, 30.f ) );
	playerBox.setPosition( playerPosition );
}

void Player::Update()
{
	//Player movement
	if ( sf::Keyboard::isKeyPressed( sf::Keyboard::D ) )
	{
		playerBox.move( vel, 0.f );
	}

	if ( sf::Keyboard::isKeyPressed( sf::Keyboard::A ) )
	{
		playerBox.move( -vel, 0.f );
	}

	//Jump
	if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Space ) && jumpTimer <= 15 )
	{
		playerBox.move( 0, jumpVel );
		jumpTimer += 1;
	}
	if ( playerBox.getPosition().y >= 500 )
		jumpTimer = 0;

	//"Gravity"
	playerBox.move( 0, gravity );
}

void Player::Collision(sf::RectangleShape floor)
{
	if ( playerBox.getPosition().y >= floor.getPosition().y - playerBox.getSize().y )
		playerBox.setPosition( playerBox.getPosition().x, floor.getPosition().y - playerBox.getSize().y );
}

GrappleHook::GrappleHook(Player &player)
{
	//Initialize Grapple Line
	grappleLine.setFillColor( sf::Color::Green);
	grappleLine.setSize( sf::Vector2f( hookX, hookY ) );
	
	//Initialize Grapple Hook
	grappleHook.setFillColor( sf::Color::Blue );
	grappleHook.setSize( grappleHookSize );
}

/* - Need to change the grappling hook so that it detects if a point or seperate entity at the end of grapple not the mouse pos
*  - Need to change the line length to shrink as the player moves towards it 
*/
void GrappleHook::Update(Player &player, sf::Window *window, sf::RectangleShape box)
{
	//Make sure the grappling hook moves with player
	grappleLine.setPosition( sf::Vector2f( player.playerBox.getPosition().x, player.playerBox.getPosition().y ) );
	grappleHook.setPosition( sf::Vector2f( player.playerBox.getPosition().x, player.playerBox.getPosition().y ) );
	/*  Get hook offsetand add it to the line position for hook ? ? ? ?
	* This needs to be changed so that the offset is added to the position and not sent there immediatly.
	* 
	* Currently when the mouse is clicked the hook position is set after 2 frames
	* Need to rework how hookOffset works 
	*/

	//Grappling Hook
	if ( sf::Mouse::isButtonPressed( sf::Mouse::Left) )
	{
		mousePosition = sf::Mouse::getPosition( *window );
		if ( hookActive == false )
		{
			//grapple line
			rotation = setGrappleRotation( sf::Vector2f( mousePosition ), player.playerBox.getPosition() );
			grappleLine.rotate( rotation + 270 );
			grappleLength = setGrappleLength( sf::Vector2f( mousePosition ), player.playerBox.getPosition() );

			//grapple hook
			grappleHookDistance = getHookOffset( rotation, grappleLength );
			hookActive = true;
		}
	}
	
	//Check if hook hits and move player in a line towards wherever hit
	collision(player, box);

	//Retract grapple
	retractGrapplingHook();

	//Move grapple outwards
	if ( grappleLength >= grappleLine.getSize().y && hookRetracting == false && hookActive == true)
	{
		grapMoving += 3;
		grappleLine.setSize( sf::Vector2f( 2, grapMoving ) );
	}
}		

void GrappleHook::collision(Player &player, sf::RectangleShape box )
{
	//Check if hook hits
	if ( box.getGlobalBounds().contains( sf::Vector2f( mousePosition ) ) )
	{
		hookHit = true;
		//turn off gravity so player will move towards skyBox
		player.gravity = 0.f;
		sf::Vector2f gSlope = setGrappleSlope( sf::Vector2f( mousePosition ), player.playerBox.getPosition() );
		std::cout << gSlope.x << " " << gSlope.y << std::endl;
		player.playerBox.move( gSlope.x, gSlope.y );

		hookHit = true;
	}
}

float GrappleHook::setGrappleLength( sf::Vector2f mousePosition, sf::Vector2f playerPosition )
{
	return sqrt( pow( playerPosition.x - mousePosition.x, 2 ) + pow( playerPosition.y - mousePosition.y, 2 ) * 1.0 );
}

float GrappleHook::setGrappleRotation( sf::Vector2f mousePosition, sf::Vector2f playerPosition )
{
	double pi = 3.14159265;
	float angle = atan2( mousePosition.y - playerPosition.y, mousePosition.x - playerPosition.x ) * 180 / pi;

	return angle;
}

//This function will get the x and y position to give the hook the correct position
sf::Vector2f GrappleHook::getHookOffset(float grappleRotation, float grappleLength)
{
	float radianGrappleRotation = grappleRotation * ( M_PI / 180 );
	sf::Vector2f offset ((cos(radianGrappleRotation) * grappleLength), (sin( radianGrappleRotation ) * grappleLength) );
	return offset;
}

/*Get the slope of the line between mouse positionand player positionand return x value as slope and y value as always 1 or negative 1
* based on position relative to mouse position */
sf::Vector2f GrappleHook::setGrappleSlope( sf::Vector2f mousePosition, sf::Vector2f playerPosition ) 
{
	float xSlope = abs(( playerPosition.x - mousePosition.x ) / ( playerPosition.y - mousePosition.y ));
	float ySlope = 0;

	if ( mousePosition.y > playerPosition.y )
		 ySlope = 1;
	else
		ySlope = -1;

	if ( mousePosition.x > playerPosition.x )
		xSlope = xSlope;
	else
		xSlope = -xSlope;

	return sf::Vector2f( xSlope, ySlope );
}

void GrappleHook::retractGrapplingHook()
{
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
}