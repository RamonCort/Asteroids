#pragma once
#include <SFML/Graphics.hpp>
#include "Nave.hpp"

class EscudoItem {
public:
    EscudoItem(float x, float y);
    void mover(float limiteY, float limiteX, float velocidadY = 1.0f);
    void dibujar(sf::RenderWindow& window);
    bool colision(Nave& nave);
    void reset(float limiteX);
    float getY() const;
private:
    float x, y;
    sf::CircleShape shape;
};
