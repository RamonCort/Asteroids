#include <SFML/Graphics.hpp>
#include <cstdlib>
#include "../include/DobleDisparoItem.hpp"

DobleDisparoItem::DobleDisparoItem(float x_, float y_) : x(x_), y(y_) {
    shape.setRadius(22.f);
    shape.setPointCount(20);
    shape.setFillColor(sf::Color::Red);
    shape.setOutlineColor(sf::Color::White);
    shape.setOutlineThickness(3);
    shape.setOrigin(22.f, 22.f);
    shape.setPosition(x, y);
    angulo = 0.f;
    velocidadRotacion = 2.f;
    direccionRotacion = 1;
    relojCambioDireccion.restart();
}

void DobleDisparoItem::mover(float limiteY, float limiteX, float velocidadY) {
    y += velocidadY;
    if (y > limiteY) {
        reiniciar(limiteX);
    }
    shape.setPosition(x, y);
    // Animar rotación y cambio de dirección
    if (relojCambioDireccion.getElapsedTime().asSeconds() > 0.7f) {
        direccionRotacion = (rand() % 2 == 0) ? 1 : -1;
        velocidadRotacion = 1.5f + static_cast<float>(rand() % 30) / 10.f;
        relojCambioDireccion.restart();
    }
    angulo += velocidadRotacion * direccionRotacion;
    shape.setRotation(angulo);
}

void DobleDisparoItem::dibujar(sf::RenderWindow& window) {
    shape.setPosition(x, y);
    window.draw(shape);
}

bool DobleDisparoItem::colision(sf::Sprite& naveSprite) {
    return shape.getGlobalBounds().intersects(naveSprite.getGlobalBounds());
}

void DobleDisparoItem::reiniciar(float limiteX) {
    x = static_cast<float>(rand() % static_cast<int>(limiteX - 40) + 20);
    y = 0;
    shape.setPosition(x, y);
}

float DobleDisparoItem::getY() const { return y; }
