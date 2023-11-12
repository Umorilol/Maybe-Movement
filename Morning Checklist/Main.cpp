//This will be my first attempt at a movement game
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <vector>
#include <iostream>
#include "Player.h"
#include "tile.h"
#include "ground.h"
#include "UI.h"

int main()
{
	sf::RenderWindow window( sf::VideoMode( 800, 600 ), "Maybe Movement" );
	//window.setFramerateLimit( 60 );	// commenting out to implement framerate independent movement	
	sf::Clock clock;
	sf::Time delta_time;

	// Initialize
    UI ui;
    ui.initialize();

	Player player;
	GrappleHook hook(player);

	// Vector for collidable objects
	std::vector<tile> colidable;
	
	// GrappleBox
	tile box( sf::Vector2f( 15.f, 15.f ), sf::Vector2f(200.f, 350.f), sf::Color::Blue);
	colidable.emplace_back( box );

	// Floor
	ground floor( sf::Vector2f( 800.f, 100.f ), sf::Vector2f( 0.f, 550.f ), sf::Color::Blue, true );
	colidable.emplace_back( floor );

	while ( window.isOpen() ) {
		sf::Event event;
		while ( window.pollEvent( event ) ) {
			if ( event.type == sf::Event::Closed ) {
				window.close();
			}
		}
		delta_time = clock.restart();

		// Update entities
        ui.update(delta_time);

		player.update(delta_time.asSeconds());
		for(auto& i : colidable)
			hook.Update(player, sf::Vector2f(sf::Mouse::getPosition(window)), i);

		/*Collision - Attempted to push colidable objects into a vector, current logic only works for a single object (the floor)
		 *Current iteration will detect collision using AABB method and will only cancel gravity so player does not sink through
		 *floor */
		for (auto& i : colidable) {
			player.collision(i);
		}
		//player.collision( floor );

		window.clear();

		//Draw 
		window.draw( ui.fps_text );

		for ( auto& i : colidable )
			i.draw( window );
	
		window.draw( player.p_box_ );
		window.draw( hook.g_line );

		window.display();
	}

	return 0;
}
