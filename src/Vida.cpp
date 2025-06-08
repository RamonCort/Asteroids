#include "../include/Vida.hpp"

Vida::Vida() : width(200), height(60) {
    box.setSize(sf::Vector2f(width, height));
    box.setFillColor(sf::Color(30,30,30,200));
    box.setOutlineColor(sf::Color::White);
    box.setOutlineThickness(3);
    box.setPosition(20, 20);

    if (font.loadFromFile("assets/arial.ttf")) {
        texto.setFont(font);
    }
    texto.setCharacterSize(28);
    texto.setFillColor(sf::Color::White);
    texto.setPosition(30, 30);
    texto.setString("Vidas : 3");
}

void Vida::setVidas(int vidas) {
    texto.setString("Vidas : " + std::to_string(vidas));
}

void Vida::draw(sf::RenderWindow& window) {
    window.draw(box);
    window.draw(texto);
}
