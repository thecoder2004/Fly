#include "Enemy.h"

void Enemy::initShape(sf::RenderWindow* window)
{
	if (type == ID::RED)
	{
		if (!this->texture.loadFromFile("Textures/red_enemy.png"))
		{
			std::cout << "Failed to load red enemy" << std::endl;
		}
	}
	if (type == ID::BLUE)
	{
		if (!this->texture.loadFromFile("Textures/blue_enemy.png"))
		{
			std::cout << "Failed to load blue enemy" << std::endl;
		}
	}
	if (type == ID::GREY)
	{
		if (!this->texture.loadFromFile("Textures/grey_enemy.png"))
		{
			std::cout << "Failed to load grey enemy" << std::endl;
		}
	}
	this->shape.setTexture(this->texture);
	this->shape.setScale(0.2f, 0.2f);
	this->shape.setPosition(
		static_cast<float>(rand() % (window->getSize().x - (int)this->shape.getGlobalBounds().width)),
		0.f
	);
	this->shapeHealth.setSize(sf::Vector2f(this->getBounds().width, 5.f));
	this->shapeHealth.setFillColor(sf::Color::Green);
	this->shapeHealthMax.setSize(sf::Vector2f(this->getBounds().width, 5.f));
	this->shapeHealthMax.setFillColor(sf::Color::Red);
}

void Enemy::initVariables()
{
	this->speed = 1.f;
	this->damage = type * 2;
	this->hpMax = 10.f;
	this->hp = this->hpMax;
}

Enemy::Enemy()
{
}

Enemy::Enemy(sf::RenderWindow* window, int type):type(type)
{
	this->initShape(window);
	this->initVariables();
}

Enemy::~Enemy()
{
}

const int& Enemy::getType() const
{
	return this->type;
}

const sf::FloatRect Enemy::getBounds() const
{
	return this->shape.getGlobalBounds();
}

const int& Enemy::getDamage() const
{
	return this->damage;
}

const int& Enemy::getHealth() const
{
	return this->hp;
}

void Enemy::takeDamage(int x)
{
	if (this->hp > 0)
	{
		this->hp -= x;
	}
	if (this->hp < 0)
	{
		this->hp = 0;
	}
}

void Enemy::update()
{
	this->shape.move(0.f, this->speed);
	this->shapeHealth.setPosition(sf::Vector2f(this->getBounds().left, this->getBounds().top + this->getBounds().height + 10.f));
	this->shapeHealthMax.setPosition(sf::Vector2f(this->getBounds().left, this->getBounds().top + this->getBounds().height + 10.f));
	this->shapeHealth.setSize(sf::Vector2f(this->shapeHealthMax.getSize().x * this->hp / this->hpMax, this->shapeHealthMax.getSize().y));
}

void Enemy::render(sf::RenderWindow* window)
{
	window->draw(this->shapeHealthMax);
	window->draw(this->shapeHealth);
	window->draw(this->shape);
}
