#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class Ventana {
public:
    Ventana(int width = 400, int height = 300); // Cambia el constructor
    void mostrar();
    void mostrarInicio(); // <-- Nuevo método para la pantalla de inicio
private:
    sf::RenderWindow window;
    sf::Texture texture;
    sf::Sprite sprite;
    sf::Font font;
    sf::Text errorText;
    bool fontLoaded;
};
