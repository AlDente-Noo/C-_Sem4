#pragma once
#include <cmath>
#include <vector>
#include <set>
#include "SFML/Graphics.hpp"
#include "Gem.h"
#include <iostream>
#include "bonus.h"
using namespace std;
class Gem;
class Field : public sf::IntRect {
public:
	Field(sf::RenderWindow* window, const int gemSize);
	void toBe();
	void toDraw()const;
	bool changeGems(const sf::Vector2i frstBlckCoord, const sf::Vector2i scndBlckCoord); //true if gems are close false if not
	bool checkField();
	void findFigureToDrop(int i, int j, set<vector<int>> &gemsCoords);
	void mainDrop(const set<vector<int>>& gemCoords);
	void dropOneColmn(int i, int j,const set<vector<int>>&  gemsCoords, int flag);
	sf::Vector2i ChooseRandInRadius(int radius, sf::Vector2i pos);
private:
	sf::RenderWindow* Window;
	int _gemSize;
	int nGemsX, nGemsY;
	vector <vector<shared_ptr<Gem>>> Gems;
};