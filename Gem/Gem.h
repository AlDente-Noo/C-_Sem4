#pragma once
#include "SFML/Graphics.hpp"
#include <list>
#include <iterator>
using namespace sf;
class Gem : public sf::RectangleShape {
public:
	Gem(float X, float Y, const int Size);
	//bool isSameColor(Gem nearbyGem);
	void deleteColors(Gem check);
	void chooseColor();
private:
	//Color color;
	std::list<Color>availibleColors = { Color::Blue, Color::Cyan, Color::Yellow, Color::Red, Color::Magenta, Color::Green};
};