#pragma once
#include <cmath>
#include <vector>
#include <set>
#include "SFML/Graphics.hpp"
#include "Gem.h"
using namespace std;
class Field : public sf::IntRect {
public:
	Field(sf::RenderWindow* window);
	void Fill();
private:
	sf::RenderWindow* Window;
	vector<vector<shared_ptr<Gem>>> Gems;
};