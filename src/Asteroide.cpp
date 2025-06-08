#include "../include/Asteroide.hpp"
#include <cstdlib>

Asteroide::Asteroide(float x_, float y_) : x(x_), y(y_) {
    shape.setRadius(20.f);
    shape.setPointCount(20);
    shape.setFillColor(sf::Color(120, 120, 120));
    shape.setOutlineColor(sf::Color::Red);
    shape.setOutlineThickness(3);
    shape.setPosition(x, y);
}

float Asteroide::X() const { return x; }
float Asteroide::Y() const { return y; }

void Asteroide::dibujar(sf::RenderWindow& window) {
    shape.setPosition(x, y);
    window.draw(shape);
}

void Asteroide::mover(float limiteY, float limiteX, float velocidadY) {
    y += velocidadY;
    if (y > limiteY) {
        x = static_cast<float>(rand() % static_cast<int>(limiteX - 40) + 20);
        y = 0;
    }
    shape.setPosition(x, y);
}

void Asteroide::colision(Nave& nave) {
    if (shape.getGlobalBounds().intersects(nave.getSprite().getGlobalBounds())) {
        // Aquí puedes reducir vidas, resetear posición, etc.
        x = static_cast<float>(rand() %  (int)(800 - 40) + 20);
        y = 0;
        // Ejemplo: nave pierde vida (debes implementar la lógica en Nave)
        // nave.perderVida();
    }
}
