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
		float fixedTimeStep = 1.f / 60.f;
		float accumulator = 0;

		// Sets the Textures and Fonts
		textureFontSetup();

		// Main Menu Screen
		sf::Text startBtn(font_arial);
		sf::Text exitBtn(font_arial);
		sf::Sprite mainMenuBackground(textureMainMenuBackground);
		std::vector<sf::Sprite> mainMenuBackgroundLeft;// (textureMainMenuBackgroundLeft);
		std::vector<sf::Sprite> mainMenuBackgroundRight;// (textureMainMenuBackgroundRight);
		MainMenu menu(window, &mainMenuBackground, &mainMenuBackgroundLeft, &mainMenuBackgroundRight,
			&textureMainMenuBackgroundLeft, &textureMainMenuBackgroundRight, &startBtn, &exitBtn);

		// Playing Screen
		std::vector<sf::Sprite> sushie;
		sushie.reserve(4);
		for (int i = 0; i < 20; i++) {
			sushie.emplace_back(textureSushi);
		}
		Regulator regulator(&sushie, window, fixedTimeStep);

		// Game Over Screen
		sf::Text gameOverText(font_04b30);
		sf::Text instructionText(font_04b30);
		GameOver gameOver(window, &gameOverText, &instructionText);

		// Current Game State
		GameState currentState = GameState::MainMenu;

		while (window->isOpen()) {
			sf::Time dt = clock.restart();
			if (dt.asSeconds() > 0.1f)
				dt = sf::seconds(0.1f);
			accumulator += dt.asSeconds();

			while (const std::optional event = window->pollEvent()) {
				if (event->is<sf::Event::Closed>() || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
					window->close();
			}

			// window->clear(sf::Color(92, 64, 51));
			if (!(currentState == GameState::MainMenu))
				window->clear();

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