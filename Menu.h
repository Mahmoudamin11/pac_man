#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;
using namespace sf;

class Menu
{
public:
	Text mainMenu[3];
	Menu(float width, float hight);
	void draw(RenderWindow& window);
	void moveUp();
	void moveDown();
	void setSelected(int n);
	int  pressed()
	{
		return selected;
	}
	~Menu();
private:
	int selected;
	Font font;
};

