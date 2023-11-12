#include "Player.h"

Player::Player() {
	p_box_.setSize(player_size);
	p_box_.setPosition(player_pos);
}

/*
 * tested changing movement_amount = movement_speed * delta_time -> movement_speed + delta_time * 1
 * result: drastically increased speed
 */

void Player::update(float dt) {
    delta_time = dt;
	float movement_amount = movement_speed * delta_time * multiplier;
	float gravity_amount = gravity_value * delta_time * multiplier;
	float jump_amount = jump_velocity * delta_time * multiplier;

	//Player movement
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		p_box_.move(movement_amount, 0.f);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		p_box_.move(-movement_amount, 0.f);
	}

	//Jump
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && jump_timer <= 15) {
		p_box_.move(0, jump_amount);
		jump_timer += 1;
	}
	if (p_box_.getPosition().y >= 505)
		jump_timer = 0;

	//"Gravity"
	if (gravity_on == true)
		p_box_.move(0, gravity_amount);
}

void Player::collision(tile& object) {
	if (object.collision(p_box_, object.object_, true) == 2) {
		gravity_on = false;
		colliding = true;
	}
	else if (object.collision(p_box_, object.object_) == 1) {
		colliding = true;
	}
	else {
		gravity_on = true;
	}
}

//--------------------------------------------------------------------------------------------------------------------------------------
//GrapplingHook
GrappleHook::GrappleHook(Player& player) {
	//Initialize Grappling Line
	g_line.setFillColor(sf::Color::Green);
	g_line.setSize(sf::Vector2f(hook_x, hook_y));
}

// Need to change the grappling hook so that it detects of a point or seperate entity at the end of grapple not the mouse pos
void GrappleHook::Update(Player& player, sf::Vector2f mouse_position, tile box) {
	//Make sure the grappling hook moves with player
	g_line.setPosition(sf::Vector2f(player.p_box_.getPosition().x, player.p_box_.getPosition().y));
	//Grappling Hook
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		mouse_pos = sf::Vector2f(mouse_position);
		if (hook_active == false) {
			//grappleHook.setOrigin( Vector2f( mousePos ) );
			rotation = GrappleRotation(sf::Vector2f(mouse_pos), player.p_box_.getPosition());
			g_line.rotate(rotation + 270);
			grap_length = GrappleLength(sf::Vector2f(mouse_pos), player.p_box_.getPosition());
			g_line.setSize(sf::Vector2f(2, grap_length));
			hook_active = true;
		}
	}

	//Check if hook hits
	if (box.object_.getGlobalBounds().contains(sf::Vector2f(mouse_pos)) && hook_active == true) {
		sf::Vector2f gSlope = GrappleSlope(sf::Vector2f(mouse_pos), player.p_box_.getPosition());
		std::cout << gSlope.x << " " << gSlope.y << std::endl;
		grap_length = GrappleLength(sf::Vector2f(mouse_pos), player.p_box_.getPosition());
		g_line.setSize(sf::Vector2f(2, grap_length));
		player.p_box_.move(gSlope.x, gSlope.y);
		player.gravity_value = 0.f;	// ABSOLUTELY NEED TO CHANGE
		hook_hit = true;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
			hook_hit = false;
			hook_active = false;
			player.gravity_value = 5;
		}
	}
	//Retract grapple
	else {
		if (grap_length >= 1 && hook_hit == false) {
			RetractGrapple();
		}
	}
}

void GrappleHook::Collision(Player& player) {
	//This can be to check if grapple hits a wall 
}

float GrappleHook::GrappleLength(sf::Vector2f m_pos, sf::Vector2f p_pos) {
	return static_cast<float>(sqrt(pow(p_pos.x - m_pos.x, 2) + pow(p_pos.y - m_pos.y, 2) * 1.0));
}

float GrappleHook::GrappleRotation(sf::Vector2f m_pos, sf::Vector2f p_pos) {
	double pi = 3.14159265;
	float angle = atan2(m_pos.y - p_pos.y, m_pos.x - p_pos.x) * 180 / (float)pi;

	return angle;
}

/*Get the slope of the line between mouse positionand player positionand return x value as slope and y value as always 1 or negative 1
* based on position relative to mouse position */
sf::Vector2f GrappleHook::GrappleSlope(sf::Vector2f m_pos, sf::Vector2f p_pos) {
	float xSlope = abs((p_pos.x - m_pos.x) / (p_pos.y - m_pos.y));
	float ySlope = 0;

	if (m_pos.y > p_pos.y)
		ySlope = 1;
	else
		ySlope = -1;

	if (m_pos.x > p_pos.x)
		xSlope = xSlope;
	else
		xSlope = -xSlope;

	return sf::Vector2f(xSlope, ySlope);
}

void GrappleHook::RetractGrapple() {
	grap_length -= 5;
	g_line.setSize(sf::Vector2f(2, grap_length));
	if (grap_length <= 1) {
		g_line.setRotation(0);
		hook_active = false;
	}
}
