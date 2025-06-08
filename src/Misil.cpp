#include "../include/Misil.hpp"

Misil::Misil(float x, float y) : velocidad(7.0f) {
    shape.setSize(sf::Vector2f(8, 24));
    shape.setFillColor(sf::Color::Yellow);
    shape.setOrigin(shape.getSize().x / 2, shape.getSize().y);
    shape.setPosition(x, y);
}

void Misil::mover() {
    shape.move(0, -velocidad);
}

void Misil::draw(sf::RenderWindow& window) {
    window.draw(shape);
}

bool Misil::fueraDePantalla(float altoVentana) const {
    return shape.getPosition().y + shape.getSize().y < 0;
}

sf::FloatRect Misil::getBounds() const {
    return shape.getGlobalBounds();
}
