#pragma once
#include <SFML/Graphics.hpp>

#include "Ghost.h"
#include "player.h"

using namespace sf;
using namespace std;

class LoseOrWin
{
	int widthIndicator = 0;

public:
	bool checkLose(player&, Ghost&, Ghost&, Ghost&, Ghost&);

};

