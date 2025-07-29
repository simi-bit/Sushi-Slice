#ifndef REGULATOR
#define REGULATOR

#include "Throwables.h"
#include <algorithm>
#include <ctime>

class Regulator {
private:
	GameState* currentState;

	std::random_device rdn;
	std::mt19937 GEN;
	std::uniform_real_distribution<> DISTRIB;
	std::map <int, int> objectsOrder;
	std::vector<int> objectNumber;

	bool resetTimer = true;
	bool startGameClock = false;
	float gameTime;

	// Defines the Difficulty part
	bool easy1 = false;
	bool easy2 = false;
	bool medium1 = false;
	bool medium2 = false;
	bool medium3 = false;


	std::vector<bool> activeRedSushis, activeOrangeSushis, activeGreenSushis, activeBonusSushis, activePoison;
	// int objectsTime = 0;

	std::clock_t before;

public:
	Throwables* hand = nullptr;

	Regulator(std::vector<sf::Sprite>* object, std::vector<sf::Sprite>* hearts, sf::RenderWindow* window, float FixedTimeStep,
		std::vector<sf::Text>* texts, std::vector<sf::Sound>* throwSound, GameState* currentState) {


		hand = new Throwables(window, object, hearts, texts, throwSound, currentState);

		std::mt19937 gen(rdn());
		std::uniform_real_distribution<> distrib(1,4);
		
		for (int i = 0; i < object->size(); i++) {
			if(i < 10)
				activeRedSushis.emplace_back(true);
			else if (i < 20)
				activeOrangeSushis.emplace_back(true);
			else if (i < 30)
				activeGreenSushis.emplace_back(true);
			else if (i < 33)
				activeBonusSushis.emplace_back(true);
			else
				activePoison.emplace_back(true);
		}

		this->currentState = currentState;
		hand->fixedTimeStep = FixedTimeStep;
	}



	bool easy() {
		if (resetTimer) {
			before = std::clock();
			std::fill(activeRedSushis.begin(), activeRedSushis.end(), true);
			std::fill(activeOrangeSushis.begin(), activeOrangeSushis.end(), true);
			std::fill(activeGreenSushis.begin(), activeGreenSushis.end(), true);
			std::fill(activePoison.begin(), activePoison.end(), true);
			

			resetTimer = false;
		}

		if (activeGreenSushis[0]) {
			if (((clock() - before) / CLOCKS_PER_SEC) >= 1) {
				if (hand->throwGreenSushi(0))
					activeGreenSushis[0] = false;
			}
		}
		if (activeOrangeSushis[0]) {
			if (((clock() - before) / CLOCKS_PER_SEC) >= 5) {
				if (hand->throwOrangeSushi(0))
					activeOrangeSushis[0] = false;
			}
		}

		if (activeOrangeSushis[1]) {
			if (((clock() - before) / CLOCKS_PER_SEC) >= 8) {
				if (hand->throwOrangeSushi(1))
					activeOrangeSushis[1] = false;
			}
		}

		if (activeRedSushis[0]) {
			if (((clock() - before) / CLOCKS_PER_SEC) >= 8.5) {
				if (hand->throwRedSushi(0))
					activeRedSushis[0] = false;
			}
		}

		// Intro to Poison
		if (activePoison[0]) {
			if (((clock() - before) / CLOCKS_PER_SEC) >= 12) {
				if (hand->throwPoison(0)) {
					activePoison[0] = false;
					resetTimer = true;
					if (easy1)
						easy2 = true;

					if (easy2) 
						medium1 = true;

					if (medium1) 
						medium2 = true;

					if (medium2)
						medium3 = true;
		
					easy1 = true;
				}
			}
		}

		// New Section
		if (easy1) {
			if (activeRedSushis[1]) {
				if (((clock() - before) / CLOCKS_PER_SEC) >= 2) {
					if (hand->throwRedSushi(1))
						activeRedSushis[1] = false;
				}
			}
			if (activeGreenSushis[1]) {
				if (((clock() - before) / CLOCKS_PER_SEC) >= 2.5) {
					if (hand->throwGreenSushi(1))
						activeGreenSushis[1] = false;
				}
			}
			if (activePoison[1]) {
				if (((clock() - before) / CLOCKS_PER_SEC) >= 4) {
					if (hand->throwPoison(1))
						activePoison[1] = false;
				}
			}
		}

		// New Section
		if (easy2) {
			if (activeOrangeSushis[2]) {
				if (((clock() - before) / CLOCKS_PER_SEC) >= 4) {
					if (hand->throwOrangeSushi(2)) {
						activeOrangeSushis[2] = false;
					}
				}
			}
			if (activeRedSushis[2]) {
				if (((clock() - before) / CLOCKS_PER_SEC) >= 7) {
					if (hand->throwRedSushi(2))
						activeRedSushis[2] = false;
				}
			}

			if (activePoison[2]) {
				if (((clock() - before) / CLOCKS_PER_SEC) >= 6) {
					if (hand->throwPoison(2))
						activePoison[2] = false;
				}
			}
			return true;
		}
		return false;
	}

	bool medium(bool used) {

		if (activeGreenSushis[2]) {
			if (((clock() - before) / CLOCKS_PER_SEC) >= 3) {
				if (hand->throwGreenSushi(2))
					activeGreenSushis[2] = false;
			}
		}

		if (activeRedSushis[3]) {
			if (((clock() - before) / CLOCKS_PER_SEC) >= 3.5) {
				if (hand->throwRedSushi(3))
					activeRedSushis[3] = false;
			}
		}

		if (activePoison[3]) {
			if (((clock() - before) / CLOCKS_PER_SEC) >= 6) {
				if (hand->throwPoison(3))
					activePoison[3] = false;
			}
		}

		if (activeOrangeSushis[3]) {
			if (((clock() - before) / CLOCKS_PER_SEC) >= 10) {
				if (hand->throwOrangeSushi(3)) {
					activeOrangeSushis[3] = false;
				}
			}
		}

		// New Section
		if (medium1) {
			if (activeGreenSushis[3]) {
				if (((clock() - before) / CLOCKS_PER_SEC) >= 9) {
					if (hand->throwGreenSushi(3))
						activeGreenSushis[3] = false;
				}
			}

			if (activeRedSushis[4]) {
				if (((clock() - before) / CLOCKS_PER_SEC) >= 9.25) {
					if (hand->throwRedSushi(4))
						activeRedSushis[4] = false;
				}
			}
			if (activeOrangeSushis[4]) {
				if (((clock() - before) / CLOCKS_PER_SEC) >= 9.5) {
					if (hand->throwOrangeSushi(4)) {
						activeOrangeSushis[4] = false;
					}
				}
			}

			if (activePoison[4]) {
				if (((clock() - before) / CLOCKS_PER_SEC) >= 1) {
					if (hand->throwPoison(4))
						activePoison[4] = false;
				}
			}

		}

		if (medium2) {
			if (activeGreenSushis[4]) {
				if (((clock() - before) / CLOCKS_PER_SEC) >= 9) {
					if (hand->throwGreenSushi(4))
						activeGreenSushis[4] = false;
				}
			}

			if (activeRedSushis[5]) {
				if (((clock() - before) / CLOCKS_PER_SEC) >= 11) {
					if (hand->throwRedSushi(5))
						activeRedSushis[5] = false;
				}
			}
			if (activeOrangeSushis[5]) {
				if (((clock() - before) / CLOCKS_PER_SEC) >= 9.75) {
					if (hand->throwOrangeSushi(5)) {
						activeOrangeSushis[5] = false;
					}
				}
			}

			if (activeOrangeSushis[6]) {
				if (((clock() - before) / CLOCKS_PER_SEC) >= 12) {
					if (hand->throwOrangeSushi(6)) {
						activeOrangeSushis[6] = false;
					}
				}
			}

			if (activePoison[5]) {
				if (((clock() - before) / CLOCKS_PER_SEC) >= 9.75) {
					if (hand->throwPoison(5))
						activePoison[5] = false;
				}
			}

		}

		if (medium3) {
			if (activeGreenSushis[4]) {
				if (((clock() - before) / CLOCKS_PER_SEC) >= 1.75) {
					if (hand->throwGreenSushi(4))
						activeGreenSushis[4] = false;
				}
			}

			if (activeGreenSushis[5]) {
				if (((clock() - before) / CLOCKS_PER_SEC) >= 7.5) {
					if (hand->throwGreenSushi(5))
						activeGreenSushis[5] = false;
				}
			}

			if (activeRedSushis[5]) {
				if (((clock() - before) / CLOCKS_PER_SEC) >= 11.5) {
					if (hand->throwRedSushi(5))
						activeRedSushis[5] = false;
				}
			}

			if (activeRedSushis[6]) {
				if (((clock() - before) / CLOCKS_PER_SEC) >= 8) {
					if (hand->throwRedSushi(6))
						activeRedSushis[6] = false;
				}
			}

			if (activeOrangeSushis[5]) {
				if (((clock() - before) / CLOCKS_PER_SEC) >= 9.75) {
					if (hand->throwOrangeSushi(5)) {
						activeOrangeSushis[5] = false;
					}
				}
			}

			if (activeOrangeSushis[6]) {
				if (((clock() - before) / CLOCKS_PER_SEC) >= 1.75) {
					if (hand->throwOrangeSushi(6)) {
						activeOrangeSushis[6] = false;
					}
				}
			}

			if (activePoison[5]) {
				if (((clock() - before) / CLOCKS_PER_SEC) >= 10.75) {
					if (hand->throwPoison(5))
						activePoison[5] = false;
				}
			}

		}

		return false;
	}

	void waves() {

		if (!startGameClock) {
			startGameClock = true;
			gameTime = std::clock();
		}
		
		//easy(false);
		if (easy()) {
			medium(false);
		}
		// Displays the current Score
		hand->drawScore();
		if (!hand->drawHearts()) {
			easy1 = false;
			easy2 = false;
			medium1 = false;
			medium2 = false;
			medium3 = false;
			hand->resetHealth();
			resetTimer = true;
			*currentState = GameState::GameOver;
		}

	}

};


#endif // !REGULATOR
