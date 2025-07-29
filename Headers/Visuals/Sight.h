#ifndef SIGHT_H
#define SIGHT_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

sf::Texture textureSushiRed, textureSushiOrange, textureSushiGreen, textureSushiBonus, texturePoison, 
textureFilledHeart, textureEmptyHeart, textureMainMenuBackground, textureMainMenuBackgroundLeft, textureMainMenuBackgroundRight;

sf::Font font_arial, font_04b30;

sf::SoundBuffer throwBuffer;

void textureFontSetup() {
	// Textures
	textureSushiRed.loadFromFile("Resources/Images/Objects/sushiRed.png");
	textureSushiOrange.loadFromFile("Resources/Images/Objects/sushiOrange.png");
	textureSushiGreen.loadFromFile("Resources/Images/Objects/sushiGreen.png");
	textureSushiBonus.loadFromFile("Resources/Images/Objects/sushiBonus.png");
	texturePoison.loadFromFile("Resources/Images/Objects/poison.png");
	textureFilledHeart.loadFromFile("Resources/Images/Objects/filledHeart.png");
	textureEmptyHeart.loadFromFile("Resources/Images/Objects/emptyHeart.png");
	textureMainMenuBackground.loadFromFile("Resources/Images/Backgrounds/mainmenu.png");
	textureMainMenuBackgroundLeft.loadFromFile("Resources/Images/Backgrounds/mainmenuleft.png");
	textureMainMenuBackgroundRight.loadFromFile("Resources/Images/Backgrounds/mainmenuright.png");

	// Fonts
	font_arial.openFromFile("Resources/Fonts/arial.ttf");
	font_04b30.openFromFile("Resources/Fonts/04b30.ttf");

	// Sounds
	throwBuffer.loadFromFile("Resources/Sounds/objectThrow.mp3");
}


class Shapes {

protected:
	float sushiWidth, sushiHeight, sushiBonusWidth, sushiBonusHeight, poisonWidth, poisonHeight,
		filledHeartWidth, filledHeartHeight, emptyHeartWidth, emptyHeartHeight;

	Shapes() {
		sushiWidth = textureSushiRed.getSize().x;
		sushiHeight = textureSushiRed.getSize().y;

		sushiBonusWidth = textureSushiBonus.getSize().x;
		sushiBonusHeight = textureSushiBonus.getSize().y;

		poisonWidth = texturePoison.getSize().x;
		poisonHeight = texturePoison.getSize().y;

		filledHeartWidth = textureFilledHeart.getSize().x;
		filledHeartHeight = textureFilledHeart.getSize().x;

		emptyHeartWidth = textureEmptyHeart.getSize().x;
		emptyHeartHeight = textureEmptyHeart.getSize().y;
	}
};

#endif // !

