#ifndef OPORTUNIDAD_HPP
#define OPORTUNIDAD_HPP

class Oportunidad {
public:
    Oportunidad(int oportunidades = 3, int vidasPorOportunidad = 3);
    void perderVida();
    int getVidas() const;
    int getOportunidades() const;
    bool sinOportunidades() const;
    void reiniciar();
    void sumarVida();
private:
    int oportunidades;
    int vidas;
    int vidasPorOportunidad;
};

#endif // OPORTUNIDAD_HPP
