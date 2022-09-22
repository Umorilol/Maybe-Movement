////This will be my first attempt at a movement game
//#include <SFML/Graphics.hpp>
//#include <SFML/Window.hpp>
//#include <SFML/System.hpp>
//#include <vector>
//#include <iostream>
//
//using namespace sf;
//float grappleRotation( Vector2f mPos, Vector2f pPos );
//float grappleLength( Vector2f mPos, Vector2f pPos );
///*
//* - Create player class
//* - Create skybox class
//
//*/
//
///*
//class Grapple
//{
//public:
//	RectangleShape grapplingHook;
//
//	Grapple(Vector2f playerPos, Vector2f destinationPos)
//	{
//		grapplingHook.setPosition( playerPos );
//		grapplingHook.setSize( Vector2f( destinationPos.x, 10.f) );
//	}
//};
//*/
//
//int main() 
//{
//	sf::RenderWindow window( sf::VideoMode( 800, 600 ), "Maybe Movement" );
//	window.setFramerateLimit( 60 );
//
//	//Create player 
//	RectangleShape player;
//	float x = 40.f, y = 500.f;
//	Vector2f playerPos(x, y);
//	player.setSize( Vector2f(30.f, 30.f ));
//	player.setPosition( playerPos );
//
//	int vel = 5;
//	int gravity = 5;
//	int jumpVel = -10;
//	int jumpTimer = 0;
//
//	//GrappleBox
//	sf::RectangleShape box;
//	box.setSize( sf::Vector2f( 15.f, 15.f ) );
//	box.setPosition( sf::Vector2f( 200, 300 ) );
//
//	//GrapplingHook
//	Vector2i mousePos;
//	float hookX = 10, hookY = 5;
//	bool hookActive = false;
//	bool hookHit = false;
//	RectangleShape grappleHook;
//	float rotation;
//	float grapLength = 1;
//	grappleHook.setFillColor( Color::Green );
//	grappleHook.setSize(Vector2f(hookX, hookY));
//	grappleHook.setPosition( Vector2f( player.getPosition().x, player.getPosition().y ) );
//	
//	//Floor
//	RectangleShape floor;
//	floor.setFillColor( Color::Blue );
//	floor.setPosition( 0, 530 );
//	floor.setSize(Vector2f(800, 100 ));
//	
//	while ( window.isOpen() ) 
//	{
//		sf::Event event;
//		while ( window.pollEvent( event ) )
//		{
//			if ( event.type == sf::Event::Closed )
//			{
//				window.close();
//			}
//		}
//
//		//Player movement
//		if ( sf::Keyboard::isKeyPressed( sf::Keyboard::D ) )
//		{
//			player.move( vel, 0.f );
//		}
//
//		if ( sf::Keyboard::isKeyPressed( sf::Keyboard::A ) )
//		{
//			player.move( -vel, 0.f );
//		}
//
//		//Jump
//		if ( Keyboard::isKeyPressed( Keyboard::Space ) && jumpTimer <= 15 )
//		{
//			player.move( 0, jumpVel );
//			jumpTimer += 1;
//		}
//		if ( player.getPosition().y >= 500 )
//			jumpTimer = 0;
//
//		//"Gravity"
//		player.move( 0, gravity );
//		
//		//Grappling Hook
//		if ( Mouse::isButtonPressed( Mouse::Left ) )
//		{
//			mousePos = Mouse::getPosition(window);
//			if ( hookActive == false )
//			{
//				//grappleHook.setOrigin( Vector2f( mousePos ) );
//				rotation = grappleRotation( Vector2f( mousePos ), player.getPosition() );
//				std::cout << rotation << std::endl;
//				grappleHook.rotate( rotation + 270 );
//				grapLength = grappleLength( Vector2f( mousePos ), player.getPosition() );
//				std::cout << grapLength << std::endl;
//				grappleHook.setSize( Vector2f( 2, grapLength));
//				hookActive = true;
//			}	
//		}
//
//		//Check if hook hits
//		if ( box.getGlobalBounds().contains( Vector2f( mousePos ) ) )
//		{
//			//grappleHook.setOrigin( Vector2f( mousePos ) );
//			player.move( 5, -10 );
//			hookHit = true;
//		}
//		//Retract grapple
//		else
//		{
//			if ( grapLength >= 1 && hookHit == false )
//			{
//				grapLength -= 5;
//				grappleHook.setSize( Vector2f( 2, grapLength ) );
//				if ( grapLength <= 1 )
//				{
//					grappleHook.setRotation( 0 );
//					hookActive = false;
//				}
//			}
//		}
//
//		//Collision - Need to fix/ flesh out
//		// the hook is falling off of the player when jumping 
//		//Player
//		if ( player.getPosition().y >= floor.getPosition().y - player.getSize().y )
//			player.setPosition( player.getPosition().x, floor.getPosition().y - player.getSize().y);
//
//		//GrapplingHook collision
//		if ( grappleHook.getPosition().y >= player.getPosition().y )
//			grappleHook.setPosition( player.getPosition().x, player.getPosition().y );
//		if ( grappleHook.getPosition().x <= player.getPosition().x )
//			grappleHook.setPosition( player.getPosition().x, player.getPosition().y );
//
//
//		window.clear();
//
//		//Draw
//		window.draw( floor );
//		window.draw( player );
//		window.draw( box );
//		window.draw( grappleHook );
//
//		window.display();
//	}
//
//	return 0;
//}
//
//float grappleLength( Vector2f mPos, Vector2f pPos )
//{
//	return sqrt( pow( pPos.x - mPos.x, 2 ) + pow( pPos.y - mPos.y, 2 ) * 1.0 );
//}
//
//float grappleRotation(Vector2f mPos, Vector2f pPos)
//{
//	double pi = 3.14159265;
//	float angle = atan2(mPos.y - pPos.y, mPos.x - pPos.x) * 180 / pi;
//
//	return angle;
//}