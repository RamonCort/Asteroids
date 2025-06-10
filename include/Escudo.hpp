#ifndef ESCUDO_HPP
#define ESCUDO_HPP

#include "Punto.hpp"
#include <SFML/Graphics.hpp>

class Escudo {
private:
    Punto posicion;
    sf::Sprite sprite;
    sf::Texture textura;
    int duracion;
    bool activo;
public:
    Escudo(const Punto& pos, const std::string& rutaTextura, int duracion);
    void dibujar(sf::RenderWindow& ventana);
    void actualizar();
    bool estaActivo() const;
    void desactivar();
    const Punto& getPosicion() const;
    int getDuracion() const;
};

#endif // ESCUDO_HPP
