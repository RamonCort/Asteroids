#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;
class Nave
{
public:
    Nave(sf::Vector2f position)
    {
        shape.setSize(sf::Vector2f(50, 50));
        shape.setPosition(position);
        shape.setFillColor(sf::Color::Transparent);

        // Cambia la ruta a la imagen de tu nave
        if (!texture.loadFromFile("./assets/images/nave.png"))
        {
            cout << "No se pudo cargar la imagen de la nave" << std::endl;
        }
        sprite = sf::Sprite(texture);
        sprite.setPosition(position);

        // Ajusta el tamaño del sprite si es necesario
        sprite.setScale(0.5f, 0.5f); // Cambia el factor según el tamaño de tu imagen
    }

    void move(float offsetX, float offsetY)
    {
        sprite.move(offsetX, offsetY);
        shape.move(offsetX, offsetY);
    }

    void draw(sf::RenderWindow &window)
    {
        window.draw(sprite);
        // window.draw(shape); // Si no quieres mostrar el cuadro, comenta esta línea
    }

    void update()
    {
        // Si tienes animación de nave, ajusta aquí el recorte
        // sprite.setTextureRect(sf::IntRect(...));
    }

private:
    sf::RectangleShape shape;
    sf::Sprite sprite;
    sf::Texture texture;
};

double velocidad = 0.5;

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Nave Espacial");

    Nave nave(sf::Vector2f(400, 300));

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            nave.move(-velocidad, 0);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            nave.move(velocidad, 0);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            nave.move(0, -velocidad);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            nave.move(0, velocidad);
        }

        nave.update();

        window.clear();
        nave.draw(window);
        window.display();
    }

    return 0;
}
