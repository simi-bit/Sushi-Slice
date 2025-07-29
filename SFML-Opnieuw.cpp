#include "Headers/Visuals/Window.h"

int main() {
	sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Test", sf::Style::None, sf::State::Fullscreen);
	window.setVerticalSyncEnabled(true);
	Window startGame(&window);
	return 0;
}