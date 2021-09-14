#include <SFML/Graphics.hpp>
#include "field.h"
#include "Gem.h"
using namespace sf;
const int W = 880;
const int H = 528;
const int gemSize = 44;
int main(void) {
    sf::RenderWindow window(sf::VideoMode(W, H), "Gems");
	Field Field(&window, gemSize);
	Field.toBe();
	while (window.isOpen()) {
		Event event;
		
		while (window.pollEvent(event))
		{
			window.clear(Color::Black);
			if (event.type == Event::Closed)
				window.close();
			Field.toDraw();
			window.display();
			if (Mouse::isButtonPressed(Mouse::Left)) {
				Vector2i mousePosition = Mouse::getPosition(window);
				if (Field.contains(mousePosition) == 1) {
					window.close();
				}
			}
		}
	}
	return 0;
}