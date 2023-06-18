#pragma once

#include <iostream>
#include <ctime>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
class Bullet
{
	sf::Sprite shape;
	sf::Vector2f direction;
	float movementSpeed;
	float setScale;
public:
	Bullet();
	Bullet(sf::Texture* texture, float pos_x, float pos_y, float dir_x, float dir_y, float movementSpeed, float set_scale = 0.04f);
	virtual ~Bullet();
	//Accessors
	const sf::FloatRect getBounds() const;
	//Modifiers
	void setRotation(int x);
	//Functions
	void update();
	void render(sf::RenderWindow* window);
};

