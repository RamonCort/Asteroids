#pragma once

class Punto {
public:
    Punto();
    void sumar();
    void sumar(int valor); // Nueva función para sumar puntos variables
    int getPuntos() const;
private:
    int puntos;
};
