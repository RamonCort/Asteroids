#pragma once
#include <SFML/Graphics.hpp>

class Misil {
public:
    Misil(float x, float y);
    void mover();
    void draw(sf::RenderWindow& window);
    bool fueraDePantalla(float altoVentana) const;
    sf::FloatRect getBounds() const;
private:
    sf::RectangleShape shape;
    float velocidad;
};
