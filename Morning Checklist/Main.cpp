//This will be my first attempt at a movement game
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <vector>
#include "Player.h"
#include "shape.h"
int main()
{
	sf::RenderWindow window( sf::VideoMode( 800, 600 ), "Maybe Movement" );
	window.setFramerateLimit( 60 );

	//Initialize
	Player player;
	GrappleHook hook(player);

	//Vector for collidable objects
	std::vector<shape> colidable;
	
	//GrappleBox
	shape box( sf::Vector2f( 15.f, 15.f ), sf::Vector2f(200.f, 350.f), sf::Color::Blue);
	colidable.push_back( box );

	//Floor
	shape floor(sf::Vector2f(800, 100), sf::Vector2f(0, 530), sf::Color::Blue);
	colidable.push_back( floor );

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
		player.update();
		for(auto& i : colidable)
			hook.Update(player, &window, i);

		/*Collision - Attempted to push colidable objects into a vector, current logic only works for a single object (the floor)
		 *Current iteration will detect collision using AABB method and will only cancel gravity so player does not sink through
		 *floor */
		for (auto& i : colidable)
		{
			player.collision(&i);
		}
		//player.collision( floor );

		window.clear();

		//Draw
		window.draw( floor );
		window.draw( player.pBox );
		window.draw( box );
		window.draw( hook.g_line );

		window.display();
	}

	return 0;
}
