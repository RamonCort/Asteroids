#include "../include/Misil.hpp"

sf::Texture Misil::texturaDisparo; // Definición de la textura estática

Misil::Misil(float x, float y) : velocidad(7.0f) {
    if (texturaDisparo.getSize().x == 0) {
        texturaDisparo.loadFromFile("assets/images/Disparo.png");
    }
    if (texturaDisparo.getSize().x > 0) {
        frameActual = 0;
        totalFrames = 5;
        framesPorFila = 5;
        frameWidth = 125;
        frameHeight = 313;
        tiempoPorFrame = 0.08f;
        spriteDisparo.setTexture(texturaDisparo);
        spriteDisparo.setTextureRect(sf::IntRect(0, 0, frameWidth, frameHeight));
        spriteDisparo.setOrigin(frameWidth / 2, frameHeight);
        spriteDisparo.setPosition(x, y);
        spriteDisparo.setScale(0.15f, 0.15f);
        relojAnimacion.restart();
    } else {
        shape.setSize(sf::Vector2f(8, 24));
        shape.setFillColor(sf::Color::Yellow);
        shape.setOrigin(shape.getSize().x / 2, shape.getSize().y);
        shape.setPosition(x, y);
    }
}

void Misil::Mover() {
    if (texturaDisparo.getSize().x > 0) {
        spriteDisparo.move(0, -velocidad);
        // Animación de frames (solo primera fila)
        if (relojAnimacion.getElapsedTime().asSeconds() > tiempoPorFrame) {
            frameActual = (frameActual + 1) % totalFrames;
            int columna = frameActual % framesPorFila;
            int fila = 0; // Solo la primera fila
            spriteDisparo.setTextureRect(sf::IntRect(columna * frameWidth, fila * frameHeight, frameWidth, frameHeight));
            relojAnimacion.restart();
        }
    } else {
        shape.move(0, -velocidad);
    }
}

void Misil::Dibujar(sf::RenderWindow& window) {
    if (texturaDisparo.getSize().x > 0)
        window.draw(spriteDisparo);
    else
        window.draw(shape);
}

bool Misil::FueraDePantalla(float altoVentana) const {
    if (texturaDisparo.getSize().x > 0)
        return spriteDisparo.getPosition().y + frameHeight < 0;
    else
        return shape.getPosition().y + shape.getSize().y < 0;
}

sf::FloatRect Misil::ObtenerLimites() const {
    if (texturaDisparo.getSize().x > 0)
        return spriteDisparo.getGlobalBounds();
    else
        return shape.getGlobalBounds();
}
