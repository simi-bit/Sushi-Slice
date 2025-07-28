#ifndef THROWABLES_H
#define THROWABLES_H

#include "../Visuals/Dynamics.h"
#include "../Visuals/Sight.h"
#include "../ID/ID.h"
#include <SFML/Audio.hpp>

class Score {
private:
	int score = 0;
	std::string scoreString;
	sf::Text* scoreText;
	sf::RenderWindow* window;
public:
	Score(sf::RenderWindow* window, std::vector<sf::Text>* scoreText) {
		// Score Apearance
		scoreText->emplace_back(font_arial);
		scoreText->at(0).setCharacterSize(64);
		scoreText->at(0).setString("00000000");
		scoreText->at(0).setOrigin({scoreText->at(0).getLocalBounds().size.x, scoreText->at(0).getLocalBounds().size.y});
		scoreText->at(0).setPosition({(98.f/100.f) * window->getSize().x, (5.f / 100.f) * window->getSize().y });

		this->window = window;
		this->scoreText = &scoreText->at(0);
	}

	void updateScore(int plusScore) {
		score += plusScore;
		scoreString = "";
		if (std::to_string(score).length() < 8) {
			for (int i = 0; i < 8 - std::to_string(score).length(); i++) {
				scoreString += '0';
			}
		}
		scoreString += std::to_string(score);
		scoreText->setString(scoreString);
	}

	void drawScore() {
		window->draw(*scoreText);
	}
};

class Health : public Shapes {
private:
	sf::RenderWindow* window;
	std::vector<sf::Sprite>* hearts;
	int health = 3;

protected:
	void healthM() {
		health -= 1;
	}

public:
	Health(sf::RenderWindow* window, std::vector<sf::Sprite>* hearts) : Shapes() {
		float heartsScale = (((9.f / 100.f) * window->getSize().y) / filledHeartWidth);
		hearts->reserve(6);
		for (float i = 0; i < 6; i++) {
			if (i < 3) {
				hearts->emplace_back(textureFilledHeart);
				if (i == 0) {
					hearts->at(i).setPosition({ (1.f / 100.f) * window->getSize().x, (0.5f / 100.f) * window->getSize().y });
				} else if (i >= 1)
					hearts->at(i).setPosition({ ((1.f + (5.f * i)) / 100.f) * window->getSize().x, (0.01f / 100.f) * window->getSize().y });
			}
			else {
				hearts->emplace_back(textureEmptyHeart);
				hearts->at(i).setPosition({ hearts->at(i - 3.f).getPosition().x, hearts->at(i - 3.f).getPosition().y });
			}
				hearts->at(i).setScale({ heartsScale, heartsScale });
		}
		
		this->window = window;
		this->hearts = hearts;
	}
	void drawHearts() {
		for (int i = 0; i < health; i++) {
			window->draw(hearts->at(i));
		}
		if (health <= 2) {
			window->draw(hearts->at(5));
		}
		if (health <= 1) {
			window->draw(hearts->at(4));
		}
		if (health <= 0) {
			window->draw(hearts->at(3));
		}
	}
};

class Throwables : public d::Kinematics, public Score, public Health {
private:
	Point smallPoint = Point::Small;
	GameState* currentState;
	std::vector<sf::Sound>* throwSound;

	bool throwSushi(int sushi) {
		Point point = Throw(sushi);
		if (point == Point::Earned) {
			if (sushi > 32)
				*currentState = GameState::GameOver;

			updateScore((int)smallPoint);
			return true;
		}
		else if (point == Point::Moving)
		{
			return false;
		}
		else
		{
			// Lose a life
			if (sushi < 33)
				healthM();
			return true;
		}
	}

public:
	Throwables(sf::RenderWindow* window, std::vector<sf::Sprite>* object, std::vector<sf::Sprite>* hearts, std::vector<sf::Text>* scoreText, std::vector<sf::Sound>* throwSound, GameState* currentState) :
		d::Kinematics::Kinematics(window, object, throwSound), Score(window, scoreText), Health(window, hearts) {
		d::Kinematics::width_object = Shapes::sushiWidth;
		d::Kinematics::height_object = Shapes::sushiHeight;

		
		float scaleSushi = (((9.f / 100.f) * screen_width) / sushiWidth);
		float scalePoison = (((20.f / 100.f) * screen_height) / poisonHeight);

		object->reserve(40);
		throwSound->reserve(40);
		for (int i = 0; i < 40; i++) {
			throwSound->emplace_back(throwBuffer);
			if (i < 10) {
				object->emplace_back(textureSushiRed);
				object->at(i).setOrigin({ Shapes::sushiWidth / 2.f, Shapes::sushiHeight / 2.f });
				object->at(i).setScale({ scaleSushi, scaleSushi });
			}
			else if (i < 20) {
				object->emplace_back(textureSushiOrange);
				object->at(i).setOrigin({ Shapes::sushiWidth / 2.f, Shapes::sushiHeight / 2.f });
				object->at(i).setScale({ scaleSushi, scaleSushi });
			}
			else if (i < 30) {
				object->emplace_back(textureSushiGreen);
				object->at(i).setOrigin({ Shapes::sushiWidth / 2.f, Shapes::sushiHeight / 2.f });
				object->at(i).setScale({ scaleSushi, scaleSushi });
			}
			else if (i < 33) {
				object->emplace_back(textureSushiBonus);
				object->at(i).setOrigin({ Shapes::sushiBonusWidth / 2.f, Shapes::sushiBonusHeight / 2.f });
			}
			else {
				object->emplace_back(texturePoison);
				object->at(i).setOrigin({ Shapes::poisonWidth / 2.f, Shapes::poisonHeight / 2.f });
				object->at(i).setScale({ scalePoison, scalePoison });
			}
			
		}
		this->currentState = currentState;
		this->throwSound = throwSound;
	}


	bool throwRedSushi(int sushi) {
		return throwSushi(sushi);
	}
	bool throwOrangeSushi(int sushi) {
		return throwSushi(sushi + 10);
	}
	bool throwGreenSushi(int sushi) {
		return throwSushi(sushi + 20);
	}
	bool throwBonusSushi(int sushi) {
		return throwSushi(sushi + 30);
	}

	bool throwPoison(int sushi) {
		return throwSushi(sushi + 33);
	}

};



#endif // THROWABLES_H
