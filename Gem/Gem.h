#pragma once
#include "SFML/Graphics.hpp"
#include <list>
#include <iterator>
#include <vector>
#include "bonus.h"
using namespace sf;
class Bonus;
class Gem : public sf::RectangleShape {
private:
	std::shared_ptr<Bonus> _bonus;
	std::list<Color>availibleColors = { Color::Blue, Color::Cyan, Color::Yellow, Color::Red, Color::Magenta, Color::Green };
public:
	std::vector<sf::Vector2i> ActivateBonus(const sf::Vector2i& board_size, const sf::Vector2i& pos);

	Gem(float X, float Y, const int Size);
	void deleteColors(Gem check);
	void chooseColor();
	void Move(sf::Vector2f speed);
	bool HasBonus () const { return _bonus != nullptr;};
	bool SetRandomBonus();
};