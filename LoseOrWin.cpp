#include "LoseOrWin.h"
#include <SFML/Graphics.hpp>
#include "Ghost.h"
using namespace sf;
using namespace std;
bool LoseOrWin::checkLose(player& pacman, Ghost& red, Ghost& pink, Ghost& blue, Ghost& orange) {
	if (pacman.getPlayerSprite().getGlobalBounds().intersects(red.getGhostSprite().getGlobalBounds())) {
		return true; // lose 
	}
	if (pacman.getPlayerSprite().getGlobalBounds().intersects(pink.getGhostSprite().getGlobalBounds())) {
		return true; // lose 
	}
	if (pacman.getPlayerSprite().getGlobalBounds().intersects(blue.getGhostSprite().getGlobalBounds())) {
		return true; // lose 
	}
	if (pacman.getPlayerSprite().getGlobalBounds().intersects(orange.getGhostSprite().getGlobalBounds())) {
		return true; // lose 
	}
	// render pos 
}



