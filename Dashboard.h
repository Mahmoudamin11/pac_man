#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include<vector>
#include <fstream>
#include<map>
#include<string>
using namespace std;
using namespace sf;


class Dashboard
{

public:
	Dashboard(int);
	Texture historyTexture;
	Sprite	historySprite;
	Text text[100];
	ifstream infile;
	string line ;
	multimap< int, string > mutmap;



private:
	Font font; 

};

