#include "Gem.h"
#include "SFML/Graphics.hpp"
Gem::Gem(float X, float Y, Colors color, float Size) {
	setPosition(X, Y);
	setSize(sf::Vector2f(Size, Size));
	Color = color;
}