#include "../include/Ventana.hpp"

int main() {
    Ventana ventana(800, 600); // Cambia el tamaño aquí
    ventana.MostrarInicio();   // Mostrar pantalla de inicio
    ventana.Mostrar();         // Lógica principal del juego
    return 0;
}
