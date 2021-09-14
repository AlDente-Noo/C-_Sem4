#include "field.h"
#include <list>
#include <iterator>
using namespace sf;
Field::Field(sf::RenderWindow* window, const int gemSize) {
	Window = window;
	vector <vector<shared_ptr<Gem>>> gems;
	float x, y;
	sf::Vector2u size = window->getSize();
	unsigned int width = size.x;
	unsigned int height = size.y;
	int xGems = width / gemSize;
	int yGems = height / gemSize;
	nGemsX = xGems; 
	nGemsY = yGems;
	for (int i = 0; i < xGems; i++) {
		x = (i) * gemSize;
		vector <shared_ptr<Gem>>  tmp;
		for (int j = 0; j < yGems; j++) {
			y = double(j * gemSize);
			auto pGem = std::make_shared<Gem>(Gem(x, y, gemSize));
			tmp.push_back(pGem);
		}
		gems.push_back(tmp);
	}
	Gems = gems;
}
void Field::toBe()
{
	int i,j = 0;
		for (i = 0; i < nGemsX; i++) {
			vector <shared_ptr<Gem>> tmpVec = Gems.at(i);
			for (j = 0; j < nGemsY; j++) {
				auto tmpGem = tmpVec.at(j); 
				if (i < nGemsX - 1) {
					if (this->Gems[i + 1][j]->getFillColor() != sf::Color::White)
						tmpGem->deleteColors(*this->Gems[i + 1][j]);
				}
				if (j < nGemsY - 1) {
					if (this->Gems[i][j + 1]->getFillColor() != sf::Color::White)
						tmpGem->deleteColors(*this->Gems[i][j + 1]);
				}
				if (j >= 1) {
					if (this->Gems[i][j - 1]->getFillColor() != sf::Color::White) 
						tmpGem->deleteColors(*this->Gems[i][j - 1]);
				}
				if (i >= 1) {
					if (this->Gems[i - 1][j]->getFillColor() != sf::Color::White)
						tmpGem->deleteColors(*this->Gems[i - 1][j]);
				}
				tmpGem->chooseColor();
			}
		}
}

void Field::toDraw()
{
	for (int i = 0; i < nGemsX; i++) {
		vector <shared_ptr<Gem>> tmpVec = Gems.at(i);
		for (int j = 0; j < nGemsY; j++) {
			auto tmpGem = tmpVec.at(j);
			Window->draw(*tmpGem);
		}
	}
}
