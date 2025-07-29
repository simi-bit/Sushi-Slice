DL#ifndef DYNAMICS_H
#define DYNAMICS_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <cmath>
#include <random>
#include <map>
#include "../ID/ID.h"

namespace d {
	class Kinematics {
	private:
		// Random generator setup
		std::random_device rd;
		std::mt19937 GEN;
		std::uniform_real_distribution<> DISTRIB_FULL;
		std::uniform_real_distribution<> DISTRIB_MIDE;

		float INIT_POSITION_Y;

		std::vector<sf::Sound>* throwSound;

		void verticalThrowPrep() {
			// Return error if conditions are not met
			if (screen_height <= 0) {
				throw std::runtime_error("screen_height must be greater then 0");
			}
			else if (percentage <= 0) {
				throw std::runtime_error("percentage must be greater then 0");
			}

			gravity = 500.f;
			float height = (percentage * screen_height) / 100;

			// v = square-root(2 x a x s)
			INIT_VELOCITY_Y = -(sqrt(2 * gravity * height));
		}
		void setRandomHorizontalSpawn() {
			std::mt19937 gen(rd());
			std::uniform_real_distribution<> distrib_f(width_object, screen_width - width_object);
			std::uniform_real_distribution<> distrib_m(screen_width / 4, screen_width - screen_width / 4);

			GEN = gen;
			DISTRIB_FULL = distrib_f;
			DISTRIB_MIDDLE = distrib_m;
		}
		float random_position_x(bool full) {
			if (full)
				return DISTRIB_FULL(GEN);
			return DISTRIB_MIDDLE(GEN);
		}

	protected:
	void resetObjects() {
			for (int i = 0; i < 40; i++) {
				motion[i][0][0] = random_position_x(false);
				motion[i][0][1] = INIT_POSITION_Y;
				motion[i][1][0] = velocityX;
				motion[i][1][1] = INIT_VELOCITY_Y;
			}
		}

	public:
		// Screen Window
		sf::RenderWindow* window;
		float screen_height, screen_width;

		// Object's info
		std::vector<sf::Sprite>* objects;
		float width_object, height_object;
		
		// Object's positioning
		std::vector<std::vector<std::vector<float>>> motion;
		float percentage = 70;

		// Object's Speed
		float gravity, init_velocity_x, INIT_VELOCITY_Y;
		float velocityX = 0;

		float fixedTimeStep;


		Point Throw(int object) {


			// Sets random positionX for ball
			if (motion[object][0][1] >= INIT_POSITION_Y) {
				if (motion[object][0][0] >= screen_width / 2)
					motion[object][1][0] = -50;
				else
					motion[object][1][0] = 50;
			}

			// Ball kinematics
			motion[object][1][1] += gravity * fixedTimeStep;
			motion[object][0][1] += motion[object][1][1] * fixedTimeStep;
			motion[object][0][0] += motion[object][1][0] * fixedTimeStep;
			objects->at(object).rotate(sf::degrees(0.1f));
			objects->at(object).setPosition({ motion[object][0][0], motion[object][0][1] });

			// Destroying the ball
			if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
				if (objects->at(object).getGlobalBounds().contains((sf::Vector2f)window->mapCoordsToPixel(sf::Vector2f(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y)))) {
					throwSound->at(object).play();
					motion[object][0][1] = INIT_POSITION_Y;
					motion[object][1][1] = INIT_VELOCITY_Y;
					motion[object][0][0] = random_position_x(false);
					return Point::Earned;
				}
			}

			// Resetting the ball
			if ((motion[object][0][1] >= INIT_POSITION_Y) && (std::abs(motion[object][1][1]) >= std::abs(INIT_VELOCITY_Y))) {
				motion[object][0][1] = INIT_POSITION_Y;
				motion[object][1][1] = INIT_VELOCITY_Y;
				motion[object][0][0] = random_position_x(false);
				return Point::None;
			}

			window->draw(objects->at(object));
			return Point::Moving;
		}


		Kinematics(sf::RenderWindow* window, std::vector<sf::Sprite>* objects, std::vector<sf::Sound>* throwSound) {
			this->window = window;
			this->objects = objects;
			this->throwSound = throwSound;

			sf::VideoMode RESOLUTION = sf::VideoMode::getDesktopMode();
			screen_width = RESOLUTION.size.x;
			screen_height = RESOLUTION.size.y;

			setRandomHorizontalSpawn();
			verticalThrowPrep();
			INIT_POSITION_Y = screen_height + (40 * height_object);
			float velocityY = INIT_VELOCITY_Y;
			float positionY = INIT_POSITION_Y;
			float positionX;
			for (int i = 0; i < 40; i++) {
				positionX = random_position_x(false);
				motion.push_back({ { random_position_x(false) , positionY}, {velocityX, velocityY}});
			}
		}

	};
}

#endif // !DYNAMICS_H

