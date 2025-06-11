#include "../include/EscudoItem.hpp"
#include <cstdlib>

EscudoItem::EscudoItem(float x_, float y_) : x(x_), y(y_) {
    shape.setRadius(18.f);
    shape.setPointCount(20);
    shape.setFillColor(sf::Color::Red);
    shape.setOutlineColor(sf::Color::White);
    shape.setOutlineThickness(3);
    shape.setPosition(x, y);
}

void EscudoItem::mover(float limiteY, float limiteX, float velocidadY) {
    y += velocidadY;
    if (y > limiteY) {
        reset(limiteX);
    }
    shape.setPosition(x, y);
}

void EscudoItem::dibujar(sf::RenderWindow& window) {
    shape.setPosition(x, y);
    window.draw(shape);
}

bool EscudoItem::colision(Nave& nave) {
    if (shape.getGlobalBounds().intersects(nave.getSprite().getGlobalBounds())) {
        return true;
    }
    return false;
}

void EscudoItem::reset(float limiteX) {
    x = static_cast<float>(rand() % static_cast<int>(limiteX - 40) + 20);
    y = 0;
    shape.setPosition(x, y);
}

float EscudoItem::getY() const {
    return y;
}
