#include "../include/Ventana.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "../include/Nave.hpp"
#include "../include/Misil.hpp"
#include "../include/Margen.hpp" // <-- Añadir esta línea
#include <vector>

// Constructor
Ventana::Ventana(int width, int height) : window(sf::VideoMode(1200, 900), "Asteroids - Ventana de inicio"), fontLoaded(false) {
    if (!texture.loadFromFile("assets/images/nave.png")) {
        std::cerr << "No se pudo cargar la imagen: assets/images/nave.png" << std::endl;
    } else {
        sprite.setTexture(texture);
        sprite.setPosition(100, 100);
    }
    if (font.loadFromFile("assets/arial.ttf")) {
        fontLoaded = true;
        errorText.setFont(font);
        errorText.setCharacterSize(18);
        errorText.setFillColor(sf::Color::Red);
        errorText.setPosition(10, 10);
    }
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

        nave.draw(window);

        if (fontLoaded) {
            errorText.setString("No se pudo cargar la imagen:\nassets/nave.png");
            window.draw(errorText);
        }
        window.display();
    }
}