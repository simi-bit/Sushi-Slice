#ifndef THROWABLES_H
#define THROWABLES_H

#include "../Visuals/Dynamics.h"
#include "../Visuals/Sight.h"

class Sushies : public Shapes, public d::Kinematics {
public:
	Sushies(std::vector<sf::Sprite>* object) : Shapes(), d::Kinematics::Kinematics(object) {
		d::Kinematics::width_object = Shapes::width_object;
		d::Kinematics::height_object = Shapes::height_object;
	}
};

#endif // THROWABLES_H
