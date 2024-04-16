#include "Player.h"

Player::Player()
{
	platform.setFillColor(sf::Color::Green);
	platform.setPosition(400, 800);
	platform.setSize(sf::Vector2f(150,25));
}

Player::~Player()
{

}

void Player::move()
{
	platform.move(speed,0);
}

sf::FloatRect Player::getPosition()
{
	return platform.getGlobalBounds();
}

void Player::setPosition(float x, float y)
{
	platform.setPosition(x,y);
}

void Player::draw(sf::RenderWindow& window)
{
	window.draw(platform);
}

void Player::setSpeed(float newSpeed)
{
	this->speed = newSpeed;
}
