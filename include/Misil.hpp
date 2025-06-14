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
    static sf::Texture texturaDisparo;
    sf::Sprite spriteDisparo;
    float velocidad;

    // Variables para animación de sprite
    int frameActual = 0;
    int totalFrames = 5; // Solo la primera fila
    int framesPorFila = 5;
    int frameWidth = 125;
    int frameHeight = 313;
    float tiempoPorFrame = 0.08f;
    sf::Clock relojAnimacion;
};
