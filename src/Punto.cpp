#include "../include/Punto.hpp"

Punto::Punto() : puntos(0) {}

void Punto::sumar() {
    puntos += 10;
}

int Punto::getPuntos() const {
    return puntos;
}
