#ifndef REGULATOR
#define REGULATOR

#include "Throwables.h"
#include <map>

class Regulator {
private:
	std::random_device rdn;
	std::mt19937 GEN;
	std::uniform_real_distribution<> DISTRIB;
	std::map <int, int> objectsOrder;
	std::vector<int> objectNumber;

public:
	Sushies* sushies = nullptr;

	Regulator(std::vector<sf::Sprite>* object, sf::RenderWindow* window, float FixedTimeStep) {
		sushies = new Sushies(object);
		sushies->window = window;
		sushies->fixedTimeStep = FixedTimeStep;

		std::mt19937 gen(rdn());
		std::uniform_real_distribution<> distrib(1,4);
		
		for (int i = 0; i < object->size(); i++) {
			objectNumber.emplace_back(i);
		}
		objectsOrder[0] = 0;
		objectsOrder[1] = 2;
		objectsOrder[2] = 1;
		objectsOrder[3] = 3;
	}

	void waves() {

		

		sushies->verticalThrow(&objectsOrder, 0);
		sushies->verticalThrow(&objectsOrder, 2);
		sushies->verticalThrow(&objectsOrder, 1);
		sushies->verticalThrow(&objectsOrder, 3);
	}

};

class Trikster {

};

#endif // !REGULATOR
