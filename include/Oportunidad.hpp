#ifndef OPORTUNIDAD_HPP
#define OPORTUNIDAD_HPP

class Oportunidad {
public:
    Oportunidad(int oportunidades = 3, int vidasPorOportunidad = 3);    void PerderVida();
    int ObtenerVidas() const;
    int ObtenerOportunidades() const;
    bool SinOportunidades() const;
    void Reiniciar();
    void SumarVida();
private:
    int oportunidades;
    int vidas;
    int vidasPorOportunidad;
};

#endif // OPORTUNIDAD_HPP
