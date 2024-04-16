#pragma once
#include <SFML/Graphics.hpp>

class Player
{
public:
	Player();
	~Player();
	void move();
	sf::FloatRect getPosition();
	void setPosition(float x, float y);
	void draw(sf::RenderWindow &window);
	void setSpeed(float newSpeed);
private:
	sf::RectangleShape platform;
	float speed=0.f;
};

