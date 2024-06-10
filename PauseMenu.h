#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;
using namespace sf;

class pause_menu
{
public:
	Text pausemenu[3];
	pause_menu(float width, float hight);
	void draw(RenderWindow& window);
	void moveUp();
	void moveDown();
	void setSelected(int n);
	int  pressed()
	{
		return selected;
	}
	~pause_menu();
private:
	int selected;
	Font font;
};

