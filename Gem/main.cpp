#include <SFML/Graphics.hpp>
#include "field.h"
using namespace sf;
const int W = 880;
const int H = 880;
const int gemSize = 88;
int main(void) {
	sf::Texture texture;
    sf::RenderWindow window(sf::VideoMode(W, H), "Gems");
	Field Field(&window, gemSize);
	Field.toBe();
	bool frstBlck = false;
	bool scndBlck = false;
	Vector2i scndBlckCoord;
	Vector2i frstBlckCoord;
	while (window.isOpen()) {
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
			Field.toDraw();
			if (Mouse::isButtonPressed(Mouse::Left)) {
				Vector2i mousePosition = Mouse::getPosition(window);
				if (Field.contains(mousePosition) == 1) {
					if (frstBlck == false ){
						frstBlckCoord = mousePosition;		
						frstBlck = true;
					}
					else {
						scndBlckCoord = mousePosition;
						scndBlck = true;
						if (frstBlck == true && scndBlck == true) {
							if (Field.changeGems(frstBlckCoord, scndBlckCoord) == true) {
								window.clear(Color::Black);
								Field.toDraw();
								if (Field.checkField() == false) {
										sf::sleep(sf::seconds(0.5));
										Field.changeGems(frstBlckCoord, scndBlckCoord);
										window.clear(Color::Black);
										Field.toDraw();
								}
								while (Field.checkField() == true) {	
								}
							}
						}
						frstBlck = false;
						scndBlck = false;
					}
				}
			}
		}
	}
	return 0;
}