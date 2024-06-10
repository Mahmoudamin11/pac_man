#include "Dashboard.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include<vector>
#include <fstream>
#include<map>
#include<string>
#include <sstream>
using namespace std;
using namespace sf;


Dashboard::Dashboard(int x)
{
	font.loadFromFile("main_menu/Gatrich-BF63dc6fcf996b7.otf");
	for (int i = 0; i < 55 ; i++)
	{
		text[i].setFont(font);
		text[i].setCharacterSize(40);
		text[i].setFillColor(Color::Yellow);	
	}
	



	infile.open("Dashboardf.txt", ios::in);



	if (infile.is_open()) {
		while (getline(infile, line, '*'))
		{
			std::istringstream iss;
			iss.str(line);
			std::string name;
			int score;
			iss >> name >> score;
			mutmap.insert({ score, line }); // map used 
		}
	
	}
	else {
		std::cerr << "Unable to open file\n";
	
	}
	text[0].setString("Name  Score");
	text[0].setPosition(50, 0 );

	bool flag = true;   // flag for first iterate 
	int i = 0;
	int posy = 50;

	for (auto it = mutmap.end(); it != mutmap.begin(); it--)
	{		
		// handle map.end     -----> map.end point to it after last element in map
		if (flag)
		{
			it--;
			flag = false;
		}
		i++;
		posy += 50;
		text[i].setString(it->second);
		text[i].setPosition(50, posy);

	}
	

}


////////////////////////////////////////////////////////////////////////////
// update and fix map the conflict was mutmap.end point to outside map by one postion
//  and at the end of loop the mutmab.begin wasnot accessed due to (!=) and we solve this by add temp with very low score to txt file 
 

