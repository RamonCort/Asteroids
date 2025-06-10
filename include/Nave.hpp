#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class Nave {
public:
    Nave(float x, float y, const std::string& ruta = "assets/images/nave.png");
    void draw(sf::RenderWindow& window);
    void mover(const sf::RenderWindow& window);
    sf::Sprite& getSprite(); // <-- Añadido para Margen
protected:
    sf::Texture texture;
    sf::Sprite sprite;
    float velocidad = 5.0f;
};
