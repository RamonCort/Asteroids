// Estrella.hpp
#ifndef ESTRELLA_HPP
#define ESTRELLA_HPP

class Escudo; // Forward declaration
class Tiempo; // Forward declaration

class Estrella {
public:
    Tiempo ActivarInmunidad(Escudo escudo);
};

#endif // ESTRELLA_HPP