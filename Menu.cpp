#include "Menu.h"
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;
using namespace sf;


Menu::Menu(float width, float hight)
{

	// play button

	font.loadFromFile("main_menu/Gatrich-BF63dc6fcf996b7.otf");
	mainMenu[0].setFont(font);
	mainMenu[0].setFillColor(Color::Yellow);
	mainMenu[0].setString("Play");
	mainMenu[0].setCharacterSize(60);
	mainMenu[0].setPosition(Vector2f(40, 150));


	// Dashboard button
	font.loadFromFile("main_menu/Gatrich-BF63dc6fcf996b7.otf");
	mainMenu[1].setFont(font);
	mainMenu[1].setFillColor(Color::White);
	mainMenu[1].setString("Dashboard");
	mainMenu[1].setCharacterSize(60);
	mainMenu[1].setPosition(Vector2f(40, 250));



	// Exit button
	font.loadFromFile("main_menu/Gatrich-BF63dc6fcf996b7.otf");
	mainMenu[2].setFont(font);
	mainMenu[2].setFillColor(Color::White);
	mainMenu[2].setString("Exit");
	mainMenu[2].setCharacterSize(60);
	mainMenu[2].setPosition(Vector2f(40, 350));


	selected = 0;


}


Menu::~Menu() {}



void Menu::setSelected(int n)
{
	selected = n;


}


void Menu::draw(RenderWindow& window)
{
	for (int i = 0; i < 3; i++)
	{
		window.draw(mainMenu[i]);
	}

}


void Menu::moveDown()
{
	if (selected + 1 <= 3)
	{
		mainMenu[selected].setFillColor(Color::White);
		selected++;
		if (selected == 3)
		{
			selected = 0;
		}

		mainMenu[selected].setFillColor(Color::Yellow);
	}


}

void Menu::moveUp()
{

	if (selected - 1 >= -1)
	{
		mainMenu[selected].setFillColor(Color::White);
		selected--;
		if (selected == -1)
		{
			selected = 2;
		}

		mainMenu[selected].setFillColor(Color::Yellow);
	}


}
