#pragma once
#include <cmath>
#include <vector>
#include <set>
#include "SFML/Graphics.hpp"
#include "Gem.h"
using namespace std;
class Field : public sf::IntRect {
public:
	Field(sf::RenderWindow* window, const int gemSize);
	void toBe();
	void toDraw();
	sf::RenderWindow* Window;
private:
	
	int nGemsX, nGemsY;
	vector <vector<shared_ptr<Gem>>> Gems;
};