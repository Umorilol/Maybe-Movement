//This will be my first attempt at a movement game
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
		player.Collision( floor );
		hook.Update(player, &window, skyBox);

		//Draw
		window.clear();

		window.draw( floor );
		window.draw( player.playerBox );
		window.draw( skyBox );
		window.draw( hook.grappleLine );
		window.draw( hook.grappleHook );

		window.display();
	}

	return 0;
}