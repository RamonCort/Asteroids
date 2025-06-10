#pragma once
#include <SFML/Graphics.hpp>
#include "Nave.hpp"
#include "Misil.hpp"

class Asteroide {
public:
    Asteroide(float x, float y);
    float X() const;
    float Y() const;
    void dibujar(sf::RenderWindow& window);
    void mover(float limiteY, float limiteX, float velocidadY = 3.0f); // velocidadY por defecto 3.0f
    void colision(Nave& nave);
    bool colisionaConNave(Nave& nave);
    bool colisionaConMisil(const Misil& misil);
    sf::CircleShape shape; // <-- Fallback si no hay textura
    float x, y; // <-- Posición
    static sf::Texture textureAsteroide;
    static bool textureCargada;
    sf::Sprite sprite;
};
