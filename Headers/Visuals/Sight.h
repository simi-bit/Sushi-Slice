#ifndef SIGHT_H
#define SIGHT_H

#include <SFML/Graphics.hpp>

sf::Texture textureSushi, textureMainMenuBackground, textureMainMenuBackgroundLeft, textureMainMenuBackgroundRight;
sf::Font font_arial, font_04b30;

void textureFontSetup() {
	// Textures
	textureSushi.loadFromFile("Code_Database/Images/sushi.png");
	textureMainMenuBackground.loadFromFile("Code_Database/Images/Backgrounds/mainmenu.png");
	textureMainMenuBackgroundLeft.loadFromFile("Code_Database/Images/Backgrounds/mainmenuleft.png");
	textureMainMenuBackgroundRight.loadFromFile("Code_Database/Images/Backgrounds/mainmenuright.png");

	// Fonts
	font_arial.openFromFile("Code_Database/Fonts/arial.ttf");
	font_04b30.openFromFile("Code_Database/Fonts/04b30.ttf");
}


class Shapes {
public:
	float width_object, height_object;

	Shapes() {
		width_object = textureSushi.getSize().x;
		height_object = textureSushi.getSize().y;
	}
};

#endif // !

