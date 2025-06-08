#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class Vida {
public:
    Vida();
    void setVidas(int vidas);
    void draw(sf::RenderWindow& window);
private:
    sf::RectangleShape box;
    sf::Font font;
    sf::Text texto;
    float width;
    float height;
};
