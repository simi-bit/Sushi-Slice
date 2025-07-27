#ifndef GAME_OVER
#define GAME_OVER

#include <SFML/Graphics.hpp>

class GameOver {
private:
    sf::RenderWindow* window;
    sf::Text* gameOverText;
    sf::Text* instructionText;

public:
    GameOver(sf::RenderWindow* window, sf::Text *gameOverText, sf::Text* instructionText) {
        // Maak de "Game Over" tekst aan
        gameOverText->setString("GAME OVER");
        gameOverText->setCharacterSize(100); // Grootte van de tekst
        gameOverText->setFillColor(sf::Color::Red); // Kleur van de tekst


        // Centreer de tekst
        sf::FloatRect textRect = gameOverText->getLocalBounds();
        gameOverText->setOrigin(textRect.getCenter());
        gameOverText->setPosition(sf::Vector2f(window->getSize().x / 2.0f, window->getSize().y / 2.0f - 50));

        //sf::Text NextTimeText(font);
        //NextTimeText.setFont(font);
        //NextTimeText.setString("Volgende keer beter!");
        //NextTimeText.setCharacterSize(50); // Grootte van de tekst
        //NextTimeText.setFillColor(sf::Color::White);

        // Centreer de tekst
        // sf::FloatRect nextTimeRect = NextTimeText.getLocalBounds();
        // NextTimeText.setOrigin(nextTimeRect.getCenter());
        // NextTimeText.setPosition(sf::Vector2f(window.getSize().x / 2.0f, window.getSize().y / 2.0f + 50));

        // Maak de instructietekst aan
        instructionText->setString("Druk op [R] om opnieuw te spelen of [ESC] om af te sluiten.");
        instructionText->setCharacterSize(30);
        instructionText->setFillColor(sf::Color::White);

        // Centreer de instructietekst
        sf::FloatRect instructionRect = instructionText->getLocalBounds();
        instructionText->setOrigin(instructionRect.getCenter());
        instructionText->setPosition(sf::Vector2f(window->getSize().x / 2.0f, window->getSize().y / 2.0f + 50));

        // Giving the display() function access to these vars
        this->window = window;
        this->gameOverText = gameOverText;
        this->instructionText = instructionText;
    }

    void display() {
        window->clear(sf::Color::Black);
        window->draw(*gameOverText);
        window->draw(*instructionText);
    }
};

#endif // !GAME_OVER
