#pragma once
#include "SFML/Graphics.hpp"
enum class Colors {
	BLUE,
	GREEN,
	YELLOW,
	WHITE,
	RED
};
class Gem : public sf::RectangleShape {
public:
	Gem(float X, float Y, Colors color, float Size);
private:
	Colors Color;
};