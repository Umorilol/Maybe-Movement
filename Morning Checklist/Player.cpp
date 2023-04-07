#include "Player.h"

Player::Player()
{
	pBox.setSize( sf::Vector2f( 30.f, 30.f ) );
	pBox.setPosition( player_pos );
}

void Player::update()
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
	if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Space ) && jump_timer <= 15 )
	{
		pBox.move( 0, jump_velocity );
		jump_timer += 1;
	}
	if ( pBox.getPosition().y >= 500 )
		jump_timer = 0;

	//"Gravity"
	pBox.move( 0,gravity );
}

void Player::collision(sf::RectangleShape floor)
{
	if ( pBox.getPosition().y >= floor.getPosition().y - pBox.getSize().y )
		pBox.setPosition( pBox.getPosition().x, floor.getPosition().y - pBox.getSize().y );
}

//--------------------------------------------------------------------------------------------------------------------------------------
//GrapplingHook
GrappleHook::GrappleHook(Player &player)
{
	//Initialize Grappling Line
	g_line.setFillColor( sf::Color::Green);
	g_line.setSize( sf::Vector2f( hook_x, hook_y ) );

}

// Need to change the grappling hook so that it detects of a point or seperate entity at the end of grapple not the mouse pos
void GrappleHook::Update(Player &player, sf::Window *window, sf::RectangleShape box)
{
	//Make sure the grappling hook moves with player
	g_line.setPosition( sf::Vector2f( player.pBox.getPosition().x, player.pBox.getPosition().y ) );
	//Grappling Hook
	if ( sf::Mouse::isButtonPressed( sf::Mouse::Left) )
	{
		mouse_pos = sf::Mouse::getPosition( *window );
		if ( hook_active == false )
		{
			//grappleHook.setOrigin( Vector2f( mousePos ) );
			rotation = GrappleRotation( sf::Vector2f( mouse_pos ), player.pBox.getPosition() );
			std::cout << rotation << std::endl;
			g_line.rotate( rotation + 270 );
			grap_length = grappleLength( sf::Vector2f( mouse_pos ), player.pBox.getPosition() );
			std::cout << grap_length << std::endl;
			g_line.setSize( sf::Vector2f( 2, grap_length ) );
			hook_active = true;
			
		}
	}
	
	//Check if hook hits
	if ( box.getGlobalBounds().contains( sf::Vector2f( mouse_pos ) ) && hook_active == true)
	{
		sf::Vector2f gSlope = grappleSlope( sf::Vector2f( mouse_pos ), player.pBox.getPosition() );
		std::cout << gSlope.x << " " << gSlope.y << std::endl;
		grap_length = grappleLength( sf::Vector2f( mouse_pos ), player.pBox.getPosition() );
		g_line.setSize( sf::Vector2f( 2, grap_length ) );
		player.pBox.move( gSlope.x, gSlope.y );
		player.gravity = 0.f;
		hook_hit = true;
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::S) )
		{
			hook_hit = false;
			hook_active = false;
			player.gravity = 5;
	
		}
	}
	//Retract grapple
	else
	{
		if ( grap_length >= 1 && hook_hit == false )
		{
			RetractGrapple();
		}
	}
}

void GrappleHook::Collision(Player &player)
{
	//This can be to check if grapple hits a wall 

}

float GrappleHook::grappleLength( sf::Vector2f m_pos, sf::Vector2f p_pos )
{
	return sqrt( pow( p_pos.x - m_pos.x, 2 ) + pow( p_pos.y - m_pos.y, 2 ) * 1.0 );
}

float GrappleHook::GrappleRotation( sf::Vector2f m_pos, sf::Vector2f p_pos )
{
	double pi = 3.14159265;
	float angle = atan2( m_pos.y - p_pos.y, m_pos.x - p_pos.x ) * 180 / pi;

	return angle;
}

/*Get the slope of the line between mouse positionand player positionand return x value as slope and y value as always 1 or negative 1
* based on position relative to mouse position */
sf::Vector2f GrappleHook::grappleSlope( sf::Vector2f m_pos, sf::Vector2f p_pos ) 
{
	float xSlope = abs(( p_pos.x - m_pos.x ) / ( p_pos.y - m_pos.y ));
	float ySlope = 0;

	if ( m_pos.y > p_pos.y )
		 ySlope = 1;
	else
		ySlope = -1;

	if ( m_pos.x > p_pos.x )
		xSlope = xSlope;
	else
		xSlope = -xSlope;

	return sf::Vector2f( xSlope, ySlope );
}


void GrappleHook::RetractGrapple()
{
	grap_length -= 5;
	g_line.setSize( sf::Vector2f( 2, grap_length ) );
	if ( grap_length <= 1 )
	{
		g_line.setRotation( 0 );
		hook_active = false;
	}
}
