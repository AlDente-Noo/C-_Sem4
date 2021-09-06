#include <SFML/Graphics.hpp>
#include "field.h"
#include "Gem.h"
vector<vector<shared_ptr<Gem>>> getGems(sf::RenderWindow *window, int gemSize, vector<vector<shared_ptr<Gem>>> gems);