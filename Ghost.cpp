#include "Ghost.h"
#include <sfml\Graphics.hpp>
#include <queue>
#include <stack>
#include <map>
#include <vector>
#include <iostream>
#include "player.h"
using namespace std;
using namespace sf;





Ghost::Ghost(Texture& texture, pair<float, float> renderPos) {
    createGhost(texture, renderPos);
    this->height_indecator = 0;
    this->width_indecator = 0;
    this->height = height;
    this->left = left;
    this->width = width;
    this->top = top;
    pos.first = renderPos.first;
    renderPosition.first = renderPos.first;
    renderPosition.second = renderPos.second;
    pos.second = renderPos.second;
    direction = -1;

}

void Ghost::update(vector<vector<int>> mapGrid, float dt, RenderWindow& window, map< pair<int, int>, vector<pair<int, int>> > connectedCells, player& pacman, bool caught) {

    // set the frames according to the level (easy || medium || hard)
    int xFrame = level == 2 || level == 3 ? 16 : 32;

    if (!caught) {
        if (changeDir % xFrame == 0) {
            if (level == 1 || level == 2) {
                bool crashright = collision(ghost_speed + pos.first, pos.second, mapGrid); //0 => no coll 
                bool crashleft = collision(pos.first - ghost_speed, pos.second, mapGrid);
                bool crashup = collision(pos.first, pos.second - ghost_speed, mapGrid);
                bool crashdown = collision(pos.first, ghost_speed + pos.second, mapGrid);

                vector<int> trueDir;
                //  only store the available  direction 
                if (!crashup) trueDir.push_back(1);
                if (!crashright) trueDir.push_back(0);
                if (!crashdown) trueDir.push_back(3);
                if (!crashleft) trueDir.push_back(2);

                // Randomly change direction 
                if (!trueDir.empty()) {
                    int random;
                    // if it's the only direction then you have to go back 
                    if (trueDir.size() == 1) {
                        random = rand() % trueDir.size();
                        // in this line trueDir[random] is the new direction and the direction is the old one 
                        direction = trueDir[random];
                    }
                    // more choices 
                    else {
                        vector<int> neverGoBack = removePrevCell(trueDir);
                        random = rand() % neverGoBack.size();
                        direction = neverGoBack[random];
                    }
                }
            }
            else {

                stack<int> fastPath = getShortestPath(connectedCells, pacman);
                direction = fastPath.top();
            }
        }
    }

    else {
        direction = -1;
        ghost_sprite.setPosition(renderPosition.first, renderPosition.second);
        pos.first = renderPosition.first;
        pos.second = renderPosition.second;
        caught = 0;
    }


    switch (direction) {
    case 0:
        pos.first = ((ghost_speed + pos.first));
        break;
    case 1:
        pos.second = pos.second - ghost_speed;
        break;
    case 2:
        pos.first = pos.first - ghost_speed;
        break;
    case 3:
        pos.second = pos.second + ghost_speed;
        break;
    }
    changeDir++;
}



bool Ghost::collision(float posx, float posy, vector<vector<int>> mapGrid) {
    bool willCrash = 0;
    float cell_x = posx / static_cast<float>(cell); // cell  = 32 
    float cell_y = posy / static_cast<float>(cell);
    int x, y;
    // right 
    if (posx > pos.first) {
        x = (pos.first / 32) + 1; // next cell 
        y = pos.second / 32;
    }
    // left 
    else if (posx < pos.first) {
        x = (pos.first / 32) - 1; // prev cell 
        y = pos.second / 32;
    }
    // up 
    else if (posy < pos.second) {
        x = (pos.first / 32);
        y = (pos.second / 32) - 1; // prev cell 
    }
    //down 
    else if (posy > pos.second) {
        x = (pos.first / 32);
        y = (pos.second / 32) + 1; // next cell 
    }

    // 

    if (cell_y <= 0 || cell_x <= 0 || cell_y >= 18 || cell_x >= 18)
        return true; // out of the map 

    if (mapGrid[y][x] == 1) { // obstacle 
        willCrash = 1;
    }

    return willCrash;
}


vector<int> Ghost::removePrevCell(vector<int> allDirs) {
    vector <int> availbleDirs;
    for (int dir : allDirs) {
        if (abs(dir - direction) != 2) // if it isn't the opposite direction of the old one 
            availbleDirs.push_back(dir);
    }
    return availbleDirs; // new directions without the opposite direction 
}

void Ghost::createGhost(Texture& texture, pair<float, float> renderPos) {
    this->ghost_sprite.setTexture(texture);
    this->ghost_sprite.setPosition(renderPos.first, renderPos.second);
}

Sprite Ghost::getGhostSprite() {
    return ghost_sprite;
}

void Ghost::draw(RenderWindow& window) {
    ghost_sprite.setPosition(pos.first, pos.second);
    window.draw(this->ghost_sprite);
}

bool Ghost::randomChance() {
    return (rand() % 10) < 3;
}

void Ghost::selectLevel(int lev, vector<vector<int>> mapGrid) {
    level = lev;
    if (level == 1) {
        this->ghost_speed = 1.0f;
    }
    else if (level == 2 || level == 3) {
        this->ghost_speed = 2.0f;
    }
}


stack<int> Ghost::getShortestPath(map< pair<int, int>, vector<pair<int, int>> > connectedCells, player& pacman) {
    // get pos (ghost , pac) as indecies of cells 
    pair<int, int> ghostPos = convert_ghost_pos_toIndecies();

    pair<int, int>  pacPos = convert_pacman_pos_toIndecies(pacman);

    //          start   target   relationMap 
    return bfs(ghostPos, pacPos, connectedCells);
}

pair<int, int> Ghost::convert_ghost_pos_toIndecies() {
    return { ghost_sprite.getPosition().y / 32 , ghost_sprite.getPosition().x / 32 };
}

pair<int, int> Ghost::convert_pacman_pos_toIndecies(player& pac) {

    int y = 0, x = 0;
    y = round(pac.getPlayerSprite().getPosition().y / 32);
    x = round(pac.getPlayerSprite().getPosition().x / 32);
    return { y  , x };
}

stack<int>  Ghost::bfs(pair<int, int>ghostCell, pair<int, int>pacCell, map< pair<int, int>, vector<pair<int, int>> >& connectedCells) {
    queue < pair<int, int> > q;
    map< pair<int, int>, bool > vis;
    pair<int, int> parent = ghostCell;
    map<pair<int, int>, pair<int, int>> getParent;
    q.push(parent);
    vis[parent] = true;
    bool finished = false;


    while (!q.empty()) {
        pair<int, int> curr = q.front();
        q.pop();
        for (pair<int, int> nbr : connectedCells[curr]) {
            if (!vis[{nbr.first, nbr.second}]) {
                getParent[{nbr.first, nbr.second}] = { curr.first , curr.second };
                vis[nbr] = true;
                if (nbr == pacCell) {
                    finished = true;
                    break;
                }
                q.push(nbr);
            }
        }
        if (finished) break;
    }

    // convert map of parents into real path 
    return get_Path_From_Parent_Map(pacCell, ghostCell, getParent);

}

stack<int> Ghost::get_Path_From_Parent_Map(pair<int, int>pacCell, pair<int, int>ghostCell, map<pair<int, int>, pair<int, int>>& getParent) {

    stack<int> path;
    pair<int, int> currNode = pacCell;
    while (currNode != ghostCell) {
        int childXCell = currNode.first; // i
        int childYCell = currNode.second; // j
        int parentXCell = getParent[currNode].first; // i
        int parentYCell = getParent[currNode].second; // j
        // parent is under the child 
        if (parentXCell == childXCell + 1) {
            path.push(1); // move up to go to pacman 
        }
        // parent is above the child means to go to the child we moved right (0) 
        else if (parentXCell == childXCell - 1) {
            path.push(3); // left to fo to child 
        }
        // parent is on the right of  the child means to go to the child we moved up (1) 
        else if (parentYCell == childYCell + 1) {
            path.push(2); // left to go to child 
        }
        // parent is on the left of the  child means to go to the child we moved down (3) 
        else if (parentYCell == childYCell - 1) {
            path.push(0); // right to fo to child 
        }
        currNode = getParent[currNode];
    }

    return path;
}

void Ghost::reset() {
    direction = -1;
    ghost_sprite.setPosition(renderPosition.first, renderPosition.second);
    pos.first = renderPosition.first;
    pos.second = renderPosition.second;
}