#include "../include/Ventana.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "../include/Nave.hpp"
#include "../include/Misil.hpp"
#include "../include/Margen.hpp"
#include "../include/Punto.hpp"
#include "../include/Puntaje.hpp"
#include "../include/Vida.hpp"
#include <vector>
#include "../include/Asteroide.hpp"

// Constructor
Ventana::Ventana(int width, int height) : window(sf::VideoMode(1200, 900), "Asteroids - Ventana de inicio"), fontLoaded(false) {
    if (!texture.loadFromFile("assets/images/nave.png")) {
        std::cerr << "No se pudo cargar la imagen: assets/images/nave.png" << std::endl;
    } else {
        sprite.setTexture(texture);
        sprite.setPosition(100, 100);
    }
    // (Eliminado el bloque de carga de fuente y configuración de errorText)
}

void Ventana::mostrar() {
    // Reproducir música al abrir la ventana
    sf::Music music;
    if (music.openFromFile("assets/music/videoplayback.ogg")) {
        music.setLoop(true);
        music.play();
    }
    float cx = window.getSize().x / 2.f;
    float cy = window.getSize().y / 2.f;
    Nave nave(cx, cy); // Crea la nave centrada

    std::vector<Misil> misiles;
    bool disparoAnterior = false;

    // Instanciar el margen (usar el tamaño de la ventana)
    Margen margen(window.getSize().x, window.getSize().y);
    Punto punto;
    sf::Font fontPuntos;
    bool fuenteCargada = fontPuntos.loadFromFile("assets/arial.ttf");
    Puntaje puntaje(window.getSize().x);
    Vida vida;
    int vidas = 3; // Puedes actualizar este valor según la lógica de tu juego
    vida.setVidas(vidas);

    // Nueva sección para asteroides
    std::vector<Asteroide> asteroides;
    int cantidadAsteroides = 5;
    float limiteX = window.getSize().x;
    float limiteY = window.getSize().y;

    sf::Clock relojAsteroides;
    int asteroidesCreados = 0;
    float tiempoEntreAsteroides = 2.5f; // Más dispersión (2.5 segundos entre cada uno)

    float velocidadAsteroide = 0.6f; // velocidad inicial (5 veces más lento que 3)
    int ultimoPuntajeVel = 0;

    // Inicializa los asteroides en posiciones aleatorias arriba
    for (int i = 0; i < cantidadAsteroides; ++i) {
        float ax = static_cast<float>(rand() % static_cast<int>(limiteX - 40) + 20);
        float ay = static_cast<float>(rand() % 100);
        asteroides.emplace_back(ax, ay);
    }

    bool pAnterior = false;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear(sf::Color::Black);

        // Dibuja el margen antes de los demás elementos
        margen.draw(window);

        // Movimiento nave
        nave.mover(window);

        // Limitar la nave dentro del margen
        margen.limitar(nave);

        // Disparo de misil al presionar espacio (solo una vez por pulsación)
        bool disparoActual = sf::Keyboard::isKeyPressed(sf::Keyboard::Space);
        if (disparoActual && !disparoAnterior) {
            sf::Vector2f navePos = nave.getSprite().getPosition();
            float misilX = navePos.x;
            float misilY = navePos.y - nave.getSprite().getGlobalBounds().height / 2;
            misiles.emplace_back(misilX, misilY);
        }
        disparoAnterior = disparoActual;

        // Mover y dibujar misiles
        for (auto it = misiles.begin(); it != misiles.end(); ) {
            it->mover();
            if (it->fueraDePantalla(0)) {
                it = misiles.erase(it);
            } else {
                it->draw(window);
                ++it;
            }
        }

        // Aumentar velocidad de los asteroides cada 30 puntos en un 20%
        int puntosActuales = punto.getPuntos();
        if (puntosActuales >= 30 && (puntosActuales / 30) > (ultimoPuntajeVel / 30)) {
            velocidadAsteroide *= 1.2f;
            ultimoPuntajeVel = puntosActuales;
        }

        // Crear un nuevo asteroide cada 2.5 segundos hasta llegar a la cantidad deseada
        if (asteroidesCreados < cantidadAsteroides && relojAsteroides.getElapsedTime().asSeconds() >= tiempoEntreAsteroides) {
            float ax = static_cast<float>(rand() % static_cast<int>(limiteX - 40) + 20);
            float ay = static_cast<float>(rand() % 100);
            asteroides.emplace_back(ax, ay);
            asteroidesCreados++;
            relojAsteroides.restart();
        }

        // Mover y dibujar asteroides con velocidad variable
        for (auto& ast : asteroides) {
            ast.mover(limiteY, limiteX, velocidadAsteroide);
            ast.dibujar(window);
            // ast.colision(nave); // si quieres colisión
        }

        nave.draw(window);

        if (fontLoaded) {
            errorText.setString("No se pudo cargar la imagen:\nassets/nave.png");
            window.draw(errorText);
        }

        // Sumar puntos solo una vez por pulsación de 'P'
        bool pActual = sf::Keyboard::isKeyPressed(sf::Keyboard::P);
        if (pActual && !pAnterior) {
            punto.sumar();
        }
        pAnterior = pActual;

        // Mostrar puntos en pantalla solo si la fuente se cargó correctamente
        if (fuenteCargada) {
            sf::Text textoPuntos;
            textoPuntos.setFont(fontPuntos);
            textoPuntos.setString("Puntos: " + std::to_string(punto.getPuntos()));
            textoPuntos.setCharacterSize(32);
            textoPuntos.setFillColor(sf::Color::White);
            textoPuntos.setPosition(20, 20);
            window.draw(textoPuntos);
        }

        // Dibuja el recuadro de vidas en la parte superior izquierda
        vida.draw(window);

        // Actualizar y dibujar el recuadro marcador arriba a la derecha
        puntaje.setPuntos(punto.getPuntos());
        puntaje.draw(window);

        window.display();
    }
}