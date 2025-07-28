#ifndef WINDOW
#define WINDOW

#include "Headers/Playing/Regulator.h"
#include "../Main_Menu/Main_Menu.h"
#include "../Game_Over/Game_Over.h"
#include "../ID/ID.h"

class Window {
public:
	Window(sf::RenderWindow* window) {

		// Time
		sf::Clock clock;
		float fixedTimeStep = 1.f / 400.f;
		float accumulator = 0;

		// Sets the Textures and Fonts
		textureFontSetup();

		// Current Game State
		GameState currentState = GameState::MainMenu;

		// Main Menu Screen
		sf::Text startBtn(font_04b30);
		sf::Text exitBtn(font_04b30);
		sf::Sprite mainMenuBackground(textureMainMenuBackground);
		std::vector<sf::Sprite> mainMenuBackgroundLeft;
		std::vector<sf::Sprite> mainMenuBackgroundRight;
		MainMenu menu(window, &mainMenuBackground, &mainMenuBackgroundLeft, &mainMenuBackgroundRight,
			&textureMainMenuBackgroundLeft, &textureMainMenuBackgroundRight, &startBtn, &exitBtn, &currentState);

		// Playing Screen
		std::vector<sf::Sprite> objects;
		std::vector<sf::Sprite> hearts;
		std::vector<sf::Text> texts;
		std::vector<sf::Sound> throwSound;
		Regulator regulator(&objects, &hearts, window, fixedTimeStep, &texts, &throwSound, &currentState);

		// Game Over Screen
		sf::Text gameOverText(font_04b30);
		sf::Text instructionText(font_04b30);
		GameOver gameOver(window, &gameOverText, &instructionText, &currentState);

		
		while (window->isOpen()) {
			sf::Time dt = clock.restart();
			if (dt.asSeconds() > 0.1f)
				dt = sf::seconds(0.1f);
			accumulator += dt.asSeconds();

			while (const std::optional event = window->pollEvent()) {
				if (event->is<sf::Event::Closed>() || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) {
					window->close();
				}
			}

			window->clear(sf::Color(92, 64, 51));

			while (accumulator >= fixedTimeStep) {
				if (currentState == GameState::MainMenu) {
					menu.display();
				}
				else if (currentState == GameState::Playing) {
					regulator.waves();
				}
				else if(currentState == GameState::GameOver)
				{
					gameOver.display();
				}
				accumulator -= fixedTimeStep;
			}
			window->display();
		}
	}
};

#endif // !WINDOW