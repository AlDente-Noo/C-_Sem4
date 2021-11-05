#include "Gem.h"
#include <iostream>
#include "SFML/Graphics.hpp"
using namespace sf;
Gem::Gem(float X, float Y, const int Size) {
	setPosition(X, Y);
	setSize(sf::Vector2f(Size, Size));
	setOutlineColor(sf::Color::Black);
	setOutlineThickness(-2.5f);
}
void Gem::Move(sf::Vector2f speed)
{
	move(speed);
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
bool Gem::SetRandomBonus() {

	int bonus_threshold = rand() % 100;
	if (bonus_threshold < BONUS_CHANCE && _bonus == nullptr) {
		if (bonus_threshold % 2)
			_bonus = std::make_shared<Bomb>(Bomb(getPosition()));
		else
			_bonus = std::make_shared<Paint>(Paint(getPosition()));
		return true;
	}
	return false;
}

vector<sf::Vector2i> Gem::ActivateBonus(const sf::Vector2i& board_size,
	const sf::Vector2i& pos) {
	auto affected_gems = _bonus->Activate(board_size, pos);
	_bonus = nullptr;
	return affected_gems;
}
