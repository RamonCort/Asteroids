#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class Nave {
public:
    Nave(float x, float y, const std::string& ruta = "assets/images/nave.png");
    void Dibujar(sf::RenderWindow& window);
    void Mover(const sf::RenderWindow& window);
    sf::Sprite& ObtenerSprite(); // <-- Añadido para Margen
    float ObtenerVelocidad() const { return velocidad; }
    void EstablecerVelocidad(float v) { velocidad = v; }
protected:
    sf::Texture texture;
    sf::Sprite sprite;
    float velocidad = 5.0f;
};
