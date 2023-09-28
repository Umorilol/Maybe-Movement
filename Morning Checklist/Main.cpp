//This will be my first attempt at a movement game
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <vector>
#include <iostream>
// local headers
#include "Player.h"
#include "tile.h"
#include "ground.h"

int main()
{
	sf::RenderWindow window( sf::VideoMode( 800, 600 ), "Maybe Movement" );
	//window.setFramerateLimit( 60 );	// commenting out to implement framerate independent movement	
	sf::Clock clock;
	sf::Time delta_time;
		// code for calculating framerate
	sf::Time fps_update_time;
	unsigned int frame_count = 0;
		// text
	sf::Text fps_text;
	sf::Font font;
	if ( !font.loadFromFile( "fonts/Dosis-Light.ttf" ) ) // Replace with the path to your font file
	{
		// font loading error handling
		return EXIT_FAILURE;
	}
	fps_text.setFont( font );
	fps_text.setCharacterSize( 30 );
	fps_text.setFillColor( sf::Color::Red );
	fps_text.setPosition( 50.f, 50.f );

	//Initialize
	Player player;
	GrappleHook hook(player);

	//Vector for collidable objects
	std::vector<tile> colidable;
	
	//GrappleBox
	tile box( sf::Vector2f( 15.f, 15.f ), sf::Vector2f(200.f, 350.f), sf::Color::Blue);
	colidable.emplace_back( box );

	//Floor
	ground floor( sf::Vector2f( 800.f, 100.f ), sf::Vector2f( 0.f, 550.f ), sf::Color::Blue, true );
	colidable.emplace_back( floor );

	while ( window.isOpen() )
	{
		sf::Event event;
		while ( window.pollEvent( event ) )
		{
			if ( event.type == sf::Event::Closed )
			{
				window.close();
			}
		}
		// framerate
		delta_time = clock.restart();
		frame_count++;
		fps_update_time += delta_time;

		if ( fps_update_time >= sf::seconds( 1.0f ) )
		{
			float fps = frame_count / fps_update_time.asSeconds();
			fps_text.setString( "FPS: " + std::to_string( static_cast<int>( fps ) ) );

			frame_count = 0;
			fps_update_time -= sf::seconds( 1.0f );
		}

		//Update entities
		player.update(delta_time.asSeconds());
		for(auto& i : colidable)
			hook.Update(player, &window, i);

		/*Collision - Attempted to push colidable objects into a vector, current logic only works for a single object (the floor)
		 *Current iteration will detect collision using AABB method and will only cancel gravity so player does not sink through
		 *floor */
		for (auto& i : colidable)
		{
			player.collision(i);
		}
		//player.collision( floor );

		window.clear();

		//Draw 
		window.draw( fps_text );
		// colidable vector
		for ( auto& i : colidable )
			i.draw( window );
		// player
		window.draw( player.pBox );
		window.draw( hook.g_line );

		window.display();
	}

	return 0;
}
