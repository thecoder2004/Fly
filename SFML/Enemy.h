#pragma once
#include "Bullet.h"
enum ID
{
	RED = 0,
	BLUE,
	GREY,
	NUMBEROFTYPE
};
class Enemy
{
private:
	sf::Texture texture;
	sf::Sprite shape;
	int type;
	float speed;
	unsigned damage;

	int hp, hpMax;
	//Health
	sf::RectangleShape shapeHealth, shapeHealthMax;
	 //Function
	void initShape(sf::RenderWindow* window);
	void initVariables();
public:
	Enemy();
	Enemy(sf::RenderWindow* window, int type);
	virtual ~Enemy();
	//Accessors
	const int& getType() const;
	const sf::FloatRect getBounds() const;
	const int& getDamage() const;
	const int& getHealth() const;
	//Modifier
	void takeDamage(int x);
	//Functions
	void update();
	void render(sf::RenderWindow* window);
};

