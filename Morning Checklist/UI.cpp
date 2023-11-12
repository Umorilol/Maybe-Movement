#include "UI.h"

int UI::initialize() {
    if (!this->font.loadFromFile("fonts/Dosis-Light.ttf"))
    {
        // font loading error handling
        return EXIT_FAILURE;
    }
    fps_text.setFont(font);
    fps_text.setCharacterSize(30);
    fps_text.setFillColor(sf::Color::Red);
    fps_text.setPosition(50.f, 50.f);
}

void UI::update(sf::Time dt)
{
        frame_count++;
		fps_update_time += dt;

		if ( fps_update_time >= sf::seconds( 1.0f ) )
		{
			float fps = frame_count / fps_update_time.asSeconds();
			fps_text.setString( "FPS: " + std::to_string( static_cast<int>( fps ) ) );

			frame_count = 0;
			fps_update_time -= sf::seconds( 1.0f );
		}
}