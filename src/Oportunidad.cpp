// Agrega el include correcto para el método miembro
#include "../include/Oportunidad.hpp"
void Oportunidad::sumarVida() {
    if (vidas < vidasPorOportunidad) {
        vidas++;
    }
}
#include "../include/Oportunidad.hpp"

Oportunidad::Oportunidad(int oportunidades, int vidasPorOportunidad)
    : oportunidades(oportunidades), vidas(vidasPorOportunidad), vidasPorOportunidad(vidasPorOportunidad) {}

void Oportunidad::perderVida() {
    vidas--;
    if (vidas <= 0) {
        oportunidades--;
        if (oportunidades > 0) {
            vidas = vidasPorOportunidad;
        }
    }
}

int Oportunidad::getVidas() const {
    return vidas;
}

int Oportunidad::getOportunidades() const {
    return oportunidades;
}

bool Oportunidad::sinOportunidades() const {
    return oportunidades <= 0;
}

void Oportunidad::reiniciar() {
    oportunidades = 3;
    vidas = vidasPorOportunidad;
}
