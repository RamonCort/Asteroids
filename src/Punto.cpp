#include "../include/Punto.hpp"

Punto::Punto() : puntos(0) {}

void Punto::sumar() {
    puntos += 10;
}

void Punto::sumar(int valor) {
    puntos += valor;
}

int Punto::getPuntos() const {
    return puntos;
}
