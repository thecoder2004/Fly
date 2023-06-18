#include "Player.h"

void Player::initTexture()
{
	if (!this->texture.loadFromFile("Textures/ship.png"))
	{
		std::cout << "Failed to load ship image!" << std::endl;
	};
}

void Player::initShape()
{
	this->shape.setTexture(this->texture);
	this->shape.setScale(0.15f, 0.15f);
}
void Player::initVariables()
{
	this->attackCoolDownMax = 10.f;
	this->attackCoolDown = this->attackCoolDownMax;
	this->movementSpeed = 5;
	this->hpMax = 100;
	this->hp = this->hpMax;
}

Player::Player()
{
	this->initTexture();
	this->initShape();
	this->initVariables();
}

Player::~Player()
{
}

const sf::FloatRect Player::getBounds() const
{
	return this->shape.getGlobalBounds();
}

const bool Player::canAttack() 
{
	if (this->attackCoolDown >= this->attackCoolDownMax)
	{
		this->attackCoolDown = 0.f;
		return true;
	}
	return false;
}

const int& Player::getHp() const
{
	return this->hp;
}

const int& Player::getHpMax() const
{
	return this->hpMax;
}

const sf::Vector2f& Player::getPos() const
{
	return this->shape.getPosition();
}

void Player::setPosition(float x, float y)
{
	this->shape.setPosition(x, y);
}

void Player::setPosition(sf::Vector2f pos)
{
	this->shape.setPosition(pos.x, pos.y);
}

void Player::move(const float dir_x, const float dir_y)
{
	this->shape.move(dir_x * movementSpeed, dir_y * movementSpeed);
}

void Player::getDamage(const unsigned& x)
{
	if (this->hp > 0)
	{
		this->hp -= x;
	}
	if(this->hp <= 0)
	{
		this->hp = 0;
	}
}

void Player::takeHealth(const unsigned& x)
{
	if (this->hp < this->hpMax)
	{
		this->hp += x;
	}
	if (this->hp > this->hpMax)
	{
		this->hp = this->hpMax;
	}
}

void Player::setHp()
{
	this->hp = this->hpMax;
}



void Player::updateAttack()
{
	if (this->attackCoolDown < this->attackCoolDownMax)
	{
		this->attackCoolDown += 0.5f;
	}
}

void Player::update()
{
	this->updateAttack();
}



void Player::render(sf::RenderWindow* window)
{
	window->draw(this->shape);
}
