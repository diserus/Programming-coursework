#include "Ball.h"

Ball::Ball()
{
	circle.setFillColor(sf::Color::Red);
	circle.setPosition(460, 770);
	circle.setRadius(15.f);
}
Ball::~Ball()
{

}

void Ball::move()
{
	circle.move(speedX, speedY);
}

sf::Vector2f Ball::getPosition()
{
	return circle.getPosition();
}

void Ball::setPosition(float x, float y)
{
	circle.setPosition(x, y);
}

void Ball::draw(sf::RenderWindow& window)
{
	window.draw(circle);
}

void Ball::setSpeed(float newSpeedX,float newSpeedY)
{
	this->speedX = newSpeedX;
	this->speedY = newSpeedY;
}

void Ball::setSpeedX(float newSpeedX)
{
	this->speedX = newSpeedX;
}

void Ball::setSpeedY(float newSpeedY)
{
	this->speedY = newSpeedY;
}

float Ball::getSpeedX()
{
	return speedX;
}

float Ball::getSpeedY()
{
	return speedY;
}

bool Ball::isColidePlayer(Player player)
{
	return circle.getGlobalBounds().intersects(player.getPosition());
}

bool Ball::isColidePlitka(sf::RectangleShape plitka)
{
	return circle.getGlobalBounds().intersects(plitka.getGlobalBounds());
}