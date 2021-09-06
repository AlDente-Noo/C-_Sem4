#include <SFML/Graphics.hpp>
#include "field.h"
#include "Gem.h"
#include "AddFuncs.h"
using namespace std;
const int W = 860;
const int H = 540;
int main(void) {
    sf::RenderWindow window(sf::VideoMode(W, H), "Gems");
    vector<vector<shared_ptr<Gem>>> GEMS = getGems(&window, 3);
    return 0;
}