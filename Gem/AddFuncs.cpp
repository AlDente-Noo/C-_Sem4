#include "AddFuncs.h"
#include <iostream>
#include <memory>
#include <string>
#include <vector>
vector<vector<shared_ptr<Gem>>> getGems(sf::RenderWindow *window, int gemSize, vector<vector<shared_ptr<Gem>>> gems) {
	float x, y;
	Colors color;
	sf::Vector2u size = window->getSize();
	unsigned int width = size.x;
	unsigned int height = size.y;
	int xGems = width / gemSize;
	int yGems = (height - 100) / gemSize;
	for (int i = 0; i < xGems; i++) {
		x = (i+1) * gemSize;
		for (int j = 0; j < yGems; j++) {
			y = double(j * gemSize);
			auto pGem = std::make_shared<Gem>(Gem(x, y, Colors::BLUE, gemSize));
			gems[i][j] = pGem;
		}
	}
	return gems;
}