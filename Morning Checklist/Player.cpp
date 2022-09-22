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

//--------------------------------------------------------------------------------------------------------------------------------------
//GrapplingHook
GrappleHook::GrappleHook(Player &player)
{
	//Initialize Grappling Line
	gLine.setFillColor( sf::Color::Green);
	gLine.setSize( sf::Vector2f( hookX, hookY ) );
	gLine.setPosition( sf::Vector2f( player.pBox.getPosition().x,player.pBox.getPosition().y));

	//Initialize GrappleHook
	gHook.setFillColor( sf::Color::Magenta );
	gHook.setSize( sf::Vector2f( 5.f, 5.f ));
	gHook.setPosition( sf::Vector2f( gLine.getPosition() ));
}

void GrappleHook::Update(Player &player, sf::Window *window, sf::RectangleShape box)
{
	//Grappling Hook
	if ( sf::Mouse::isButtonPressed( sf::Mouse::Left) )
	{
		mousePos = sf::Mouse::getPosition( *window );
		if ( hookActive == false )
		{
			//grappleHook.setOrigin( Vector2f( mousePos ) );
			rotation = grappleRotation( sf::Vector2f( mousePos ), player.pBox.getPosition() );
			std::cout << rotation << std::endl;
			gLine.rotate( rotation + 270 );
			grapLength = grappleLength( sf::Vector2f( mousePos ), player.pBox.getPosition() );
			std::cout << grapLength << std::endl;
			gLine.setSize( sf::Vector2f( 2, grapLength ) );
			hookActive = true;
		}
	}
	
	//Check if hook hits
	if ( box.getGlobalBounds().contains( sf::Vector2f( mousePos ) ) )
	{
		//grappleHook.setOrigin( Vector2f( mousePos ) );
		player.pBox.move( 5, -10 );
		hookHit = true;
	}
	//Retract grapple
	else
	{
		if ( grapLength >= 1 && hookHit == false )
		{
			grapLength -= 5;
			gLine.setSize( sf::Vector2f( 2, grapLength ) );
			if ( grapLength <= 1 )
			{
				gLine.setRotation( 0 );
				hookActive = false;
			}
		}
	}
}

void GrappleHook::Collision(Player &player)
{
	//keep GrappleLine onto player
	if ( gLine.getPosition().y != player.pBox.getPosition().y )
		gLine.setPosition( player.pBox.getPosition().x, player.pBox.getPosition().y );
	if ( gLine.getPosition().x != player.pBox.getPosition().x )
		gLine.setPosition( player.pBox.getPosition().x, player.pBox.getPosition().y );

	//Keep grappleHook on line
	gHook.setPosition( sf::Vector2f(gLine.getPosition().x + mousePos.x - gHook.getSize().x, gLine.getGlobalBounds().top));

}

float GrappleHook::grappleLength( sf::Vector2f mPos, sf::Vector2f pPos )
{
	return sqrt( pow( pPos.x - mPos.x, 2 ) + pow( pPos.y - mPos.y, 2 ) * 1.0 );
}

float GrappleHook::grappleRotation( sf::Vector2f mPos, sf::Vector2f pPos )
{
	double pi = 3.14159265;
	float angle = atan2( mPos.y - pPos.y, mPos.x - pPos.x ) * 180 / pi;

	return angle;
}
