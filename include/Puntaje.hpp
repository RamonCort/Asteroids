#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class Puntaje {
public:
    Puntaje(float windowWidth);
    void setPuntos(int puntos);
    void draw(sf::RenderWindow& window);
private:
    sf::RectangleShape box;
    sf::Font font;
    sf::Text texto;
    float width;
    float height;
};
