#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <vector>
#include <iostream>

class Player
{
public:
	sf::RectangleShape pBox;
	float startX { 40.f };
	float startY { 500.f };
	int vel { 5 };
	int gravity { 5 };
	int jumpVel { -10 };
	int jumpTimer { 0 };
	sf::Vector2f playerPos {startX, startY};

	Player();

	void Update();
	void Collision(sf::RectangleShape floor);
};

class GrappleHook
{
public:
	sf::Vector2i mousePosition;
	//Grapple Hook and Grapple Line
	sf::RectangleShape grappleLine;
	sf::RectangleShape gHook;
	float hookX{ 10 };
	float hookY{ 5 };
	bool hookActive{ false };
	bool hookHit { false };
	float rotation {0};
	float grappleLength { 1 };
	float grapMoving{ 0 };

	GrappleHook( Player &player );
	void Update( Player &player, sf::Window *window, sf::RectangleShape box );
	void Collision( Player &player );

	// Return the angle between the mouse clicked and player position
	float setGrappleRotation( sf::Vector2f mPos, sf::Vector2f pPos );

	// Calculates the length of grappling hook 
	float getGrappleLength( sf::Vector2f mPos, sf::Vector2f pPos );

	// Returns a vector for the length and height of "hook triangle"
	sf::Vector2f hookOffset( float grapRotat, float grapLength );

	// Slope of the grapplinghook line
	sf::Vector2f setGrappleSlope(sf::Vector2f mPos, sf::Vector2f pPos);
};

