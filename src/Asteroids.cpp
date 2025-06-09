#include "../include/Ventana.hpp"

int main() {
    Ventana ventana(800, 600); // Cambia el tamaño aquí
    ventana.mostrarInicio();   // Mostrar pantalla de inicio
    ventana.mostrar();         // Lógica principal del juego
    return 0;
}
