#include "Player.h"

Player::Player()
{
    p_box_.setSize(player_size);
    p_box_.setPosition(player_pos);
}

void Player::update(float dt)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && velocity.y < .1)
    {
        velocity.y = jump_velocity;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        velocity.x = player_speed;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        velocity.x = -player_speed;
    }

    player_pos = player_pos + (velocity * dt);

    if (player_pos.y >= 500)
    {
        player_pos.y = 500;
        velocity.y = 0;
    }

    velocity.y = velocity.y + (gravity * dt);

    if (velocity.x > 0)
    {
        velocity.x = std::max(0.f, velocity.x - friction * dt);
    }
    else if (velocity.x < 0)
    {
        velocity.x = std::min(0.f, velocity.x + friction * dt);
    }

    p_box_.setPosition(player_pos);
    std::cout << velocity.x << " " << velocity.y << "\n";
}

void Player::collision(tile& object)
{
}

//--------------------------------------------------------------------------------------------------------------------------------------
//GrapplingHook
GrappleHook::GrappleHook(Player& player)
{
    //Initialize Grappling Line
    g_line.setFillColor(sf::Color::Green);
    g_line.setSize(sf::Vector2f(hook_x, hook_y));
}

// Need to change the grappling hook so that it detects of a point or seperate entity at the end of grapple not the mouse pos
void GrappleHook::Update(Player& player, sf::Vector2f mouse_position, tile box, float dt)
{
    dt_ = dt;
    //Make sure the grappling hook moves with player
    g_line.setPosition(sf::Vector2f(player.p_box_.getPosition().x, player.p_box_.getPosition().y));
    //Grappling Hook
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        mouse_pos = sf::Vector2f(mouse_position);
        if (hook_active == false)
        {
            //grappleHook.setOrigin( Vector2f( mousePos ) );
            rotation = GrappleRotation(sf::Vector2f(mouse_pos), player.p_box_.getPosition());
            g_line.rotate(rotation + 270);
            grap_length = GrappleLength(sf::Vector2f(mouse_pos), player.p_box_.getPosition());
            g_line.setSize(sf::Vector2f(2, grap_length));
            hook_active = true;
        }
    }

    //Check if hook hits (this breaks everything
    if (box.object_.getGlobalBounds().contains(sf::Vector2f(mouse_pos)) && hook_active == true)
    {
        sf::Vector2f gSlope = GrappleSlope(sf::Vector2f(mouse_pos), player.p_box_.getPosition());
        std::cout << gSlope.x << " " << gSlope.y << std::endl;
        grap_length = GrappleLength(sf::Vector2f(mouse_pos), player.p_box_.getPosition());
        g_line.setSize(sf::Vector2f(2, grap_length));
        player.velocity.y = 0.f;
        player.player_pos += gSlope;
        hook_hit = true;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            hook_hit = false;
            hook_active = false;
        }
    }

    //Retract grapple
    else
    {
        if (grap_length >= 1 && hook_hit == false)
        {
            RetractGrapple();
        }
    }
}

void GrappleHook::Collision(Player& player)
{
    //This can be to check if grapple hits a wall 
}

float GrappleHook::GrappleLength(sf::Vector2f m_pos, sf::Vector2f p_pos)
{
    return sqrt(pow(p_pos.x - m_pos.x, 2) + pow(p_pos.y - m_pos.y, 2));
}

float GrappleHook::GrappleRotation(sf::Vector2f m_pos, sf::Vector2f p_pos)
{
    double pi = 3.14159265;
    float angle = atan2(m_pos.y - p_pos.y, m_pos.x - p_pos.x) * 180 / (float)pi;

    return angle;
}

/*Get the slope of the line between mouse positionand player positionand return x value as slope and y value as always 1 or negative 1
* based on position relative to mouse position */
sf::Vector2f GrappleHook::GrappleSlope(sf::Vector2f m_pos, sf::Vector2f p_pos)
{
    float xSlope = abs((p_pos.x - m_pos.x) / (p_pos.y - m_pos.y) + .01);
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

void GrappleHook::RetractGrapple()
{
    grap_length -= 100 * dt_;
    g_line.setSize(sf::Vector2f(2, grap_length));
    if (grap_length <= 1)
    {
        g_line.setRotation(0);
        hook_active = false;
    }
}