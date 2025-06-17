#pragma once
#include <SFML/Graphics.hpp>
#include "Nave.hpp"
#include "Misil.hpp"

class Asteroide {
public:
    Asteroide(float x, float y);
    float ObtenerX() const;
    float ObtenerY() const;
    void Dibujar(sf::RenderWindow& window);
    void Mover(float limiteY, float limiteX, float velocidadY = 3.0f); // velocidadY por defecto 3.0f
    void Colisionar(Nave& nave);
    bool ColisionarConNave(Nave& nave);
    bool ColisionarConMisil(const Misil& misil);
    sf::CircleShape shape; // <-- Fallback si no hay textura
    float x, y; // <-- Posición
    static sf::Texture textureAsteroide;
    static bool textureCargada;
    sf::Sprite sprite;
};
