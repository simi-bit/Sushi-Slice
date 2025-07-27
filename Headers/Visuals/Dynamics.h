#ifndef DYNAMICS_H
#define DYNAMICS_H

#include <SFML/Graphics.hpp>
#include <cmath>
#include <random>
#include<map>

namespace d {
	class Kinematics {
	private:
		// Random generator setup
		std::random_device rd;
		std::mt19937 GEN;
		std::uniform_real_distribution<> DISTRIB_FULL;
		std::uniform_real_distribution<> DISTRIB_MIDDLE;

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
		// float positionX;
		// float positionY;
		float INIT_POSITION_Y;

		// Object's Speed
		// float gravity, velocityX, velocityY;
		float gravity, init_velocity_x, INIT_VELOCITY_Y;

		float fixedTimeStep;

		void setRandomHorizontalSpawn() {
			std::mt19937 gen(rd());
			std::uniform_real_distribution<> distrib_f(width_object, screen_width - width_object);
			std::uniform_real_distribution<> distrib_m(screen_width / 4, screen_width - screen_width / 4);

			GEN = gen;
			DISTRIB_FULL = distrib_f;
			DISTRIB_MIDDLE = distrib_m;
		}

		void verticalThrow(std::map<int, int>* objectsOrder, int object) {


			// Sets random positionX for ball
			if (motion[object][0][1] >= INIT_POSITION_Y)
				motion[object][0][0] = random_position_x(false);

			// Decides if the ball must be resetted
			bool reset = false;

			// Ball kinematics
			motion[object][1][1] += gravity * fixedTimeStep;
			motion[object][0][1] += motion[object][1][1] * fixedTimeStep;
			objects->at(object).setPosition({ motion[object][0][0], motion[object][0][1] });

			// Destroying the ball
			if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
				if (objects->at(object).getGlobalBounds().contains((sf::Vector2f)window->mapCoordsToPixel(sf::Vector2f(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y))))
					reset = true;
			}

			// Resetting the ball
			if (reset || ((std::abs(motion[object][0][1]) >= INIT_POSITION_Y) && (std::abs(motion[object][1][1]) >= std::abs(INIT_VELOCITY_Y)))) {
				motion[object][1][1] = INIT_VELOCITY_Y;
				motion[object][0][1] = INIT_POSITION_Y;
			}

			
			// Drawing the Sprite
			for (int i = 0, c = 1; i != objectsOrder->size(); i++, c++) {
				for (int index = 0; index != objectsOrder->size(); index++) {
					if (objectsOrder->at(index) == objectsOrder->size() - c) {
						window->draw(objects->at(index));
						break;
					}
				}
			}
		}
		float random_position_x(bool full) {
			if (full)
				return DISTRIB_FULL(GEN);
			return DISTRIB_MIDDLE(GEN);
		}

		Kinematics(std::vector<sf::Sprite>* OBJECTS) {
			objects = OBJECTS;

			sf::VideoMode RESOLUTION = sf::VideoMode::getDesktopMode();
			screen_width = RESOLUTION.size.x;
			screen_height = RESOLUTION.size.y;

			setRandomHorizontalSpawn();
			verticalThrowPrep();
			INIT_POSITION_Y = screen_height + (height_object / 2);
			float velocityY = INIT_VELOCITY_Y;
			float positionY = INIT_POSITION_Y;
			float positionX;
			for (int i = 0; i < 4; i++) {
				positionX = random_position_x(false);
				motion.push_back({ { positionX , positionY }, { 0, velocityY } });
			}
		}

	};
}

#endif // !DYNAMICS_H

