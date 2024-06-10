#pragma once
#include <sfml\Graphics.hpp>
#include <iostream>
#include <stack>
#include "player.h"

using namespace std;
using namespace sf;
class Ghost
{
private:
	Sprite ghost_sprite;
	float top;
	float left;
	float height;
	float width;
	int height_indecator;
	int width_indecator;
	int direction;
	pair<float, float> pos;
	float ghost_speed;
	float cell = 32.0f;
	int changeDir = 0;
	int level;
	pair<float, float> renderPosition;


public:
	Ghost(Texture&, pair<float, float> renderPos);
	bool collision(float, float, vector<vector<int>>);
	void update(vector<vector<int>>, float dt, RenderWindow&, map<pair<int, int>, vector<pair<int, int>>>, player&, bool);
	void createGhost(Texture&, pair<float, float> renderPos);
	Sprite getGhostSprite();
	void draw(RenderWindow&);
	bool randomChance();
	vector<int> removePrevCell(vector<int> trueDir);
	void selectLevel(int, vector<vector<int>>);
	stack <int> getShortestPath(map< pair<int, int>, vector<pair<int, int>> >, player&);
	pair<int, int> convert_ghost_pos_toIndecies();
	pair<int, int> convert_pacman_pos_toIndecies(player&);
	stack <int> bfs(pair<int, int>, pair<int, int>, map< pair<int, int>, vector<pair<int, int>> >&);
	stack <int> get_Path_From_Parent_Map(pair<int, int>, pair<int, int>, map<pair<int, int>, pair<int, int>>&);
	void reset();
};

