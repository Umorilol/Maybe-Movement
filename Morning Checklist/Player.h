#define _USE_MATH_DEFINES

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <vector>
#include <iostream>

class Player
{
public:
	sf::RectangleShape playerBox;
	float startX{ 40.f };
	float startY{ 500.f };
	int vel{ 5 };
	int gravity{ 5 };
	int jumpVel{ -10 };
	int jumpTimer{ 0 };
	sf::Vector2f playerPosition{ startX, startY };

	Player();

	void Update();
	void Collision( sf::RectangleShape floor );
};

class GrappleHook
{
public:
	sf::Vector2i mousePosition;
	//Grapple Hook and Grapple Line
	sf::RectangleShape grappleLine;
	sf::RectangleShape grappleHook;
	sf::Vector2f grappleHookSize {10.f, 10.f};
	float hookX{ 10 };
	float hookY{ 5 };
	bool hookActive{ false };
	bool hookHit{ false };
	bool hookRetracting{ false };
	float rotation{ 0 };
	float grappleLength{ 1 };
	sf::Vector2f grappleHookDistance { 0, 0 };
	float grapMoving{ 0 };

	GrappleHook( Player& player );
	void Update( Player& player, sf::Window* window, sf::RectangleShape box );
	void collision( Player& player, sf::RectangleShape box );

	// Return the angle between the mouse clicked and player position
	float setGrappleRotation( sf::Vector2f mPos, sf::Vector2f pPos );

	// Calculates the length of grappling hook 
	float setGrappleLength( sf::Vector2f mPos, sf::Vector2f pPos );

	// Returns a vector for the length and height of "hook triangle"
	sf::Vector2f getHookOffset( float grappleRotation, float grappleLength );


	// Slope of the grapplinghook line
	sf::Vector2f setGrappleSlope( sf::Vector2f mPos, sf::Vector2f pPos );

	//Retract grappling hook
	void retractGrapplingHook();
};

