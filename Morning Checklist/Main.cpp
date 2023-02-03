//This will be my first attempt at a movement game
#include "Player.h"
using namespace sf;

// Temp function to create a map tile
RectangleShape tileSquare( Color, Vector2f);

int main()
{
	sf::RenderWindow window( sf::VideoMode( 800, 600 ), "Maybe Movement" );
	window.setFramerateLimit( 60 );

	//Initialize
	Player player;
	GrappleHook hook(player);
	
	// Create an array of tiles with different colors
	RectangleShape sky = tileSquare(Color::Blue, Vector2f(0, 0));

	//Floor
	sf::RectangleShape floor;
	floor.setFillColor( sf::Color::Green );
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
		//hook.Update(player, &window, skyBox);

		//Draw
		window.clear();

		window.draw( floor );
		window.draw( player.pBox );
		window.draw( sky );
		//window.draw( skyBox );
		window.draw( hook.grappleLine );
		window.draw( hook.grappleHook );

		window.display();
	}

	return 0;
}

RectangleShape tileSquare( Color tileColor, Vector2f tilePosition ) {
	Vector2f tileSize( 16.f, 16.f );
	RectangleShape tempTile;

	tempTile.setSize( tileSize );
	tempTile.setFillColor( tileColor );
	tempTile.setPosition( tilePosition );

	return tempTile;
}