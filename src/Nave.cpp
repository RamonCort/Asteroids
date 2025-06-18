#include "../include/Nave.hpp"
#include <iostream>
#include <cmath> // Incluir cmath para std::atan2

Nave::Nave(float x, float y, const std::string& ruta) {
    if (!texture.loadFromFile(ruta)) {
        std::cerr << "No se pudo cargar la imagen: " << ruta << std::endl;
    }
    sprite.setTexture(texture);
    sf::FloatRect bounds = sprite.getLocalBounds();
    // Cambia el tamaño de la nave (por ejemplo, al doble)
    sprite.setScale(2.0f, 2.0f);
    sprite.setOrigin(bounds.width / 2, bounds.height / 2);
    sprite.setPosition(x, y);
    velocidad = 1.0f; // Ahora el doble de rápido que antes (antes 0.5f)
}

void Nave::Mover(const sf::RenderWindow& window) {
    sf::Vector2f movimiento(0.f, 0.f);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        movimiento.x -= velocidad;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        movimiento.x += velocidad;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        movimiento.y -= velocidad;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        movimiento.y += velocidad;
    sprite.move(movimiento);
    // Rotar la nave según la dirección de movimiento
    if (movimiento.x != 0.f || movimiento.y != 0.f) {
        float angulo = std::atan2(movimiento.y, movimiento.x) * 180.f / 3.14159265f + 90.f;
        sprite.setRotation(angulo);
    }
}

void Nave::Dibujar(sf::RenderWindow& window) {
    window.draw(sprite);
}

sf::Sprite& Nave::ObtenerSprite() {
    return sprite;
}
