#include "../include/Nave.hpp"
#include <iostream>

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
    velocidad = 0.5f; // 10 veces más lento que 5.0f
}

void Nave::mover(const sf::RenderWindow& window) {
    // Movimiento libre, sin límites de ventana
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        sprite.move(-velocidad, 0);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        sprite.move(velocidad, 0);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        sprite.move(0, -velocidad);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        sprite.move(0, velocidad);
}

void Nave::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}

sf::Sprite& Nave::getSprite() {
    return sprite;
}
