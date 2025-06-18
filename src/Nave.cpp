#include "../include/Nave.hpp"
#include <iostream>
#include <cmath> // Incluir cmath para std::atan2

Nave::Nave(float x, float y, const std::string& ruta) {
    if (!texture.loadFromFile(ruta)) {
        std::cerr << "No se pudo cargar la imagen: " << ruta << std::endl;
    }
    sprite.setTexture(texture);
    sf::FloatRect bounds = sprite.getLocalBounds();
    // Cambia el tamaño de la nave (por ejemplo, al doble)
    sprite.setScale(2.0f, 2.0f);
    sprite.setOrigin(bounds.width / 2, bounds.height / 2);
    sprite.setPosition(x, y);
    velocidad = 1.0f; // Ahora el doble de rápido que antes (antes 0.5f)
      // Inicializar posición anterior para el rastro
    posicionAnterior = sf::Vector2f(x, y);
    
    // Determinar si tiene rastro y su color según la nave
    if (ruta.find("AstroNave_pixil.png") != std::string::npos) {
        tieneRastro = true;
        colorRastro = sf::Color(0, 150, 255); // Azul para la nave de la izquierda
    } else if (ruta.find("nave.png") != std::string::npos) {
        tieneRastro = true;
        colorRastro = sf::Color(255, 140, 0); // Naranja para la nave de la derecha
    } else {
        tieneRastro = false;
        colorRastro = sf::Color::White; // Color por defecto
    }
}

void Nave::Mover(const sf::RenderWindow& window) {
    sf::Vector2f posicionActual = sprite.getPosition();
    sf::Vector2f movimiento(0.f, 0.f);
    
    // Movimiento con teclas de flecha
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        movimiento.x -= velocidad;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        movimiento.x += velocidad;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        movimiento.y -= velocidad;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        movimiento.y += velocidad;
    
    // Movimiento con teclas WASD
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        movimiento.x -= velocidad;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        movimiento.x += velocidad;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        movimiento.y -= velocidad;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        movimiento.y += velocidad;
    
    // Determinar si la nave se está moviendo
    seEstaMoviendo = (movimiento.x != 0.f || movimiento.y != 0.f);      // Crear partículas de rastro si se está moviendo y la nave tiene rastro
    if (seEstaMoviendo && tieneRastro) {
        // Calcular la posición trasera de la nave basada en su rotación
        float angulo = sprite.getRotation() - 90.f; // -90 porque la nave apunta hacia arriba por defecto
        float rad = angulo * 3.14159265f / 180.f;
        
        // Obtener el tamaño de la nave
        sf::FloatRect bounds = sprite.getGlobalBounds();
        float distanciaTrasera = bounds.height * 0.4f; // Distancia desde el centro hacia la parte trasera
        
        // Calcular el vector perpendicular para el ancho de la nave
        sf::Vector2f vectorPerpendicular;
        vectorPerpendicular.x = -std::sin(rad);
        vectorPerpendicular.y = std::cos(rad);
          // Crear múltiples partículas a lo ancho de la parte posterior
        int numParticulas = 5; // Ahora 5 rayos de turbo
        float anchoNave = bounds.width * 0.6f; // Ancho de la parte posterior
        
        for (int i = 0; i < numParticulas; i++) {
            // Calcular offset lateral para distribuir partículas a lo ancho
            float offset = (i - numParticulas/2.0f) * (anchoNave / numParticulas);
            
            // Calcular la posición trasera con offset lateral
            sf::Vector2f posicionTrasera;
            posicionTrasera.x = posicionActual.x - std::cos(rad) * distanciaTrasera + vectorPerpendicular.x * offset;
            posicionTrasera.y = posicionActual.y - std::sin(rad) * distanciaTrasera + vectorPerpendicular.y * offset;
            
            // Agregar nueva partícula de rastro
            particulas.emplace_back(posicionTrasera);
        }
    }
    
    sprite.move(movimiento);
    
    // Apuntar hacia el mouse
    ApuntarHaciaMouse(window);
    
    // Actualizar el rastro
    ActualizarRastro();
    
    // Actualizar posición anterior
    posicionAnterior = sprite.getPosition();
}

void Nave::ApuntarHaciaMouse(const sf::RenderWindow& window) {
    // Obtener la posición del mouse en el mundo
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    sf::Vector2f worldMousePos = window.mapPixelToCoords(mousePos);
    
    // Obtener la posición de la nave
    sf::Vector2f navePos = sprite.getPosition();
    
    // Calcular el ángulo hacia el mouse
    float dx = worldMousePos.x - navePos.x;
    float dy = worldMousePos.y - navePos.y;
    float angulo = std::atan2(dy, dx) * 180.f / 3.14159265f + 90.f;
    
    // Aplicar la rotación
    sprite.setRotation(angulo);
}

void Nave::ActualizarRastro() {
    // Actualizar vida de las partículas y eliminar las que han expirado
    for (auto it = particulas.begin(); it != particulas.end();) {
        it->vida -= 0.05f; // Velocidad de desvanecimiento
        it->alpha = static_cast<sf::Uint8>(it->vida * 255.f);
        
        if (it->vida <= 0.f) {
            it = particulas.erase(it);
        } else {
            ++it;
        }
    }
}

void Nave::DibujarRastro(sf::RenderWindow& window) {
    // Solo dibujar el rastro si la nave lo tiene habilitado
    if (!tieneRastro) return;
    
    // Dibujar cada partícula de rastro
    for (const auto& particula : particulas) {
        sf::CircleShape punto(2.f); // Tamaño pequeño para el efecto de rastro
        punto.setPosition(particula.posicion.x - 2.f, particula.posicion.y - 2.f);
        
        // Usar el color específico de la nave con transparencia que se desvanece
        sf::Color colorConAlpha = colorRastro;
        colorConAlpha.a = particula.alpha;
        punto.setFillColor(colorConAlpha);
        
        window.draw(punto);
    }
}

void Nave::Dibujar(sf::RenderWindow& window) {
    // Primero dibujar el rastro, luego la nave
    DibujarRastro(window);
    window.draw(sprite);
}

sf::Sprite& Nave::ObtenerSprite() {
    return sprite;
}
