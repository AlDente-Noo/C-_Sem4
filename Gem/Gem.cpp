#include "Gem.h"
#include <iostream>
#include "SFML/Graphics.hpp"
using namespace sf;
Gem::Gem(float X, float Y, const int Size) {
	setPosition(X, Y);
	setSize(sf::Vector2f(Size, Size));
	setOutlineColor(sf::Color::Black);
	setOutlineThickness(-2.5f);
	//setFillColor(Color(255,0 ,0));
}
void Gem::deleteColors(Gem check) {
	std::list<Color>::iterator it = this->availibleColors.begin();
	for (it; it!= availibleColors.end(); it++) {
		if (*it == check.getFillColor()) {
			this->availibleColors.erase(it);
			break;
		}
	}
}
void Gem::chooseColor() {
	int d = rand()%(this->availibleColors.size());
	auto it = this->availibleColors.begin();
	std::advance(it, d);
	this->setFillColor(*it);
}
/*bool Gem::isSameColor(Gem nearbyGem)
{
	if (this->getFillColor() == nearbyGem.getFillColor()) return true;
	else return false;
}*/
