#pragma once
#include <sfml\Graphics.hpp>
#include <queue>
using namespace std;
using namespace sf;
class Maps
{
private:
	float cell;
	void loadFileToGrid(string filePath);
	vector<vector<int>> mapGrid;
	pair<float, float> getPos(int row, int col);
	vector<pair<float, float> > mapObstaclesPos;
	vector<Sprite> mapObstacles;
	vector<pair<float, float> > foodPos;
	vector<Sprite> food;
	bool didLoadFood = 0;
	//         node           vector (nodes)     
	map <pair<int, int>, vector<pair<int, int>>> connectedCells;

public:
	map<int, bool> eaten; // index => eaten or not 
	pair<float, float> playerRenderPos;
	Maps(string filePath, RenderWindow& window);
	void draw(RenderWindow& window);
	vector<vector<int>> getMapGrid();
	vector<pair<float, float>> getMapObstaclesPos();
	vector<Sprite> getMapObstacles();
	// store food pos
	vector<pair<float, float>> getFoodPos();
	vector<Sprite> getFood();
	void createConnectedCells();
	map <pair<int, int>, vector<pair<int, int>>> getConnectedCells();
};

