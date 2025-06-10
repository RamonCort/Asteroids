#include "../include/Asteroide.hpp"
#include "../include/Misil.hpp"
#include <cstdlib>

sf::Texture Asteroide::textureAsteroide;
bool Asteroide::textureCargada = false;

Asteroide::Asteroide(float x_, float y_) : x(x_), y(y_) {
    if (!textureCargada) {
        if (!textureAsteroide.loadFromFile("assets/images/Asteroide.pixil.png")) {
            // Si falla, usar círculo como fallback
            shape.setRadius(20.f);
            shape.setPointCount(20);
            shape.setFillColor(sf::Color(120, 120, 120));
            shape.setOutlineColor(sf::Color::Red);
            shape.setOutlineThickness(3);
            shape.setPosition(x, y);
            return;
        }
        textureCargada = true;
    }
    sprite.setTexture(textureAsteroide);
    sprite.setOrigin(textureAsteroide.getSize().x/2, textureAsteroide.getSize().y/2);
    sprite.setPosition(x, y);
    sprite.setScale(0.5f, 0.5f); // Ajusta el tamaño si es necesario
}

float Asteroide::X() const { return x; }
float Asteroide::Y() const { return y; }

void Asteroide::dibujar(sf::RenderWindow& window) {
    if (textureCargada) {
        sprite.setPosition(x, y);
        window.draw(sprite);
    } else {
        shape.setPosition(x, y);
        window.draw(shape);
    }
}

void Asteroide::mover(float limiteY, float limiteX, float velocidadY) {
    y += velocidadY;
    if (y > limiteY) {
        x = static_cast<float>(rand() % static_cast<int>(limiteX - 40) + 20);
        y = 0;
    }
    if (textureCargada) sprite.setPosition(x, y);
    else shape.setPosition(x, y);
}

void Asteroide::colision(Nave& nave) {
    if (textureCargada) {
        if (sprite.getGlobalBounds().intersects(nave.getSprite().getGlobalBounds())) {
            x = static_cast<float>(rand() %  (int)(800 - 40) + 20);
            y = 0;
        }
    } else {
        if (shape.getGlobalBounds().intersects(nave.getSprite().getGlobalBounds())) {
            x = static_cast<float>(rand() %  (int)(800 - 40) + 20);
            y = 0;
        }
    }
}

bool Asteroide::colisionaConNave(Nave& nave) {
    if (textureCargada) {
        return sprite.getGlobalBounds().intersects(nave.getSprite().getGlobalBounds());
    } else {
        return shape.getGlobalBounds().intersects(nave.getSprite().getGlobalBounds());
    }
}

bool Asteroide::colisionaConMisil(const Misil& misil) {
    if (textureCargada) {
        return sprite.getGlobalBounds().intersects(misil.getBounds());
    } else {
        return shape.getGlobalBounds().intersects(misil.getBounds());
    }
}
