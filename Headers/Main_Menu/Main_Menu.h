#ifndef MAIN_MENU
#define MAIN_MENU

#include <SFML/Graphics.hpp>

class MainMenu {
private:
	sf::RenderWindow* menu;
	sf::Sprite* mainMenuBackground;
	std::vector<sf::Sprite>* mainMenuBackgroundLeft;
	std::vector<sf::Sprite>* mainMenuBackgroundRight;
	sf::Text* startBtn;
	sf::Text* exitBtn;

public:
	MainMenu(sf::RenderWindow* menu, sf::Sprite* mainMenuBackground, std::vector<sf::Sprite>* mainMenuBackgroundLeft, std::vector<sf::Sprite>* mainMenuBackgroundRight,
		sf::Texture* textureMainMenuBackgroundLeft, sf::Texture* textureMainMenuBackgroundRight, sf::Text* startBtn, sf::Text* exitBtn) {
		// Screen Resolution
		sf::VideoMode RESOLUTION = sf::VideoMode::getDesktopMode();
		float screenWidth = menu->getSize().x;
		float screenHeight = menu->getSize().y;
		float SCREEN_RESOLUTION = screenWidth * screenHeight;

		// Background
		float mainMenuBackgroundWidth = mainMenuBackground->getLocalBounds().size.x;
		float mainMenuBackgroundHeight = mainMenuBackground->getLocalBounds().size.y;
		mainMenuBackground->setOrigin({ mainMenuBackgroundWidth / 2, mainMenuBackgroundHeight / 2 });
		mainMenuBackground->setPosition({ screenWidth / 2.f, screenHeight / 2.f });
		float scale = menu->getSize().y / mainMenuBackgroundHeight;
		mainMenuBackground->setScale({ scale, scale });
		for (float i = 0; i < (screenWidth / 2) - (mainMenuBackground->getGlobalBounds().size.x / 2) + 1; i++) {
			mainMenuBackgroundLeft->emplace_back(*textureMainMenuBackgroundLeft);
			mainMenuBackgroundLeft->at(i).setOrigin({ mainMenuBackgroundLeft->at(i).getLocalBounds().size.x / 2.f,  mainMenuBackgroundLeft->at(i).getLocalBounds().size.y / 2.f });
			mainMenuBackgroundLeft->at(i).setPosition({ i, screenHeight / 2.f });
			mainMenuBackgroundLeft->at(i).setScale({1.f, scale});

			mainMenuBackgroundRight->emplace_back(*textureMainMenuBackgroundRight);
			mainMenuBackgroundRight->at(i).setOrigin({ mainMenuBackgroundRight->at(i).getLocalBounds().size.x / 2.f,  mainMenuBackgroundRight->at(i).getLocalBounds().size.y / 2.f });
			mainMenuBackgroundRight->at(i).setPosition({ screenWidth - i, screenHeight / 2.f });
			mainMenuBackgroundRight->at(i).setScale({ 1.f, scale });
		}

		// Text Size
		unsigned int TEXT_SIZE = ((100 / 200) * SCREEN_RESOLUTION);

		startBtn->setString("Start");
		startBtn->setCharacterSize(TEXT_SIZE);
		startBtn->setFillColor(sf::Color::White);
		startBtn->setPosition({ 350.f, 200.f });
		startBtn->setFillColor(sf::Color(100, 200, 50));
		startBtn->setOutlineThickness(2.f);                     // thickness in pixels
		startBtn->setOutlineColor(sf::Color::White);            // border color

		// Center the origin of the start button
		sf::FloatRect bounds = startBtn->getLocalBounds();
		startBtn->setOrigin(bounds.getCenter()); // center the origin	
		startBtn->setPosition({ RESOLUTION.size.x / 2.f, RESOLUTION.size.y / 2.f });

		// sf::Text exitBtn(font);
		exitBtn->setString("Exit");
		exitBtn->setCharacterSize(TEXT_SIZE);
		exitBtn->setFillColor(sf::Color::White);
		exitBtn->setPosition({ 350.f, 300.f });
		exitBtn->setFillColor(sf::Color(255, 0, 0));
		exitBtn->setOutlineThickness(2.f);                     // thickness in pixels
		exitBtn->setOutlineColor(sf::Color::White);            // border color

		// Center the origin of the exit button
		sf::FloatRect exitBounds = exitBtn->getLocalBounds();
		exitBtn->setOrigin(exitBounds.getCenter()); // center the origin
		exitBtn->setPosition({ RESOLUTION.size.x / 2.f, RESOLUTION.size.y / 2.f + 100.f });

		this->menu = menu;
		this->mainMenuBackground = mainMenuBackground;
		this->mainMenuBackgroundLeft = mainMenuBackgroundLeft;
		this->mainMenuBackgroundRight = mainMenuBackgroundRight;
		this->startBtn = startBtn;
		this->exitBtn = exitBtn;
	}

	void display() {
		for (int i = 0; i < mainMenuBackgroundLeft->size(); i++) {
			menu->draw(mainMenuBackgroundLeft->at(i));
			menu->draw(mainMenuBackgroundRight->at(i));
		}
		menu->draw(*mainMenuBackground);
		menu->draw(*startBtn);
		menu->draw(*exitBtn);
	}
};

#endif // !MAIN_MENU