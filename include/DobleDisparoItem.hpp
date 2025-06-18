#pragma once
#include <SFML/Graphics.hpp>

class DobleDisparoItem {
public:
    DobleDisparoItem(float x, float y);
    void mover(float limiteY, float limiteX, float velocidadY = 1.0f);
    void dibujar(sf::RenderWindow& window);
    bool colision(sf::Sprite& naveSprite);
    void reiniciar(float limiteX);
    float getY() const;
    float getX() const { return x; }
    void setPos(float nx, float ny) { x = nx; y = ny; shape.setPosition(x, y); }
private:
    float x, y;
    sf::CircleShape shape;
    float angulo;
    float velocidadRotacion;
    int direccionRotacion;
    sf::Clock relojCambioDireccion;
};
