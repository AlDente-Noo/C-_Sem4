#include "field.h"
using namespace std;
Field::Field(sf::RenderWindow* window, vector<vector<shared_ptr<Gem>>> gems) {
	Window = window;
	Gems = gems;
}
void Field::Fill() {
	
}