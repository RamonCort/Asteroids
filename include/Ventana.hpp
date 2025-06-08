#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class Ventana {
public:
    Ventana(int width = 400, int height = 300); // Cambia el constructor
    void mostrar();
private:
    sf::RenderWindow window;
    sf::Texture texture;
    sf::Sprite sprite;
    sf::Font font;
    sf::Text errorText;
    bool fontLoaded;
};
