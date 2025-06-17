#include "../include/Ventana.hpp"
#include "../include/Oportunidad.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "../include/Nave.hpp"
#include "../include/Misil.hpp"
#include "../include/Margen.hpp"
#include "../include/Punto.hpp"
#include "../include/Puntaje.hpp"
#include "../include/Vida.hpp"
#include "../include/VidaExtra.hpp"
#include "../include/EscudoItem.hpp"
#include <vector>
#include "../include/Asteroide.hpp"
#include <cmath> // Nueva inclusión para std::sin
#include "../include/TablaDePuntaje.hpp"

// Prototipo de la función de selección de armamento
int seleccionarArmamento(sf::RenderWindow& window, sf::Font& font);

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
    // Cargar la imagen de portada
    sf::Texture portadaTexture;
    if (!portadaTexture.loadFromFile("assets/images/Portada.jpg")) {
        std::cerr << "No se pudo cargar la portada.\n";
        return;
    }
    sf::Sprite portadaSprite(portadaTexture);
    float scaleX = window.getSize().x / portadaSprite.getLocalBounds().width;
    float scaleY = window.getSize().y / portadaSprite.getLocalBounds().height;
    portadaSprite.setScale(scaleX, scaleY);

    // Cargar la imagen del título
    sf::Texture tituloTexture;
    if (!tituloTexture.loadFromFile("assets/images/Titulo.png")) {
        std::cerr << "No se pudo cargar la imagen del título: assets/images/Titulo.png\n";
        // Si falla, simplemente no se muestra el título
    }
    sf::Sprite tituloSprite(tituloTexture);
    // Escalar el título para que sea visible y centrado
    float tituloScale = std::min(window.getSize().x / tituloSprite.getLocalBounds().width * 0.7f,
                                 window.getSize().y / tituloSprite.getLocalBounds().height * 0.25f);
    tituloSprite.setScale(tituloScale, tituloScale);
    tituloSprite.setOrigin(tituloSprite.getLocalBounds().width / 2, tituloSprite.getLocalBounds().height / 2);
    tituloSprite.setPosition(window.getSize().x / 2.f, 200);

    // --- Botón visual de PLAY en el menú principal ---
    sf::Font fontPlay;
    fontPlay.loadFromFile("assets/arial.ttf");
    sf::Text playText("PRESIONA ENTER PARA JUGAR", fontPlay, 60);
    playText.setFillColor(sf::Color(200, 200, 255));
    playText.setOutlineColor(sf::Color::Black);
    playText.setOutlineThickness(4.f);
    sf::FloatRect playBounds = playText.getLocalBounds();
    playText.setOrigin(playBounds.width / 2, playBounds.height / 2);
    playText.setPosition(window.getSize().x / 2.f, window.getSize().y - 180);

    sf::Clock animClock;
    float animSpeed = 2.5f;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter)
                return; // Sale al presionar ENTER
        }
        // Animación: solo escala del sprite del título, sin cambio de color
        float t = animClock.getElapsedTime().asSeconds();
        float scale = 1.0f + 0.08f * std::sin(t * animSpeed);
        tituloSprite.setScale(tituloScale * scale, tituloScale * scale);
        tituloSprite.setColor(sf::Color::White); // Sin animación de color
        // Mantener centrado
        tituloSprite.setOrigin(tituloSprite.getLocalBounds().width / 2, tituloSprite.getLocalBounds().height / 2);
        tituloSprite.setPosition(window.getSize().x / 2.f, 200);

        window.clear();
        window.draw(portadaSprite);
        window.draw(tituloSprite);
        window.draw(playText); // Dibuja el botón visual de PLAY
        window.display();
    }
}

// Nueva función para seleccionar nave
int seleccionarNave(sf::RenderWindow& window, sf::Font& font) {
    sf::Texture tex1, tex2;
    tex1.loadFromFile("assets/images/AstroNave_pixil.png");
    tex2.loadFromFile("assets/images/nave.png");
    sf::Sprite nave1(tex1), nave2(tex2);
    nave1.setScale(2,2); nave2.setScale(2,2);
    nave1.setPosition(window.getSize().x/2.f-200, window.getSize().y/2.f);
    nave2.setPosition(window.getSize().x/2.f+100, window.getSize().y/2.f);
    int seleccion = 0; // 0 = AstroNave, 1 = nave normal
    bool elegido = false;
    sf::Text txt("Elige tu nave: ← → ENTER", font, 48);
    txt.setFillColor(sf::Color::Yellow);
    txt.setOutlineColor(sf::Color::Black);
    txt.setOutlineThickness(3.f);
    sf::FloatRect txtBounds = txt.getLocalBounds();
    txt.setOrigin(txtBounds.width / 2, txtBounds.height / 2);
    txt.setPosition(window.getSize().x/2.f, window.getSize().y/2.f-180);

    // Cargar fuente Morally Serif para la leyenda
    sf::Font fontMorallySerif;
    fontMorallySerif.loadFromFile("assets/fonts/Morally Serif.otf");
    sf::Text leyenda("Favor de seleccionar su nave", fontMorallySerif, 44);
    leyenda.setFillColor(sf::Color(80, 160, 255)); // Azul
    leyenda.setOutlineColor(sf::Color::Black);
    leyenda.setOutlineThickness(4.f);
    leyenda.setStyle(sf::Text::Bold);
    sf::FloatRect leyendaBounds = leyenda.getLocalBounds();
    leyenda.setOrigin(leyendaBounds.width / 2, leyendaBounds.height / 2);
    leyenda.setPosition(window.getSize().x / 2.f, window.getSize().y / 2.f - 220);

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
        window.draw(leyenda);
        window.draw(txt);
        if(seleccion==0) nave1.setColor(sf::Color::Yellow), nave2.setColor(sf::Color::White);
        else nave1.setColor(sf::Color::White), nave2.setColor(sf::Color::Yellow);
        window.draw(nave1); window.draw(nave2);
        window.display();
    }
    return seleccion;
}

// Nueva función para pedir el nombre al usuario
std::string pedirNombre(sf::RenderWindow& window, sf::Font& font) {
    std::string nombre;
    sf::Text texto("Ingresa tu nombre:", font, 48);
    texto.setFillColor(sf::Color::Yellow);
    texto.setOutlineColor(sf::Color::Black);
    texto.setOutlineThickness(4.f);
    texto.setStyle(sf::Text::Bold);
    texto.setPosition(window.getSize().x / 2.f, window.getSize().y / 2.f - 100);
    sf::FloatRect textoBounds = texto.getLocalBounds();
    texto.setOrigin(textoBounds.width / 2, textoBounds.height / 2);

    sf::Font inputFont;
    if (!inputFont.loadFromFile("assets/fonts/Morally Serif.otf")) {
        inputFont = font;
    }
    // Leyenda centrada y bonita arriba del recuadro
    sf::Text leyenda("Favor de Escribir tu nombre", inputFont, 36);
    leyenda.setFillColor(sf::Color::Yellow);
    leyenda.setOutlineColor(sf::Color::Black);
    leyenda.setOutlineThickness(3.f);
    leyenda.setStyle(sf::Text::Bold | sf::Text::Italic);
    sf::FloatRect leyendaBounds = leyenda.getLocalBounds();
    leyenda.setOrigin(leyendaBounds.width / 2, leyendaBounds.height / 2);
    leyenda.setPosition(window.getSize().x / 2.f, window.getSize().y / 2.f - 40);

    sf::Text textoNombre("", inputFont, 36);
    textoNombre.setFillColor(sf::Color::Yellow);
    textoNombre.setPosition(window.getSize().x / 2.f - 190, window.getSize().y / 2.f + 5);

    sf::RectangleShape inputBox;
    inputBox.setSize(sf::Vector2f(400, 50));
    inputBox.setFillColor(sf::Color(255, 255, 255, 60)); // Blanco translúcido
    inputBox.setOutlineColor(sf::Color::Yellow);
    inputBox.setOutlineThickness(2);
    inputBox.setPosition(window.getSize().x / 2.f - 200, window.getSize().y / 2.f);

    sf::Clock cursorClock;
    bool cursorVisible = true;

    // Cargar textura de fondo
    sf::Texture fondoTexture;
    fondoTexture.loadFromFile("assets/images/Fondo.png");
    sf::Sprite fondoSprite(fondoTexture);
    // Ajustar el fondo al tamaño de la ventana
    float scaleX = window.getSize().x / static_cast<float>(fondoTexture.getSize().x);
    float scaleY = window.getSize().y / static_cast<float>(fondoTexture.getSize().y);
    fondoSprite.setScale(scaleX, scaleY);

    // Texto grande tipo pantalla de inicio
    sf::Text tituloNombre("ESCRIBE TU NOMBRE", font, 72);
    tituloNombre.setFillColor(sf::Color(200, 200, 255));
    tituloNombre.setOutlineColor(sf::Color::Black);
    tituloNombre.setOutlineThickness(8.f);
    tituloNombre.setStyle(sf::Text::Bold);
    sf::FloatRect tituloBounds = tituloNombre.getLocalBounds();
    tituloNombre.setOrigin(tituloBounds.width / 2, tituloBounds.height / 2);
    tituloNombre.setPosition(window.getSize().x / 2.f, window.getSize().y / 2.f - 180);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::TextEntered) {
                if (event.text.unicode == '\b') { // Backspace
                    if (!nombre.empty()) nombre.pop_back();
                } else if (event.text.unicode == '\r' || event.text.unicode == '\n') { // Enter
                    if (!nombre.empty()) return nombre;
                } else if (nombre.size() < 12 && event.text.unicode < 128 && event.text.unicode >= 32) {
                    nombre += static_cast<char>(event.text.unicode);
                }
            }
        }
        textoNombre.setString(nombre + "|"); // Muestra el cursor

        // Parpadeo del cursor
        if (cursorClock.getElapsedTime().asSeconds() >= 0.5f) {
            cursorVisible = !cursorVisible;
            cursorClock.restart();
        }
        if (!cursorVisible) {
            textoNombre.setString(nombre); // Oculta el cursor
        }

        window.clear(sf::Color::Black);
        window.draw(fondoSprite); // Dibuja el fondo
        window.draw(tituloNombre); // Dibuja el texto grande
        window.draw(leyenda);
        window.draw(inputBox); // Dibuja el recuadro antes del texto
        window.draw(textoNombre);
        window.display();
    }
}

void Ventana::mostrar() {
        // --- Variables de límites de ventana ---
        float limiteX = window.getSize().x;
        float limiteY = window.getSize().y;
        // Escudo item (invulnerabilidad)
        EscudoItem escudoItem(0, 0); // Se inicializa con valores dummy
        sf::Clock relojEscudoItem;
        bool escudoItemActivo = false;
        bool invulnerable = false;
        sf::Clock relojInvulnerable;
        float duracionInvulnerable = 5.0f;
        // Inicializar posición real de escudoItem después de definir limiteX
        escudoItem.Reiniciar(limiteX);
    // --- Fondo ---
    sf::Texture fondoTexture;
    if (!fondoTexture.loadFromFile("assets/images/Fondo2.png")) {
        std::cerr << "No se pudo cargar el fondo: assets/images/Fondo2.png" << std::endl;
    }
    sf::Sprite fondoSprite(fondoTexture);
    // Escalar el fondo para que cubra toda la ventana
    float scaleX = window.getSize().x / fondoSprite.getLocalBounds().width;
    float scaleY = window.getSize().y / fondoSprite.getLocalBounds().height;
    fondoSprite.setScale(scaleX, scaleY);

    // --- Selección de nave ---
    // Cargar la fuente una sola vez antes de cualquier bucle y mostrar error solo una vez
    static sf::Font fontGlobal;
    static bool fuenteCargada = fontGlobal.loadFromFile("assets/arial.ttf");
    static bool fuenteErrorMostrado = false;
    if (!fuenteCargada && !fuenteErrorMostrado) {
        std::cerr << "Failed to load font \"assets/arial.ttf\"" << std::endl;
        fuenteErrorMostrado = true;
    }
    // Pedir nombre antes de elegir nave
    std::string nombreJugador = pedirNombre(window, fontGlobal);
    // Menú de nave con título
    int naveSeleccionada = seleccionarNave(window, fontGlobal);
    // Menú de armamento
    int armamentoSeleccionado = seleccionarArmamento(window, fontGlobal);
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
        int vidas = 3; // Puedes actualizar este valor según la lógica de tu juego
        vida.setVidas(vidas);

        // Incluir Oportunidad.hpp en el encabezado, no aquí
        Oportunidad oportunidad(3, 3);
        vida.setVidas(oportunidad.getVidas());

        std::vector<Asteroide> asteroides;
        int cantidadAsteroides = 5;
        float limiteX = window.getSize().x;
        float limiteY = window.getSize().y;

        sf::Clock relojAsteroides;
        int asteroidesCreados = 0;
        float tiempoEntreAsteroides = 2.5f;

        float velocidadAsteroide = 0.6f;
        int ultimoPuntajeVel = 0;

        // Vida extra
        VidaExtra vidaExtra(static_cast<float>(rand() % static_cast<int>(limiteX - 40) + 20), 0);
        sf::Clock relojVidaExtra;
        bool vidaExtraActiva = false;

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

        // --- Variables estáticas del fondo y agujero negro para todo el método
        static sf::Texture agujeroTexture;
        static bool agujeroCargado = false;
        static sf::Sprite agujeroSprite;
        static float agujeroScale = 0.3f;
        static float agujeroRot = 0.f;
        static bool agujeroVisible = true;
        static bool fondoCambiado = false;

        // --- Bucle principal del juego ---
        // --- Sonido de disparo ---
        sf::SoundBuffer bufferLaser;
        bufferLaser.loadFromFile("assets/music/Laser2.ogg");
        sf::Sound sonidoLaser;
        sonidoLaser.setBuffer(bufferLaser);

        // --- Variables para el láser ---
        sf::Clock relojLaser;
        sf::Clock relojRecargaLaser;
        bool laserActivo = false;
        float duracionLaser = 1.0f;
        float recargaLaser = 2.0f;

        while (window.isOpen() && !gameOver) {
            // Lógica de aparición de escudo cada 25 segundos
            if (!escudoItemActivo && relojEscudoItem.getElapsedTime().asSeconds() >= 25.0f) {
                escudoItem.Reiniciar(limiteX);
                escudoItemActivo = true;
                relojEscudoItem.restart();
            }
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    window.close();
            }
            window.clear(sf::Color::Black);
            window.draw(fondoSprite); // Dibuja el fondo antes de todo

            margen.Dibujar(window);
            nave.Mover(window);
            margen.Limitar(nave);

            // Disparo de misil o láser
            bool disparoActual = sf::Keyboard::isKeyPressed(sf::Keyboard::Space);
            if (armamentoSeleccionado == 0) { // Misil
                if (disparoActual && !disparoAnterior) {
                    sf::Vector2f navePos = nave.ObtenerSprite().getPosition();
                    float misilX = navePos.x;
                    float misilY = navePos.y - nave.ObtenerSprite().getGlobalBounds().height / 2;
                    misiles.emplace_back(misilX, misilY);
                    sonidoLaser.play();
                }
            } else { // Láser
                if (!laserActivo && disparoActual && relojRecargaLaser.getElapsedTime().asSeconds() >= recargaLaser) {
                    laserActivo = true;
                    relojLaser.restart();
                    sonidoLaser.play();
                }
                if (laserActivo) {
                    sf::Vector2f navePos = nave.ObtenerSprite().getPosition();
                    sf::VertexArray laser(sf::Lines, 2);
                    laser[0].position = sf::Vector2f(navePos.x, navePos.y - nave.ObtenerSprite().getGlobalBounds().height / 2);
                    laser[0].color = sf::Color::Cyan;
                    laser[1].position = sf::Vector2f(navePos.x, 0);
                    laser[1].color = sf::Color::Cyan;
                    window.draw(laser);
                    // Colisión del láser con asteroides
                    for (auto itAst = asteroides.begin(); itAst != asteroides.end(); ) {
                        sf::FloatRect bounds = itAst->sprite.getGlobalBounds();
                        float xLaser = navePos.x;
                        if (xLaser >= bounds.left && xLaser <= bounds.left + bounds.width) {
                            itAst = asteroides.erase(itAst);
                            punto.sumar(10);
                        } else {
                            ++itAst;
                        }
                    }
                    if (relojLaser.getElapsedTime().asSeconds() >= duracionLaser || !disparoActual) {
                        laserActivo = false;
                        relojRecargaLaser.restart();
                        sonidoLaser.stop();
                    }
                }
            }
            disparoAnterior = disparoActual;

            // --- COLISIONES ASTEROIDE-NAVE ---
            for (auto& ast : asteroides) {
                if (!invulnerable && ast.ColisionarConNave(nave)) {
                    oportunidad.perderVida();
                    vida.setVidas(oportunidad.getVidas());
                    ast.x = static_cast<float>(rand() % static_cast<int>(limiteX - 40) + 20);
                    ast.y = 0;
                    ast.sprite.setPosition(ast.x, ast.y);
                    if (oportunidad.sinOportunidades()) {
                        gameOver = true;
                        break;
                    }
                }
            }
            // Dibujar y mover escudo item si está activo
            if (escudoItemActivo) {
                escudoItem.Mover(limiteY, limiteX, 1.0f);
                escudoItem.Dibujar(window);
                // Colisión con nave
                if (escudoItem.Colisionar(nave)) {
                    invulnerable = true;
                    relojInvulnerable.restart();
                    escudoItemActivo = false;
                }
                if (escudoItem.ObtenerY() > limiteY) {
                    escudoItemActivo = false;
                }
            }
            // Control de duración de invulnerabilidad
            if (invulnerable && relojInvulnerable.getElapsedTime().asSeconds() >= duracionInvulnerable) {
                invulnerable = false;
            }

            // --- COLISIONES MISIL-ASTEROIDE ---
            for (auto itAst = asteroides.begin(); itAst != asteroides.end(); ) {
                bool asteroideEliminado = false;
                for (auto itMisil = misiles.begin(); itMisil != misiles.end(); ) {
                    if (itAst->ColisionarConMisil(*itMisil)) {
                        itMisil = misiles.erase(itMisil);
                        itAst = asteroides.erase(itAst);
                        asteroideEliminado = true;
                        punto.sumar(10);
                        nave.EstablecerVelocidad(nave.ObtenerVelocidad() + 0.05f);
                        velocidadAsteroide += 0.05f;
                        break;
                    } else {
                        ++itMisil;
                    }
                }
                if (!asteroideEliminado) {
                    ++itAst;
                }
            }

            // Mover y dibujar misiles
            for (auto it = misiles.begin(); it != misiles.end(); ) {
                it->Mover();
                if (it->FueraDePantalla(0)) {
                    it = misiles.erase(it);
                } else {
                    it->Dibujar(window);
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
                ast.Mover(limiteY, limiteX, velocidadAsteroide);
                ast.Dibujar(window);
            }

            // --- Agujero Negro central ---
            if (!agujeroCargado) {
                if (agujeroTexture.loadFromFile("assets/images/Agujero_Negro.png")) {
                    agujeroSprite.setTexture(agujeroTexture);
                    agujeroSprite.setOrigin(agujeroTexture.getSize().x/2, agujeroTexture.getSize().y/2);
                    agujeroCargado = true;
                }
            }
            // El agujero negro aparece a los 100 puntos
            if (agujeroCargado && agujeroVisible && punto.getPuntos() >= 100) {
                agujeroScale += 0.0005f;
                agujeroRot += 1.0f;
                agujeroSprite.setScale(agujeroScale, agujeroScale);
                agujeroSprite.setPosition(window.getSize().x/2.f, window.getSize().y/2.f);
                agujeroSprite.setRotation(agujeroRot);
                window.draw(agujeroSprite);
                // Detectar colisión SOLO con el centro del agujero
                sf::Vector2f naveCentro = nave.ObtenerSprite().getPosition();
                sf::Vector2f agujeroCentro = agujeroSprite.getPosition();
                float distancia = std::sqrt(std::pow(naveCentro.x - agujeroCentro.x, 2) + std::pow(naveCentro.y - agujeroCentro.y, 2));
                float radioColision = agujeroSprite.getGlobalBounds().width * 0.15f; // Solo el centro
                if (distancia < radioColision) {
                    if (!fondoCambiado) {
                        if (fondoTexture.loadFromFile("assets/images/Portada.jpg")) {
                            fondoSprite.setTexture(fondoTexture);
                            float scaleX = window.getSize().x / fondoSprite.getLocalBounds().width;
                            float scaleY = window.getSize().y / fondoSprite.getLocalBounds().height;
                            float scale = std::max(scaleX, scaleY); // Escalado tipo 'cover'
                            fondoSprite.setScale(scale, scale);
                            fondoSprite.setOrigin(fondoSprite.getLocalBounds().width / 2, fondoSprite.getLocalBounds().height / 2);
                            fondoSprite.setPosition(window.getSize().x / 2.f, window.getSize().y / 2.f);
                        }
                        fondoCambiado = true;
                        agujeroVisible = false;
                    }
                }
            }
            // --- EFECTO DE ATRACCIÓN DEL AGUJERO NEGRO ---
            if (agujeroCargado && agujeroVisible && punto.getPuntos() >= 100) {
                sf::Vector2f agujeroCentro = agujeroSprite.getPosition();
                float escalaAgujero = agujeroScale; // Entre 0.3 y lo que crezca
                float factorFuerza = std::max(1.0f, escalaAgujero * 2.5f); // Aumenta con el tamaño
                // Atracción para asteroides
                for (auto it = asteroides.begin(); it != asteroides.end(); ) {
                    sf::Vector2f astPos = it->sprite.getPosition();
                    sf::Vector2f dir = agujeroCentro - astPos;
                    float dist = std::sqrt(dir.x * dir.x + dir.y * dir.y);
                    if (dist > 1.f) {
                        dir /= dist; // Normaliza
                        float fuerza = 0.15f * std::min(300.f, dist) / 300.f * factorFuerza;
                        it->sprite.move(dir * fuerza);
                        it->x = it->sprite.getPosition().x;
                        it->y = it->sprite.getPosition().y;
                    }
                    // Eliminar si colisiona con el centro
                    float radioColision = agujeroSprite.getGlobalBounds().width * 0.15f;
                    if (dist < radioColision) {
                        it = asteroides.erase(it);
                    } else {
                        ++it;
                    }
                }
                // Atracción para la nave
                sf::Vector2f navePos = nave.ObtenerSprite().getPosition();
                sf::Vector2f dirNave = agujeroCentro - navePos;
                float distNave = std::sqrt(dirNave.x * dirNave.x + dirNave.y * dirNave.y);
                if (distNave > 1.f) {
                    dirNave /= distNave;
                    float fuerzaNave = 0.10f * std::min(300.f, distNave) / 300.f * factorFuerza;
                    nave.ObtenerSprite().move(dirNave * fuerzaNave);
                }
                // Si la nave colisiona con el centro, puedes poner gameOver o efecto
                float radioColisionNave = agujeroSprite.getGlobalBounds().width * 0.15f;
                if (distNave < radioColisionNave) {
                    // Por ahora, solo la atrae, pero puedes poner lógica de game over aquí si quieres
                }
                // Atracción para el escudo
                if (escudoItemActivo) {
                    sf::Vector2f escudoPos(escudoItem.ObtenerX(), escudoItem.ObtenerY());
                    sf::Vector2f dirEscudo = agujeroCentro - escudoPos;
                    float distEscudo = std::sqrt(dirEscudo.x * dirEscudo.x + dirEscudo.y * dirEscudo.y);
                    if (distEscudo > 1.f) {
                        dirEscudo /= distEscudo;
                        float fuerzaEscudo = 0.12f * std::min(300.f, distEscudo) / 300.f * factorFuerza;
                        escudoItem.EstablecerPos(escudoPos.x + dirEscudo.x * fuerzaEscudo, escudoPos.y + dirEscudo.y * fuerzaEscudo);
                    }
                    float radioColisionEscudo = agujeroSprite.getGlobalBounds().width * 0.15f;
                    if (distEscudo < radioColisionEscudo) {
                        escudoItemActivo = false;
                    }
                }
                // Atracción para la vida extra
                if (vidaExtraActiva) {
                    sf::Vector2f vidaPos(vidaExtra.getX(), vidaExtra.getY());
                    sf::Vector2f dirVida = agujeroCentro - vidaPos;
                    float distVida = std::sqrt(dirVida.x * dirVida.x + dirVida.y * dirVida.y);
                    if (distVida > 1.f) {
                        dirVida /= distVida;
                        float fuerzaVida = 0.12f * std::min(300.f, distVida) / 300.f * factorFuerza;
                        vidaExtra.setPos(vidaPos.x + dirVida.x * fuerzaVida, vidaPos.y + dirVida.y * fuerzaVida);
                    }
                    float radioColisionVida = agujeroSprite.getGlobalBounds().width * 0.15f;
                    if (distVida < radioColisionVida) {
                        vidaExtraActiva = false;
                    }
                }
            }

            // Dibuja la nave después del agujero negro para que quede encima
            nave.Dibujar(window);

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
            sf::Font fontMorallySerif;
            if (fontMorallySerif.loadFromFile("assets/fonts/Morally Serif.otf")) {
                sf::Text textoPuntos;
                textoPuntos.setFont(fontMorallySerif);
                textoPuntos.setString("Puntos: " + std::to_string(punto.getPuntos()));
                textoPuntos.setCharacterSize(36);
                textoPuntos.setFillColor(sf::Color::White);
                // Posicionar en la esquina superior derecha
                float textWidth = textoPuntos.getLocalBounds().width;
                textoPuntos.setPosition(window.getSize().x - textWidth - 40, 20);
                window.draw(textoPuntos);
            } else {
                // Si falla la fuente, mostrar con Arial como respaldo
                if (fuenteCargada) {
                    sf::Text textoPuntos;
                    textoPuntos.setFont(fontPuntos);
                    textoPuntos.setString("Puntos: " + std::to_string(punto.getPuntos()));
                    textoPuntos.setCharacterSize(32);
                    textoPuntos.setFillColor(sf::Color::White);
                    textoPuntos.setPosition(20, 20);
                    window.draw(textoPuntos);
                }
            }

            vida.draw(window);
            // Mostrar oportunidades restantes
            sf::Font fontOpor;
            if (fontOpor.loadFromFile("assets/arial.ttf")) {
                sf::Text textoOpor;
                textoOpor.setFont(fontOpor);
                textoOpor.setString("Oportunidades: " + std::to_string(oportunidad.getOportunidades()));
                textoOpor.setCharacterSize(28);
                textoOpor.setFillColor(sf::Color::White);
                textoOpor.setPosition(20, 80);
                window.draw(textoOpor);
            }
            puntaje.setPuntos(punto.getPuntos());
            puntaje.draw(window);

            // Lógica de aparición de vida extra cada 20 segundos
            if (!vidaExtraActiva && relojVidaExtra.getElapsedTime().asSeconds() >= 20.0f) {
                vidaExtra.Reiniciar(limiteX);
                vidaExtraActiva = true;
                relojVidaExtra.restart();
            }

            // Dibujar y mover vida extra si está activa
            if (vidaExtraActiva) {
                vidaExtra.mover(limiteY, limiteX, 1.0f);
                vidaExtra.dibujar(window);
                // Colisión con nave
                if (vidaExtra.colision(nave)) {
                    oportunidad.sumarVida(); // Suma solo una vida
                    vida.setVidas(oportunidad.getVidas());
                    vidaExtraActiva = false;
                }
                if (vidaExtra.getY() > limiteY) {
                    vidaExtraActiva = false;
                }
            }

            window.display();
        }

        // --- Mostrar pantalla de Game Over ---
        if (window.isOpen()) {
            // Guardar puntaje
            TablaDePuntaje tabla("mejores_puntajes.txt");
            std::string nombre = nombreJugador.empty() ? "JUGADOR" : nombreJugador;
            tabla.agregar(nombre, punto.getPuntos());

            // Mostrar tabla de mejores puntajes
            sf::Font fontTabla;
            fontTabla.loadFromFile("assets/fonts/Morally Serif.otf");
            std::string tablaStr = "MEJORES PUNTAJES\n";
            int pos = 1;
            for (const auto& entrada : tabla.obtener()) {
                tablaStr += std::to_string(pos++) + ". " + entrada.nombre + ": " + std::to_string(entrada.puntaje) + "\n";
            }
            sf::Text textoTabla(tablaStr, fontTabla, 36);
            textoTabla.setFillColor(sf::Color::White);
            textoTabla.setStyle(sf::Text::Bold);
            sf::FloatRect bounds = textoTabla.getLocalBounds();
            textoTabla.setOrigin(bounds.width / 2, bounds.height / 2);
            textoTabla.setPosition(window.getSize().x / 2.f, window.getSize().y / 2.f + 120);

            sf::Font fontFin;
            fontFin.loadFromFile("assets/arial.ttf");
            sf::Text textoFin;
            textoFin.setFont(fontFin);
            textoFin.setString("Juego terminado\nPuntaje: " + std::to_string(punto.getPuntos()) + "\nPresiona ESPACIO para volver a jugar");
            textoFin.setCharacterSize(40);
            textoFin.setFillColor(sf::Color::White);
            textoFin.setStyle(sf::Text::Bold);
            sf::FloatRect boundsFin = textoFin.getLocalBounds();
            textoFin.setOrigin(boundsFin.width / 2, boundsFin.height / 2);
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
                window.draw(textoTabla);
                window.display();
            }
        }
        // Si la ventana se cerró, salimos del bucle
        break;
reiniciar_juego:
        // Reiniciar variables estáticas de fondo y agujero negro
        if (fondoTexture.loadFromFile("assets/images/Fondo2.png")) {
            fondoSprite.setTexture(fondoTexture);
            float scaleX = window.getSize().x / fondoSprite.getLocalBounds().width;
            float scaleY = window.getSize().y / fondoSprite.getLocalBounds().height;
            fondoSprite.setScale(scaleX, scaleY);
        }
        fondoCambiado = false;
        agujeroVisible = true;
        agujeroScale = 0.3f;
        agujeroRot = 0.f;
        continue;
    }
}

// Prototipo de la función de selección de armamento
int seleccionarArmamento(sf::RenderWindow& window, sf::Font& font) {
    // Cargar fuente Morally Serif para la leyenda
    sf::Font fontMorallySerif;
    fontMorallySerif.loadFromFile("assets/fonts/Morally Serif.otf");
    sf::Text leyenda("Favor de seleccionar su armamento", fontMorallySerif, 44);
    leyenda.setFillColor(sf::Color(80, 160, 255)); // Azul
    leyenda.setOutlineColor(sf::Color::Black);
    leyenda.setOutlineThickness(4.f);
    leyenda.setStyle(sf::Text::Bold);
    sf::FloatRect leyendaBounds = leyenda.getLocalBounds();
    leyenda.setOrigin(leyendaBounds.width / 2, leyendaBounds.height / 2);
    leyenda.setPosition(window.getSize().x / 2.f, window.getSize().y / 2.f - 220);

    // Cargar imágenes de misiles
    sf::Texture texMisil, texLaser;
    texMisil.loadFromFile("assets/images/Disparo.png");
    texLaser.loadFromFile("assets/images/Disparo.png"); // Usa la misma imagen, puedes cambiarla si tienes otra
    sf::Sprite misil1(texMisil), misil2(texLaser);
    misil1.setScale(3, 3);
    misil2.setScale(3, 3);
    misil1.setPosition(window.getSize().x/2.f-200, window.getSize().y/2.f);
    misil2.setPosition(window.getSize().x/2.f+100, window.getSize().y/2.f);

    int seleccion = 0; // 0 = Misil, 1 = Laser
    bool elegido = false;
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
        misil1.setColor(seleccion==0 ? sf::Color::Green : sf::Color::White);
        misil2.setColor(seleccion==1 ? sf::Color::Green : sf::Color::White);
        window.clear(sf::Color::Black);
        window.draw(leyenda);
        window.draw(misil1); window.draw(misil2);
        window.display();
    }
    return seleccion;
}