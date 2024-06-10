#include "PauseMenu.h"
#include<SFML/Graphics.hpp>
using namespace std;
using namespace sf;


pause_menu::pause_menu(float width, float hight)
{

	// play button

	font.loadFromFile("main_menu/Gatrich-BF63dc6fcf996b7.otf");
	pausemenu[0].setFont(font);
	pausemenu[0].setFillColor(Color::Yellow);
	pausemenu[0].setString("continue");
	pausemenu[0].setCharacterSize(50);
	pausemenu[0].setPosition(Vector2f(40, 150));


	// Dashboard button
	font.loadFromFile("main_menu/Gatrich-BF63dc6fcf996b7.otf");
	pausemenu[1].setFont(font);
	pausemenu[1].setFillColor(Color::White);
	pausemenu[1].setString("play again");
	pausemenu[1].setCharacterSize(50);
	pausemenu[1].setPosition(Vector2f(40, 250));



	// Exit button
	font.loadFromFile("main_menu/Gatrich-BF63dc6fcf996b7.otf");
	pausemenu[2].setFont(font);
	pausemenu[2].setFillColor(Color::White);
	pausemenu[2].setString("main menu");
	pausemenu[2].setCharacterSize(50);
	pausemenu[2].setPosition(Vector2f(40, 350));


	selected = 0;


}

void pause_menu::draw(RenderWindow& window)
{
	for (int i = 0; i < 3; ++i)
	{
		window.draw(pausemenu[i]);
	}
}

void pause_menu::moveUp()
{
	if (selected - 1 >= 0)
	{
		pausemenu[selected].setFillColor(Color::White);
		selected--;
		pausemenu[selected].setFillColor(Color::Yellow);
	}
}

void pause_menu::moveDown()
{
	if (selected + 1 <= 2)
	{

		pausemenu[selected].setFillColor(Color::White);
		selected++;
		pausemenu[selected].setFillColor(Color::Yellow);

	}
}



void pause_menu::setSelected(int n)
{
	selected = n;
}



pause_menu::~pause_menu()
{
}
