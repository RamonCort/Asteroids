#include "../include/Margen.hpp"

Margen::Margen(float ancho, float alto, float grosor)
    : ancho(ancho), alto(alto), grosor(grosor)
{
    top.setSize(sf::Vector2f(ancho, grosor));
    top.setPosition(0, 0);
    top.setFillColor(sf::Color::White);

    bottom.setSize(sf::Vector2f(ancho, grosor));
    bottom.setPosition(0, alto - grosor);
    bottom.setFillColor(sf::Color::White);

    left.setSize(sf::Vector2f(grosor, alto));
    left.setPosition(0, 0);
    left.setFillColor(sf::Color::White);

    right.setSize(sf::Vector2f(grosor, alto));
    right.setPosition(ancho - grosor, 0);
    right.setFillColor(sf::Color::White);
}

void Margen::draw(sf::RenderWindow& window) {
    window.draw(top);
    window.draw(bottom);
    window.draw(left);
    window.draw(right);
}

void Margen::limitar(Nave& nave) {
    sf::Sprite& sprite = nave.getSprite();
    sf::FloatRect bounds = sprite.getGlobalBounds();

    float minX = grosor + bounds.width / 2;
    float maxX = ancho - grosor - bounds.width / 2;
    float minY = grosor + bounds.height / 2;
    float maxY = alto - grosor - bounds.height / 2;

    sf::Vector2f pos = sprite.getPosition();
    if (pos.x < minX) pos.x = minX;
    if (pos.x > maxX) pos.x = maxX;
    if (pos.y < minY) pos.y = minY;
    if (pos.y > maxY) pos.y = maxY;
    sprite.setPosition(pos);
}
