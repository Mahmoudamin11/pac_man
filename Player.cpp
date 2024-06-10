#include "player.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>


using namespace std;
using namespace sf;

float cell = 32.0f;

float pacman_speed = 2.0f;

player::player(Texture& player_Texture, float left, float top, float height, float width, pair<float, float> renderPos)
{
    player_sprite.setTexture(player_Texture);
    player_sprite.setTextureRect(IntRect(32, 32, 32, 32));
    player_sprite.setScale(0.7, 0.7);
    player_sprite.setPosition(renderPos.first, renderPos.second);
    this->health = 3;
    this->score = 0;
    this->height_indecator = 0;
    this->width_indecator = 0;
    this->height = height;
    this->left = left;
    this->width = width;
    this->top = top;
    pos.first = renderPos.first;
    pos.second = renderPos.second;
    renderPostion.first = renderPos.first;
    renderPostion.second = renderPos.second;
    direction = -1;
}

void player::Animation() {

    // left
    if (this->direction == 2)
    {
        this->height_indecator = 2;
        this->width_indecator++;
        this->width_indecator %= 5;
        player_sprite.setTextureRect(IntRect(width_indecator * this->left, height_indecator * this->top, this->width, this->height));
    }
    // right 
    else if (this->direction == 0)
    {
        this->height_indecator = 0;
        this->width_indecator++;
        this->width_indecator %= 5;
        player_sprite.setTextureRect(IntRect(this->width_indecator * this->left, (this->height_indecator * this->top), this->width, this->height));
    }
    // up 
    else if (this->direction == 1) // down 
    {
        this->height_indecator = 1;
        this->width_indecator++;
        this->width_indecator %= 5;
        player_sprite.setTextureRect(IntRect(this->width_indecator * this->left, (this->height_indecator * this->top), this->width, this->height));
    }
    // down 
    else if (this->direction == 3)
    {
        this->height_indecator = 3;
        this->width_indecator++;
        this->width_indecator %= 5;
        player_sprite.setTextureRect(IntRect(this->width_indecator * this->left, (this->height_indecator * this->top), this->width, this->height));
    }
}

void player::update(vector<vector<int>> mapGrid, float dt, RenderWindow& window, vector<Sprite> obs, bool caught) {

    if (!caught) {
        Animation();
        // up
        if (direction == 1 && !collision(pos.first, pos.second - pacman_speed, mapGrid)) {
            Move(0, -1 * pacman_speed * dt * 62.5f, dt * 62.5f);
        }


        // right 
        else if (direction == 0 && !collision(pacman_speed + pos.first, pos.second, mapGrid)) {
            Move(pacman_speed * dt * 62.5f, 0, dt * 62.5f);
        }

        // left 
        else if (direction == 2 && !collision(pos.first - pacman_speed, pos.second, mapGrid)) {
            Move(-1 * pacman_speed * dt * 62.5f, 0, dt * 62.5f);
        }
        // down 
        else if (direction == 3 && !collision(pos.first, pacman_speed + pos.second, mapGrid)) {
            Move(0, pacman_speed * dt * 62.5f, dt * 62.5f);
        }
    }

    else {
        decreaseHealth();
        player_sprite.setPosition(renderPostion.first, renderPostion.second); // render
        pos.first = renderPostion.first;
        pos.second = renderPostion.second;
        direction = -1;
        caught = 0;
    }
    Event evnt;
    while (window.pollEvent(evnt))
    {

        if (evnt.type == Event::KeyPressed) {
            if (evnt.key.code == Keyboard::Escape)
            {

                this->direction = -1;
                this->movement = false;

            }
            if (evnt.key.code == Keyboard::Up)
            {
                this->direction = 1;
            }
            else if (evnt.key.code == Keyboard::Down)
            {
                this->direction = 3;
            }
            else if (evnt.key.code == Keyboard::Left)
            {
                this->direction = 2;

            }
            else if (evnt.key.code == Keyboard::Right)
            {
                this->direction = 0;
            }
        }
    }

}

bool player::collision(float posx, float posy, vector<vector<int>> mapGrid) {
    bool willCrash = 0;
    float cell_x = posx / static_cast<float>(cell); // cell pos 32 
    float cell_y = posy / static_cast<float>(cell);

    switch (direction) {

    case 0: // right
        cell_x = ceil(cell_x);
        cell_y = round(cell_y);
        break;
    case 2:// left 
        cell_x = floor(cell_x);
        cell_y = round(cell_y);
        break;
    case 1: // up 
        cell_y = floor(cell_y);
        cell_x = round(cell_x);
        break;
    case 3:// down 
        cell_y = ceil(cell_y);
        cell_x = round(cell_x);
        break;
    }

    if (mapGrid[(cell_y)][(cell_x)] == 1) { // obstacle 
        willCrash = 1;
    }

    // food = 2

    return willCrash;
}

void player::Move(float posX, float posY, float dt) {
    if (posX != 0) {
        pos.first += posX;
        player_sprite.setPosition((pos.first), pos.second);
    }
    else if (posY != 0) {
        pos.second += posY;
        player_sprite.setPosition(pos.first, pos.second);
    }

}

void player::eat()
{
    this->score++;
}

int player::getScore() {
    return this->score;
}

Sprite player::getPlayerSprite() {
    return player_sprite;
}

void player::draw(RenderWindow& window) {
    window.draw(player_sprite);
}

int player::getDirection() {
    return direction;
}

void player::decreaseHealth() {
    if (health > 0)
        health--;
    // loose func 
    else {}
}

int player::getHealth() {
    return health;
}

void player::reset(pair<float, float> newRenderPos) {
    score = 0;
    health = 3;
    player_sprite.setPosition(newRenderPos.first, newRenderPos.second); // render
    pos.first = newRenderPos.first;
    pos.second = newRenderPos.second;
    renderPostion = newRenderPos;
    direction = -1;
}