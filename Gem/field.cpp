#include "field.h"
#include <list>
#include <iterator>
#include <ctime>
#include <random>
#include <iostream>
#define COMMON_DROP 1
#define BONUS_DROP 2
#define BONUS_DROP_RADIUS 3
using namespace sf;
Field::Field(sf::RenderWindow* window, const int gemSize) {
	Window = window;
	vector <vector<shared_ptr<Gem>>> gems;
	float x, y;
	sf::Vector2u size = window->getSize();
	width = size.x;
	height = size.y;
	left = 0;
	top = 0;
	_gemSize = gemSize;
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

void Field::toDraw() const
{
	for (int i = 0; i < nGemsX; i++) {
		vector <shared_ptr<Gem>> tmpVec = Gems.at(i);
		for (int j = 0; j < nGemsY; j++) {
			auto tmpGem = tmpVec.at(j);
			Window->draw(*tmpGem);
		}
	}
	Window->display();
}

bool Field::changeGems(Vector2i frstBlckCoord, Vector2i scndBlckCoord)
{
	int frstGemX = (int)(frstBlckCoord.x / (width / nGemsX));
	int frstGemY = (int)(frstBlckCoord.y / (height / nGemsY));
	int scndGemX = (int)(scndBlckCoord.x / (width / nGemsX));
	int scndGemY = (int)(scndBlckCoord.y / (height / nGemsY));
	auto frstColor = Gems[frstGemX][frstGemY]->getFillColor();
	auto scndColor = Gems[scndGemX][scndGemY]->getFillColor();
	if ((frstGemX == scndGemX - 1 && frstGemY == scndGemY)
		|| (frstGemX == scndGemX + 1 && frstGemY == scndGemY)
		|| (frstGemY == scndGemY - 1 && frstGemX == scndGemX)
		|| (frstGemY == scndGemY + 1 && frstGemX == scndGemX)) {
		Gems[frstGemX][frstGemY]->setFillColor(scndColor);
		Gems[scndGemX][scndGemY]->setFillColor(frstColor);
		return true;
	}
	else
		return false;
}

bool Field::checkField()
{
	set<vector<int>> ::iterator it;
	
	for (int i = 0; i < nGemsX; i++) {

		for (int j = 0; j < nGemsY; j++) {
			std::set<vector<int>>gemsCoords;
			findFigureToDrop(i, j, gemsCoords);
			if (gemsCoords.size() >= 3) {
				mainDrop(gemsCoords);
				if (gemsCoords.size() >= COMBO_SIZE_FOR_BONUS)
				{
					auto key = *gemsCoords.begin();
					auto bonus_pos = ChooseRandInRadius(BONUS_DROP_RADIUS, { key[0],key[1] });
					Gems[bonus_pos.x][bonus_pos.y]->SetRandomBonus();
				}
				for (auto key : gemsCoords) {
					sf::Vector2i position{ key[0],key[1] };
 					if (Gems[position.x][position.y]->HasBonus()) {
						auto bonus_targets = Gems[position.x][position.y]->
							ActivateBonus(sf::Vector2i(nGemsX, nGemsY), position);
						if (bonus_targets.size() >= BOMB_TARGETS) {
							for (auto drop : bonus_targets){
								std::cout << "Bomb has been planted to gem " << drop.x << "\t" << drop.y << endl;
								sf::sleep(sf::seconds(0.5));
								dropOneColmn(drop.x, drop.y, gemsCoords, BONUS_DROP);
							}
						}
						else if (bonus_targets.size() == PAINT_TARGETS) {
							for (auto drop : bonus_targets) {
								std::cout << "Repainting gem " << drop.x << "\t" << drop.y << endl;
								sf::sleep(sf::seconds(0.5));
								Gems[drop.x][drop.y]->setFillColor(Gems[position.x][position.y]->getFillColor());

							}
						}
					}
				}
				return true;
			}
		}
	}
	return false;
}
void Field::findFigureToDrop(int i, int j, set<vector<int>>& gemsCoords)
{
	if (gemsCoords.find({ i  , j }) != gemsCoords.end())
		return;
	gemsCoords.insert({ i,j });
	if (i != nGemsX - 1 && Gems[i][j]->getFillColor() == Gems[i + 1][j]->getFillColor())
	{
		findFigureToDrop(i+ 1, j , gemsCoords);
	}
	if (j != nGemsY - 1 && Gems[i][j]->getFillColor() == Gems[i][j + 1]->getFillColor()) {
		findFigureToDrop(i, j + 1, gemsCoords);
	}
	if (i != 0 && Gems[i][j]->getFillColor() == Gems[i - 1][j]->getFillColor()) {
		findFigureToDrop(i - 1, j, gemsCoords);
	}
	if (j != 0 && Gems[i][j]->getFillColor() == Gems[i][j - 1]->getFillColor()) {
		findFigureToDrop(i, j - 1, gemsCoords);
	}
}
void Field::mainDrop(const set<vector<int>>& gemCoords)
{
	set <vector<int>>::reverse_iterator rIt;
	set <int> nColmnChecked;
	for (rIt = gemCoords.rbegin(); rIt != gemCoords.rend(); rIt++) { //from set's end => from bot to top
		if (nColmnChecked.find((*rIt)[0]) == nColmnChecked.end()) {
			nColmnChecked.insert((*rIt)[0]);
			dropOneColmn((*rIt)[0], (*rIt)[1], gemCoords, COMMON_DROP);
		}
	}
}
void Field::dropOneColmn(int iOfGem, int jOfGem, const set<vector<int>>& gemsCoords, int flag)
{
	set <vector<int>>::iterator It;
	sf::Vector2f speed(0.f, 0.05f);
	int nGemsInColmn = 1;
	if(flag == COMMON_DROP) {
		for (int j = jOfGem; j > 0; j--) {
			if (gemsCoords.find({ iOfGem  , j - 1 }) != gemsCoords.end() &&
				gemsCoords.find({ iOfGem  , j }) != gemsCoords.end()) {
				nGemsInColmn++;
			}
		}
	}// to find out how many gems in colomn
	
	//for (It = gemsCoords.begin(); It != gemsCoords.end(); It++) {
	//	//Gems[(*It)[0]][(*It)[1]]->setOutlineThickness(-0.0f);
	//	//Gems[(*It)[0]][(*It)[1]]->setOutlineColor(Color::White);
	//	Gems[(*It)[0]][(*It)[1]]->setFillColor(sf::Color(0,0,0,0));
	//}
	if (jOfGem - nGemsInColmn != -2) {
		for(int p = 1; p <= nGemsInColmn; p++) {
			for (int i4 = 0; i4 < _gemSize * 20 ; i4++) {
				for (int j = jOfGem - nGemsInColmn; j >= 0 ; j--) {
					Gems[iOfGem][j]->Move(speed);
				}
				toDraw();
			}//to move gems down	
		}
		for (int j = jOfGem; j - nGemsInColmn >= 0; j--) {
			Gems[iOfGem][j] = Gems[iOfGem][j - nGemsInColmn];
		}//to give upper gems pointers to lower
	}

	for (int j = 0; j < nGemsInColmn; j++) {
		Gems[iOfGem][j] = std::make_shared<Gem>(Gem(iOfGem * _gemSize, j * _gemSize, _gemSize));
		Gems[iOfGem][j]->chooseColor();
		toDraw();
	}//to create new gems on top
	for (It = gemsCoords.begin(); It != gemsCoords.end(); It++) {
		Gems[(*It)[0]][(*It)[1]]->setOutlineThickness(-2.5f);
		Gems[(*It)[0]][(*It)[1]]->setOutlineColor(Color::Black);
	}
}
sf::Vector2i Field::ChooseRandInRadius(int radius, sf::Vector2i pos) {
	int dx = pos.x + rand() % radius;
	int dy = pos.y + rand() % radius;
	while (dx < 1 || dy < 1 || dx > nGemsX - 2 || dy > nGemsY - 2) {
		dx = pos.x;
		dy = pos.y;
		if (rand() % 2)
			dx += rand() % radius;
		else
			dx -= rand() % radius;

		if (rand() % 3)
			dy -= rand() % radius;
		else
			dy += rand() % radius;
	}


	return { dx,dy };

}
