#include "Maps.h"
#include <sfml\Graphics.hpp>
#include <queue>
#include <fstream>
#include <iostream>
using namespace std;
using namespace sf;


Maps::Maps(string filePath, RenderWindow& window) {
    cell = 32;
    loadFileToGrid(filePath);
    createConnectedCells(); // bfs
}

pair<float, float> Maps::getPos(int row, int col) {

    float x = (col * cell) - (cell);
    float y = (row * cell) - (cell);
    return { x, y };
}

void Maps::draw(RenderWindow& window) {

    // obstacles
    Texture obstext;
    obstext.loadFromFile("obs.png");

    Texture foodtext;
    foodtext.loadFromFile("cppLogo.png");

    // obstacles 
    for (int i = 0; i < mapObstaclesPos.size(); i++) {
        Sprite obs;
        obs.setTexture(obstext);
        float x = mapObstaclesPos[i].first;
        float y = mapObstaclesPos[i].second;
        obs.setPosition(x, y);
        mapObstacles.push_back(obs);
        window.draw(obs);
    }

    if (!didLoadFood) {
        for (int i = 0; i < foodPos.size(); i++) {
            Sprite f;
            f.setTexture(foodtext);
            float x = foodPos[i].first;
            float y = foodPos[i].second;
            f.setPosition(x, y);
            food.push_back(f);
        }
        didLoadFood = 1;
    }

    for (int i = 0; i < food.size(); i++) {
        if (eaten[i]) {
            food[i].setScale(0, 0);
            continue;
        }
        window.draw(food[i]);
    }

}

vector<vector<int>> Maps::getMapGrid()
{
    return mapGrid;
}

vector<pair<float, float>> Maps::getMapObstaclesPos() {
    return mapObstaclesPos;
}

vector<Sprite> Maps::getMapObstacles() {
    return mapObstacles;
}

void Maps::loadFileToGrid(string filePath) {
    ifstream mapFile(filePath);
    string line;
    int rows = 0;
    while (getline(mapFile, line)) {
        vector<int> row;
        rows++;
        for (int i = 0; i < line.size(); i++)
        {

            int x = line[i] - '0'; // char to num 1 2 3
            auto pr = getPos(rows, i + 1); // calc pos in x,y
            // obstacle 
            if (x == 1) {
                mapObstaclesPos.push_back({ pr.first, pr.second });
            }
            // food
            else if (x == 2) {
                // store food 
                foodPos.push_back({ pr.first, pr.second });
            }
            // initial pos of pacman 3 
            else {
                playerRenderPos = { pr.first, pr.second };
            }
            row.push_back(x);
        }
        mapGrid.push_back(row);
    }
}


// get food func 

vector<Sprite> Maps::getFood() {
    return food;
}

vector<pair<float, float>> Maps::getFoodPos() {
    return foodPos;
}

void Maps::createConnectedCells() {
    // mapGrid 
    for (int i = 1; i < 19; i++) {
        for (int j = 1; j < 19; j++) {
            if (mapGrid[i][j] == 2 || mapGrid[i][j] == 3) {
                if (mapGrid[i + 1][j] == 2 || mapGrid[i + 1][j] == 3) {
                    connectedCells[{i, j}].push_back({ i + 1, j });
                }
                if (mapGrid[i - 1][j] == 2 || mapGrid[i - 1][j] == 3) {
                    connectedCells[{i, j}].push_back({ i - 1, j });
                }
                if (mapGrid[i][j + 1] == 2 || mapGrid[i][j + 1] == 3) {
                    connectedCells[{i, j}].push_back({ i, j + 1 });
                }
                if (mapGrid[i][j - 1] == 2 || mapGrid[i][j - 1] == 3) {
                    connectedCells[{i, j}].push_back({ i, j - 1 });
                }
            }
        }
    }
}

map <pair<int, int>, vector<pair<int, int>>> Maps::getConnectedCells() {
    return connectedCells;
}
