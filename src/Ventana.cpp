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

void Ventana::mostrarInicio() {
    sf::Font fontInicio;
    if (!fontInicio.loadFromFile("assets/arial.ttf")) {
        // Si no se puede cargar la fuente, usar por defecto
    }
    sf::Text textoInicio;
    textoInicio.setFont(fontInicio);
    textoInicio.setString("Presiona cualquier tecla para empezar con el juego");
    textoInicio.setCharacterSize(36);
    textoInicio.setFillColor(sf::Color::White);
    textoInicio.setStyle(sf::Text::Bold);
    // Centrar el texto
    sf::FloatRect bounds = textoInicio.getLocalBounds();
    textoInicio.setOrigin(bounds.width / 2, bounds.height / 2);
    textoInicio.setPosition(window.getSize().x / 2.f, window.getSize().y / 2.f);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed)
                return; // Sale al presionar cualquier tecla
        }
        window.clear(sf::Color::Black);
        window.draw(textoInicio);
        window.display();
    }
}

// Nueva función para seleccionar nave
int seleccionarNave(sf::RenderWindow& window) {
    sf::Texture tex1, tex2;
    tex1.loadFromFile("assets/images/AstroNave_pixil.png");
    tex2.loadFromFile("assets/images/nave.png");
    sf::Sprite nave1(tex1), nave2(tex2);
    nave1.setScale(2,2); nave2.setScale(2,2);
    nave1.setPosition(window.getSize().x/2.f-200, window.getSize().y/2.f);
    nave2.setPosition(window.getSize().x/2.f+100, window.getSize().y/2.f);
    int seleccion = 0; // 0 = AstroNave, 1 = nave normal
    bool elegido = false;
    sf::Font font;
    font.loadFromFile("assets/arial.ttf");
    sf::Text txt("Elige tu nave: ← → ENTER", font, 32);
    txt.setFillColor(sf::Color::White);
    txt.setPosition(window.getSize().x/2.f-200, window.getSize().y/2.f-100);
    while(window.isOpen() && !elegido) {
        sf::Event event;
        while(window.pollEvent(event)) {
            if(event.type == sf::Event::Closed) window.close();
            if(event.type == sf::Event::KeyPressed) {
                if(event.key.code == sf::Keyboard::Left) seleccion = 0;
                if(event.key.code == sf::Keyboard::Right) seleccion = 1;
                if(event.key.code == sf::Keyboard::Enter) elegido = true;
            }
        }
        window.clear(sf::Color::Black);
        window.draw(txt);
        if(seleccion==0) nave1.setColor(sf::Color::Yellow), nave2.setColor(sf::Color::White);
        else nave1.setColor(sf::Color::White), nave2.setColor(sf::Color::Yellow);
        window.draw(nave1); window.draw(nave2);
        window.display();
    }
    return seleccion;
}

void Ventana::mostrar() {
    // --- Fondo ---
    sf::Texture fondoTexture;
    if (!fondoTexture.loadFromFile("assets/images/Fondo3.png")) {
        std::cerr << "No se pudo cargar el fondo: assets/images/Fondo3.png" << std::endl;
    }
    sf::Sprite fondoSprite(fondoTexture);
    // Escalar el fondo para que cubra toda la ventana
    float scaleX = window.getSize().x / fondoSprite.getLocalBounds().width;
    float scaleY = window.getSize().y / fondoSprite.getLocalBounds().height;
    fondoSprite.setScale(scaleX, scaleY);

    // --- Selección de nave ---
    int naveSeleccionada = seleccionarNave(window);
    std::string navePath = naveSeleccionada==0 ? "assets/images/AstroNave_pixil.png" : "assets/images/nave.png";

    while (window.isOpen()) {
        // --- Bucle de juego principal ---
        // Variables de juego
        float cx = window.getSize().x / 2.f;
        float cy = window.getSize().y / 2.f;
        Nave nave(cx, cy, navePath); // Modifica el constructor de Nave para aceptar ruta

        std::vector<Misil> misiles;
        bool disparoAnterior = false;

        Margen margen(window.getSize().x, window.getSize().y);
        Punto punto;
        sf::Font fontPuntos;
        bool fuenteCargada = fontPuntos.loadFromFile("assets/arial.ttf");
        Puntaje puntaje(window.getSize().x);
        Vida vida;
        int vidas = 3;
        vida.setVidas(vidas);

        std::vector<Asteroide> asteroides;
        int cantidadAsteroides = 5;
        float limiteX = window.getSize().x;
        float limiteY = window.getSize().y;

        sf::Clock relojAsteroides;
        float tiempoEntreAsteroides = 2.5f;

        float velocidadAsteroide = 0.6f;
        int ultimoPuntajeVel = 0;

        for (int i = 0; i < cantidadAsteroides; ++i) {
            float ax = static_cast<float>(rand() % static_cast<int>(limiteX - 40) + 20);
            float ay = static_cast<float>(rand() % 100);
            asteroides.emplace_back(ax, ay);
        }

        bool pAnterior = false;
        bool gameOver = false;

        // Música (opcional, solo la primera vez)
        static bool musicaIniciada = false;
        static sf::Music music;
        if (!musicaIniciada) {
            if (music.openFromFile("assets/music/videoplayback.ogg")) {
                music.setLoop(true);
                music.play();
            }
            musicaIniciada = true;
        }

        // --- Bucle principal del juego ---
        while (window.isOpen() && !gameOver) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    window.close();
            }
            window.clear(sf::Color::Black);
            window.draw(fondoSprite); // Dibuja el fondo antes de todo

            margen.draw(window);
            nave.mover(window);
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

            // --- COLISIONES MISIL-ASTEROIDE ---
            for (auto itAst = asteroides.begin(); itAst != asteroides.end(); ) {
                bool asteroideEliminado = false;
                for (auto itMisil = misiles.begin(); itMisil != misiles.end(); ) {
                    if (itAst->shape.getGlobalBounds().intersects(itMisil->getBounds())) {
                        itMisil = misiles.erase(itMisil);
                        itAst = asteroides.erase(itAst);
                        asteroideEliminado = true;
                        punto.sumar(10);
                        break;
                    } else {
                        ++itMisil;
                    }
                }
                if (!asteroideEliminado) {
                    ++itAst;
                }
            }

            // --- COLISIONES ASTEROIDE-NAVE ---
            for (auto& ast : asteroides) {
                if (ast.shape.getGlobalBounds().intersects(nave.getSprite().getGlobalBounds())) {
                    vidas--;
                    vida.setVidas(vidas);
                    ast.shape.setPosition(
                        static_cast<float>(rand() % static_cast<int>(limiteX - 40) + 20),
                        0
                    );
                    ast.y = 0;
                    ast.x = ast.shape.getPosition().x;
                    if (vidas <= 0) {
                        gameOver = true;
                        break;
                    }
                }
            }

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
            if (asteroides.size() < cantidadAsteroides && relojAsteroides.getElapsedTime().asSeconds() >= tiempoEntreAsteroides) {
                float ax = static_cast<float>(rand() % static_cast<int>(limiteX - 40) + 20);
                float ay = static_cast<float>(rand() % 100);
                asteroides.emplace_back(ax, ay);
                relojAsteroides.restart();
            }

            // Mover y dibujar asteroides con velocidad variable
            for (auto& ast : asteroides) {
                ast.mover(limiteY, limiteX, velocidadAsteroide);
                ast.dibujar(window);
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

            vida.draw(window);
            puntaje.setPuntos(punto.getPuntos());
            puntaje.draw(window);

            window.display();
        }

        // --- Mostrar pantalla de Game Over ---
        if (window.isOpen()) {
            sf::Font fontFin;
            fontFin.loadFromFile("assets/arial.ttf");
            sf::Text textoFin;
            textoFin.setFont(fontFin);
            textoFin.setString("Juego terminado\nPuntaje: " + std::to_string(punto.getPuntos()) + "\nPresiona ESPACIO para volver a jugar");
            textoFin.setCharacterSize(40);
            textoFin.setFillColor(sf::Color::White);
            textoFin.setStyle(sf::Text::Bold);
            sf::FloatRect bounds = textoFin.getLocalBounds();
            textoFin.setOrigin(bounds.width / 2, bounds.height / 2);
            textoFin.setPosition(window.getSize().x / 2.f, window.getSize().y / 2.f);

            while (window.isOpen()) {
                sf::Event event;
                while (window.pollEvent(event)) {
                    if (event.type == sf::Event::Closed)
                        window.close();
                    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space)
                        goto reiniciar_juego;
                }
                window.clear(sf::Color::Black);
                window.draw(textoFin);
                window.display();
            }
        }
        // Si la ventana se cerró, salimos del bucle
        break;
reiniciar_juego:
        // El bucle while(window.isOpen()) se repite y reinicia el juego
        continue;
    }
}