#pragma once
#include "field.h"
#define BONUS_CHANCE 30
#define BOMB_TARGETS 5
#define PAINT_TARGETS 3
#define COMBO_SIZE_FOR_BONUS 3
#define PAINT_RADIUS 3
class Bonus : public sf::Sprite {
protected:
	int _num_affected_gems;
public:
	Bonus (sf::Vector2f pos) {
		_num_affected_gems = 0;
		setPosition(pos);
	};
	Bonus( sf::Vector2f pos, int affected_gems_count) :
		_num_affected_gems(affected_gems_count) {
		setPosition(pos);
	};
	int GetNumTargets() const { return _num_affected_gems; };
	virtual std::vector<sf::Vector2i> Activate(const sf::Vector2i& board_size,
		const sf::Vector2i& coord) = 0;
	virtual ~Bonus() {};
};


class Bomb : public Bonus {
	
public:
	Bomb(sf::Vector2f pos):Bonus( pos, BOMB_TARGETS) {};
	virtual std::vector<sf::Vector2i> Activate(const sf::Vector2i& board_size,
		const sf::Vector2i& coord);
};


class Paint : public Bonus {

	
public:
	Paint(sf::Vector2f pos) :Bonus(pos, PAINT_TARGETS) {};
	virtual std::vector<sf::Vector2i> Activate(const sf::Vector2i& board_size,
		const sf::Vector2i& coord);
	~Paint() {};
};