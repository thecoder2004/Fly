#include "Game.h"
#define PI 3.14159
void Game::initWorld()
{
	if (!this->worldBackGroundText.loadFromFile("Textures/background.jpeg"))
	{
		std::cout << "Failed to load file" << std::endl;
	};
	this->worldBackGround.setTexture(this->worldBackGroundText);
	this->worldBackGround.setScale(this->window->getSize().x / this->worldBackGround.getGlobalBounds().width,
		this->window->getSize().y / this->worldBackGround.getGlobalBounds().height);
}

void Game::initWindow()
{
	this->window = new sf::RenderWindow(sf::VideoMode::getDesktopMode(), "Fly",sf::Style::Close|sf::Style::Titlebar );
	this->window->setFramerateLimit(144);
	this->window->setVerticalSyncEnabled(false);
	this->window->setActive(true);
	//this->window->setMouseCursorGrabbed(true);
	//this->window->setMouseCursorVisible(false);
}

void Game::initPlayer()
{
	this->player = new Player;
}

void Game::initEnemies()
{
	this->spawnTimerMax = 50.f;
	this->spawnTimer = this->spawnTimerMax;
}

void Game::initTexture()
{
	this->texture["PLAYER_BULLET"] = new sf::Texture();
	if (!this->texture["PLAYER_BULLET"]->loadFromFile("Textures/player_bullet.png"))
	{
		std::cout << "Failed to load player bullet " << std::endl;
	};
	this->texture["PLAYER_BULLET_LEFT"] = new sf::Texture();
	if (!this->texture["PLAYER_BULLET_LEFT"]->loadFromFile("Textures/player_bullet_left.png"))
	{
		std::cout << "Failed to load player bullet " << std::endl;
	};
	this->texture["PLAYER_BULLET_RIGHT"] = new sf::Texture();
	if (!this->texture["PLAYER_BULLET_RIGHT"]->loadFromFile("Textures/player_bullet_right.png"))
	{
		std::cout << "Failed to load player bullet " << std::endl;
	};
	this->texture["ENEMY_BULLET"] = new sf::Texture();
	if (!this->texture["ENEMY_BULLET"]->loadFromFile("Textures/player_bullet.png"))
	{
		std::cout << "Failed to load eney bullet" << std::endl;
	}
}

void Game::initSound()
{
	if (!this->shot_buffer.loadFromFile("Audios/shot.wav"))
	{
		std::cout << "Failed to load audio file" << std::endl;
	}
	this->shot_sound.setBuffer(this->shot_buffer);
	this->shot_sound.setVolume(40.f);
	if (!this->fight_buffer.loadFromFile("Audios/fight.wav"))
	{
		std::cout << "Failed to load audio file" << std::endl;
	}
	this->fight_sound.setBuffer(this->fight_buffer);
	this->fight_sound.setVolume(40.f);

	if (!this->music.openFromFile("Audios/background.wav"))
	{
		std::cout << "Failed to load background music!" << std::endl;
	}
	this->music.setVolume(40.f);
	this->music.setLoop(this->player->getHp() > 0);
}

void Game::initText()
{
	if (!this->font.loadFromFile("Fonts/Dosis-Light.ttf"))
	{
		std::cout << "Failed to load font file" << std::endl;
	}
	this->guiText.setFont(this->font);
	this->guiText.setCharacterSize(36);
	this->guiText.setFillColor(sf::Color::White);
	this->guiText.setString("Test");

	this->endText.setFont(this->font);
	this->endText.setCharacterSize(100);
	this->endText.setFillColor(sf::Color::Red);
	this->endText.setString("GAME OVER!");
	this->endText.setPosition(sf::Vector2f
		(this->window->getSize().x/2.f - this->endText.getGlobalBounds().width/2.f,
		 this->window->getSize().y/2.f - this->endText.getGlobalBounds().height/2.f));

	this->restartText.setFont(this->font);
	this->restartText.setCharacterSize(60);
	this->restartText.setFillColor(sf::Color::Yellow);
	this->restartText.setString("New game");
	this->restartText.setPosition(sf::Vector2f
	(this->window->getSize().x / 2.f - this->restartText.getGlobalBounds().width / 2.f,
		this->window->getSize().y * 0.60f - this->restartText.getGlobalBounds().height / 2.f));
}

void Game::initHealth()
{
	this->shapeHealth.setSize(sf::Vector2f(this->player->getBounds().width, 5.f));
	this->shapeHealth.setFillColor(sf::Color::Green);

	this->shapeHealthMax.setSize(sf::Vector2f(this->player->getBounds().width, 5.f));
	this->shapeHealthMax.setFillColor(sf::Color::Red);
}

void Game::initSystem()
{
	this->points = 0;
	this->maxEnemy = 4;
}

Game::Game()
{
	this->initWindow();
	this->initWorld();
	this->initPlayer();
	this->initEnemies();
	this->initTexture();
	this->initSound();
	this->initText();
	this->initHealth();
	this->initSystem();
}

Game::~Game()
{
	delete this->window;
	delete this->player;
	for (auto& i : this->texture)
	{
		delete i.second;
	}
	for (int i = 0; i < this->player_bullets.size(); ++i)
	{
		delete this->player_bullets[i];
	}
	for (int i = 0; i < this->enemies.size(); ++i)
	{
		delete this->enemies[i];
	}
}

void Game::pollEvents()
{
	sf::Event event;
	while(this->window->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			this->window->close();
		}
		if (event.KeyPressed && event.key.code == sf::Keyboard::Escape)
		{
			this->window->close();
		}
	};
}

void Game::restart()
{
	this->points = 0;
	this->enemy_bullets.clear();
	this->enemies.clear();;
	this->player_bullets.clear();
	this->player->setHp();
}

void Game::updateInput()
{
	//Move the player by move the mouse
	sf::Vector2i mousePos = sf::Mouse::getPosition(*this->window);
	float posX = mousePos.x - this->player->getBounds().width / 2;
	float posY = mousePos.y - this->player->getBounds().height / 2;
	if (sf::Event::MouseMoved)
	{
		this->player->setPosition(posX, posY);
	}
	//Create bullets
	if (this->player->canAttack())
	{
		this->fight_sound.play();
		this->player_bullets.push_back(
			new Bullet(
				this->texture["PLAYER_BULLET"],
				mousePos.x ,
				posY,
				0.f,
				-1.f,
				5.f
			));
		this->player_bullets.push_back(
			new Bullet(
				this->texture["PLAYER_BULLET_LEFT"],
				mousePos.x,
				posY,
				-cos(PI/4),
				-sin(PI/4),
				5.f
			));
		this->player_bullets.push_back(
			new Bullet(
				this->texture["PLAYER_BULLET_RIGHT"],
				mousePos.x,
				posY,
				cos(PI/4),
				-sin(PI/4),
				5.f
			));
	}
}


void Game::updateWindowCollision()
{
	//Left
	if (this->player->getBounds().left < 0.f)
	{
		this->player->setPosition(0.f, this->player->getBounds().top);
	}
	//Right
	else if (this->player->getBounds().left + this->player->getBounds().width >= this->window->getSize().x)
	{
		this->player->setPosition(this->window->getSize().x - this->player->getBounds().width, this->player->getBounds().top);
	}
	//Top
	if (this->player->getBounds().top < 0.f)
	{
		this->player->setPosition(this->player->getBounds().left, 0.f);
	}
	//Bottom
	else if (this->player->getBounds().top + this->player->getBounds().height >= this->window->getSize().y)
	{
		this->player->setPosition(this->player->getBounds().left, this->window->getSize().y - this->player->getBounds().height);
	}
}

void Game::updateEnemy()
{
	if (this->spawnTimer >= this->spawnTimerMax)
	{
		this->spawnTimer = 0;
		if (this->enemies.size() < this->maxEnemy)
		{
			this->enemies.push_back(new Enemy(this->window, rand() % ID::NUMBEROFTYPE));
		}
	}
	else
	{
		this->spawnTimer += 1.f;
	}
	for (int i = 0; i < this->enemies.size(); ++i)
	{
		this->enemies[i]->update();
		if (rand() % 300 < 2)
		{
			this->fight_sound.play();
			this->enemy_bullets.push_back(new Bullet(
				this->texture["ENEMY_BULLET"],
				this->enemies[i]->getBounds().left + this->enemies[i]->getBounds().width/2,
				this->enemies[i]->getBounds().top + this->enemies[i]->getBounds().height,
				0.f,
				1.f,
				5.f,
				1.f
			));
			Bullet *left = new Bullet
			(this->texture["ENEMY_BULLET"],
				this->enemies[i]->getBounds().left + this->enemies[i]->getBounds().width / 2,
				this->enemies[i]->getBounds().top + this->enemies[i]->getBounds().height,
				-sin(PI/4),
				cos(PI/4),
				5.f,
				1.f
			);
			left->setRotation(45);
			this->enemy_bullets.push_back(left);

			Bullet* right = new Bullet
			(this->texture["ENEMY_BULLET"],
				this->enemies[i]->getBounds().left + this->enemies[i]->getBounds().width / 2,
				this->enemies[i]->getBounds().top + this->enemies[i]->getBounds().height,
				sin(PI / 4),
				cos(PI / 4),
				5.f,
				1.f
			);
			right->setRotation(-45);
			this->enemy_bullets.push_back(right);
		}
		if (this->enemies[i]->getBounds().top > this->window->getSize().y)
		{
			delete this->enemies[i];
			this->enemies.erase(this->enemies.begin() + i);
		}
		else if (this->player->getBounds().intersects(this->enemies[i]->getBounds()))
		{
			this->player->getDamage(this->enemies[i]->getType() * 5);
			delete this->enemies[i];
			this->enemies.erase(this->enemies.begin() + i);
		}
		
	}
}

void Game::updateBullet()
{
	for (int i = 0; i < this->player_bullets.size(); ++i)
	{
		this->player_bullets[i]->update();
		if (this->player_bullets[i]->getBounds().top + this->player_bullets[i]->getBounds().height < 0)
		{
			delete this->player_bullets[i];
			this->player_bullets.erase(this->player_bullets.begin() + i);
		}
	}
	for (int i = 0; i < this->enemy_bullets.size(); ++i)
	{
		this->enemy_bullets[i]->update();
		if (this->enemy_bullets[i]->getBounds().top > this->window->getSize().y)
		{
			delete this->enemy_bullets[i];
			this->enemy_bullets.erase(this->enemy_bullets.begin() + i);
		}
	}
	
}

void Game::updateCombat()
{
	for (int i = 0; i < this->enemies.size(); ++i)
	{
		bool enemy_removed = false;
		for (int k = 0; k < this->player_bullets.size() && !enemy_removed; ++k)
		{
			if (this->enemies[i]->getBounds().intersects(this->player_bullets[k]->getBounds()))
			{
				this->points += this->enemies[i]->getType() * 2;
				this->enemies[i]->takeDamage(3);
				if (this->enemies[i]->getHealth() <= 0)
				{
					delete this->enemies[i];
					this->enemies.erase(this->enemies.begin() + i);
				}

				delete this->player_bullets[k];
				this->player_bullets.erase(this->player_bullets.begin() + k);
				enemy_removed = true;
				this->shot_sound.play();
			}
		}
	}
	for (int i = 0; i < this->enemy_bullets.size(); ++i)
	{
		if (this->player->getBounds().intersects(this->enemy_bullets[i]->getBounds()))
		{
			delete this->enemy_bullets[i];
			this->enemy_bullets.erase(this->enemy_bullets.begin() + i);
			this->shot_sound.play();
			this->player->getDamage(5);
		}
	}
}

void Game::updateText()
{
	std::stringstream ss;
	ss << "Points: " << this->points << '\n';
		
	this->guiText.setString(ss.str());
}

void Game::updateHealth()
{
	this->shapeHealth.setPosition(this->player->getBounds().left, this->player->getBounds().top - 10.f);
	this->shapeHealthMax.setPosition(this->player->getBounds().left, this->player->getBounds().top - 10.f);
	this->shapeHealth.setSize(sf::Vector2f
		(this->shapeHealthMax.getSize().x * this->player->getHp() / this->player->getHpMax(),
		this->shapeHealthMax.getSize().y));
}

void Game::update()
{
	this->updateInput();

	this->updateBullet();

	this->player->update();

	this->updateEnemy();

	this->updateCombat();

	this->updateWindowCollision();

	this->updateText();

	this->updateHealth();
}

void Game::renderBackground()
{
	this->window->draw(this->worldBackGround);
}

void Game::renderText()
{
	this->window->draw(this->guiText);
	if (this->player->getHp() <= 0)
	{
		this->window->draw(this->endText);
		this->window->draw(this->restartText);
	}
}

void Game::renderHealth()
{
	this->window->draw(this->shapeHealthMax);
	this->window->draw(this->shapeHealth);
}

void Game::render()
{
	this->window->clear();
	//Stuff
	this->renderBackground();

	this->renderText();
	for (int i = 0; i < this->player_bullets.size(); ++i)
	{
		this->player_bullets[i]->render(this->window);
	}
	for (int i = 0; i < this->enemies.size(); ++i)
	{
		this->enemies[i]->render(this->window);
	}
	for (int i = 0; i < this->enemy_bullets.size(); ++i)
	{
		this->enemy_bullets[i]->render(this->window);
	}

	this->player->render(this->window);

	this->renderHealth();

	this->window->display();
}

void Game::run()
{
	this->music.play();
	while (this->window->isOpen())
	{
		this->pollEvents();
		if (this->player->getHp() > 0)
		{
			
			this->update();
		}
		else
		{
			this->music.pause();
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				sf::Vector2i mouse = sf::Mouse::getPosition(*this->window);
				if (this->restartText.getGlobalBounds().contains(mouse.x, mouse.y))
				{
					this->restart();
					this->music.play();
				}
			}

			if (sf::Event::MouseMoved)
			{
				sf::Vector2i mouse = sf::Mouse::getPosition(*this->window);
				if (this->restartText.getGlobalBounds().contains(mouse.x, mouse.y))
				{
					this->restartText.setFillColor(sf::Color(147, 32, 190));
				}
				else
				{
					this->restartText.setFillColor(sf::Color(147, 77, 91));
				}
			}
		}
		this->render();
	}
}
