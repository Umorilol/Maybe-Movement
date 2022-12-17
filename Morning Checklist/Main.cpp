//This will be my first attempt at a movement game
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <vector>
#include <iostream>
#include "Player.h"

int main()
{
	sf::RenderWindow window( sf::VideoMode( 800, 600 ), "Maybe Movement" );
	window.setFramerateLimit( 60 );

	//Initialize
	Player player;
	GrappleHook hook(player);

	//GrappleBox
	sf::RectangleShape skyBox;
	skyBox.setSize( sf::Vector2f( 15.f, 15.f ) );
	skyBox.setPosition( sf::Vector2f( 200, 300 ) );

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
		hook.Update(player, &window, skyBox);

		//Collision - Need to fix/ flesh out
		// the hook is falling off of the player when jumping 
		player.Collision( floor );

		window.clear();

		//Draw
		window.draw( floor );
		window.draw( player.pBox );
		window.draw( skyBox );
		window.draw( hook.grappleLine );
		window.draw( hook.gHook );

		window.display();
	}

	return 0;
}