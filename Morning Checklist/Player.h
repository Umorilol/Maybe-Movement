#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <vector>
#include <iostream>

class Player
{

public:
	sf::RectangleShape pBox;
	float x { 40.f };
	float y { 500.f };
	int vel { 5 };
	int gravity { 5 };
	int jumpVel { -10 };
	int jumpTimer { 0 };
	sf::Vector2f playerPos {x, y};

	Player();

	void Update();
	void Collision(sf::RectangleShape floor);
};

class GrappleHook
{
public:
	sf::Vector2i mousePos;
	//Grapple Hook and Grapple Line
	sf::RectangleShape gLine;
	sf::RectangleShape gHook;
	float hookX{ 10 };
	float hookY{ 5 };
	bool hookActive{ false };
	bool hookHit { false };
	float rotation {0};
	float grapLength { 1 };

	GrappleHook( Player &player );
	void Update( Player &player, sf::Window *window, sf::RectangleShape box );
	void Collision( Player &player );
	float grappleRotation( sf::Vector2f mPos, sf::Vector2f pPos );
	float grappleLength( sf::Vector2f mPos, sf::Vector2f pPos );
	sf::Vector2f hookOffset( float grapRotat, float grapLength );
	sf::Vector2f grappleSlope(sf::Vector2f mPos, sf::Vector2f pPos);
};

