#pragma once
#include <SFML/Graphics.hpp>

class Nave {
public:
    Nave(float x, float y);
    void draw(sf::RenderWindow& window);
    void mover(const sf::RenderWindow& window);
    sf::Sprite& getSprite(); // <-- Añadido para Margen
private:
    sf::Texture texture;
    sf::Sprite sprite;
    float velocidad = 5.0f;
};
