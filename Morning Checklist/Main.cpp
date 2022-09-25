//This will be my first attempt at a movement game
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <vector>
#include <iostream>
#include "Player.h"

//yes
int main()
{
	sf::RenderWindow window( sf::VideoMode( 800, 600 ), "Maybe Movement" );
	window.setFramerateLimit( 60 );

	//Initialize
	Player player;
	GrappleHook hook(player);

	//GrappleBox
	sf::RectangleShape box;
	box.setSize( sf::Vector2f( 15.f, 15.f ) );
	box.setPosition( sf::Vector2f( 200, 300 ) );

	//Floor
	sf::RectangleShape floor;
	floor.setFillColor( sf::Color::Blue );
	floor.setPosition( 0, 530 );
	floor.setSize( sf::Vector2f( 800, 100 ) );

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

		//Update entities
		player.Update();
		hook.Update(player, &window, box);

		//Collision - Need to fix/ flesh out
		// the hook is falling off of the player when jumping 
		player.Collision( floor );
		hook.Collision( player );

		window.clear();

		//Draw
		window.draw( floor );
		window.draw( player.pBox );
		window.draw( box );
		window.draw( hook.gLine );
		window.draw( hook.gHook );

		window.display();
	}

	return 0;
}