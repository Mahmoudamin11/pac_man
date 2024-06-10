#pragma once
#include <SFML/Graphics.hpp>
using namespace std;
#include <vector>

class player
{

	sf::Sprite player_sprite;
	float top;
	float left;
	float height;
	float width;
	int health = 3;
	int score;
	int height_indecator;
	int width_indecator;
	int direction; // left by default 
	pair<float, float> pos;
	int changeDir = 0;
	bool rightDir = 1;
	bool leftDir = 1;
	bool upDir = 1;
	bool downDir = 1;
	pair<float, float> renderPostion;

public:
	bool movement = 1;
	player(sf::Texture&, float, float, float, float, pair<float, float>);
	void Animation();
	void update(vector<vector<int>>, float dt, sf::RenderWindow&, vector<sf::Sprite>, bool);
	bool collision(float, float, vector<vector<int>>);
	void Move(float, float, float);
	void eat();
	int getScore();
	sf::Sprite getPlayerSprite();
	void draw(sf::RenderWindow&);
	int getDirection();
	void decreaseHealth();
	int getHealth();
	void reset(pair<float, float>);
};