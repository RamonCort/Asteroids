#include "../include/Escudo.hpp"

Escudo::Escudo(const Punto& pos, const std::string& rutaTextura, int duracion)
    : posicion(pos), duracion(duracion), activo(true) {
    textura.loadFromFile(rutaTextura);
    sprite.setTexture(textura);
    sprite.setPosition(posicion.getX(), posicion.getY());
}

void Escudo::dibujar(sf::RenderWindow& ventana) {
    if (activo) {
        ventana.draw(sprite);
    }
}

void Escudo::actualizar() {
    if (activo && duracion > 0) {
        duracion--;
        if (duracion == 0) {
            activo = false;
        }
    }
}

bool Escudo::estaActivo() const {
    return activo;
}

void Escudo::desactivar() {
    activo = false;
}

const Punto& Escudo::getPosicion() const {
    return posicion;
}

int Escudo::getDuracion() const {
    return duracion;
}
