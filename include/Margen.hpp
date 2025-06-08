#pragma once
#include <SFML/Graphics.hpp>
#include "Nave.hpp"

class Margen {
public:
    Margen(float ancho, float alto, float grosor = 5.f);
    void draw(sf::RenderWindow& window);
    void limitar(Nave& nave);
private:
    float ancho;
    float alto;
    float grosor;
    sf::RectangleShape top, bottom, left, right;
};
