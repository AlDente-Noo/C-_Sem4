#include "bonus.h"
#include <set>
#include <iostream>
using namespace std;


vector<sf::Vector2i> Paint::Activate(const sf::Vector2i& board_size,
	const sf::Vector2i& coord) {
	vector<sf::Vector2i> targets;
	for (int i = 0; i < _num_affected_gems; i++) {
		while (true) {
			sf::Vector2i targ = { coord.x, coord.y };

			if (rand() % 2) // give random offset to coordinate
				targ.x += rand() % PAINT_RADIUS;
			else
				targ.x -= rand() % PAINT_RADIUS;

			if (rand() % 3)
				targ.y -= rand() % PAINT_RADIUS;
			else
				targ.y += rand() % PAINT_RADIUS;


			// check if inside board and not a neighbor
			if (!(targ == coord || (targ.x == coord.x && targ.y == coord.y + 1)
				|| (targ.x == coord.x && targ.y == coord.y - 1)
				|| (targ.y == coord.y && targ.x == coord.x - 1)
				|| (targ.y == coord.y && targ.x == coord.x + 1))
				&& 0 <= targ.x && targ.x < board_size.x
				&& 0 <= targ.y && targ.y < board_size.y) {

				targets.push_back(targ);
				break;

			}
		}
	}
	return targets;
}




vector<sf::Vector2i> Bomb::Activate(const sf::Vector2i& board_size,
	const sf::Vector2i& coord) {
	vector<sf::Vector2i> targets;
	
	set<int> unique_targets;
	unique_targets.insert(coord.x * board_size.x + coord.y);
	size_t set_size = 1;
	int max_coord = board_size.x * board_size.y;
	while (set_size < _num_affected_gems) { // choosing random targets -> chance to
		unique_targets.insert(rand() % max_coord); // pick same one 2 times, 
		if (unique_targets.size() > set_size)
			set_size++;
	}
	for (const auto& c : unique_targets) {
		targets.push_back({ c / board_size.x, c % board_size.x });
	}
	return targets;
}