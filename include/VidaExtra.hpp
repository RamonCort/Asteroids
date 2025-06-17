#pragma once
#include <SFML/Graphics.hpp>
#include "Nave.hpp"

class VidaExtra {
public:
    VidaExtra(float x, float y);
    void mover(float limiteY, float limiteX, float velocidadY = 1.0f);
    void dibujar(sf::RenderWindow& window);
    bool colision(Nave& nave);
    void Reiniciar(float limiteX);
    float getY() const;
    float getX() const { return x; }
    void setX(float nx) { x = nx; shape.setPosition(x, y); }
    void setY(float ny) { y = ny; shape.setPosition(x, y); }
    void setPos(float nx, float ny) { x = nx; y = ny; shape.setPosition(x, y); }
private:
    float x, y;
    sf::CircleShape shape;
    sf::Texture corazonTexture;
    sf::Sprite corazonSprite;
};
