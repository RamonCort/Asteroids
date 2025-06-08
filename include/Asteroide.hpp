#pragma once
#include <SFML/Graphics.hpp>
#include "Nave.hpp"

class Asteroide {
public:
    Asteroide(float x, float y);
    float X() const;
    float Y() const;
    void dibujar(sf::RenderWindow& window);
    void mover(float limiteY, float limiteX, float velocidadY = 3.0f); // velocidadY por defecto 3.0f
    void colision(Nave& nave);
private:
    float x, y;
    sf::CircleShape shape;
};
