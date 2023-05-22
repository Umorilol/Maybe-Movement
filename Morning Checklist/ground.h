#include "tile.h"

class ground : public tile
{
public:
	ground( sf::Vector2f size, sf::Vector2f position, sf::Color color, bool floor );
	static int collision( sf::RectangleShape, sf::RectangleShape, bool floor );

private:
	bool isFloor{ false };

};
