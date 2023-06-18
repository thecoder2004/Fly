#pragma once
#include "Bullet.h"
class Player
{
	sf::Sprite shape;
	sf::Texture texture;
	float movementSpeed;
	float attackCoolDown;
	float attackCoolDownMax;
	int hp;
	int hpMax;

	void initVariables();
	void initTexture();
	void initShape();
public:
	//Constructor and Destructor
	Player();
	virtual ~Player();

	//Accessors
	const sf::FloatRect getBounds()const;
	const bool canAttack();
	const int& getHp() const;
	const int& getHpMax() const;

	//Modifiers
	const sf::Vector2f& getPos() const;
	void setPosition(float x, float y);
	void setPosition(sf::Vector2f pos);
	void move(const float dir_x,const float dir_y);
	void getDamage(const unsigned& x);
	void takeHealth(const unsigned& x);
	void setHp();
	//Functions
	void updateAttack();
	void update();
	void render(sf::RenderWindow* window);
};

