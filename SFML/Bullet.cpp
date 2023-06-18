#include "Bullet.h"

Bullet::Bullet()
{
}

Bullet::Bullet(sf::Texture* texture, float pos_x, float pos_y, float dir_x, float dir_y, float movement_speed, float set_scale)
{
	this->shape.setTexture(*texture);
	this->setScale = 0.04f;
	this->shape.setScale(this->setScale, this->setScale);
	this->shape.setPosition(pos_x - this->getBounds().width/2, pos_y - this->getBounds().height/2);
	this->direction.x = dir_x;
	this->direction.y = dir_y;
	this->movementSpeed = movement_speed;
	this->setScale = set_scale;
}

Bullet::~Bullet()
{
}

const sf::FloatRect Bullet::getBounds() const
{
	return this->shape.getGlobalBounds();
}

void Bullet::setRotation(int x)
{
	this->shape.setRotation(x);
}

void Bullet::update()
{
	
	this->shape.move(this->direction * this->movementSpeed);
}

void Bullet::render(sf::RenderWindow* window)
{
	window->draw(this->shape);
}
