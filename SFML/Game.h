#pragma once

#include <iostream>
#include <map>
#include <vector>
#include <sstream>
#include <cmath>
#include "Player.h"
#include "Enemy.h"
class Game
{
private:
	sf::RenderWindow* window;
	//Resource 
	std::map<std::string, sf::Texture*> texture;
	std::vector<Bullet*> player_bullets;
	std::vector<Bullet*> enemy_bullets;
	//Game object
	Player* player;
	std::vector<Enemy*> enemies;
	//Enemy
	float spawnTimer;
	float spawnTimerMax;
	//Background 
	sf::Texture worldBackGroundText;
	sf::Sprite worldBackGround;
	//Sound
	sf::SoundBuffer shot_buffer;
	sf::Sound shot_sound;
	
	sf::SoundBuffer fight_buffer;
	sf::Sound fight_sound;

	sf::Music music;

	sf::Font font;
	sf::Text guiText;
	sf::Text endText;
	sf::Text restartText;
	//System
	unsigned points;
	int maxEnemy;
	//Health
	sf::RectangleShape shapeHealth, shapeHealthMax;
	//Private function
	void initWorld();
	void initWindow();
	void initPlayer();
	void initEnemies();
	void initTexture();
	void initSound();
	void initText();
	void initHealth();
	void initSystem();
public:
	//Constructor and Destructor
	Game();
	virtual ~Game();


	//Function
	void pollEvents();
	void restart();

	void updateInput();
	void updateWindowCollision();
	void updateEnemy();
	void updateBullet();
	void updateCombat();
	void updateText();
	void updateHealth();
	void update();


	void renderBackground();
	void renderText();
	void renderHealth();
	void render();

	void run();

};