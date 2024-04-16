#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"
class Ball
{
public:
	Ball();
	~Ball();
	void move();
	sf::Vector2f getPosition();
	void setPosition(float x, float y);
	void draw(sf::RenderWindow& window);
	void setSpeed(float newSpeedX, float newSpeedY);
	void setSpeedX(float newSpeedX);
	float getSpeedX();
	float getSpeedY();
	void setSpeedY(float newSpeedY);
	bool isColidePlayer(Player player);
	bool isColidePlitka(sf::RectangleShape plitka);
private:
	sf::CircleShape circle;
	float speedX = 0.f;
	float speedY = 0.f;
	float angle = 0.f;
};

