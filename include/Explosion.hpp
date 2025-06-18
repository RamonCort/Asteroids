#pragma once
#include <SFML/Graphics.hpp>

class Explosion {
public:
    Explosion(float x, float y);
    void update();
    void draw(sf::RenderWindow& window);
    bool isFinished() const;

private:
    static sf::Texture texture;
    static bool textureLoaded;
    sf::Sprite sprite;
    int frameActual;
    int totalFrames;
    int framesPorFila;
    int frameWidth;
    int frameHeight;
    float tiempoPorFrame;
    sf::Clock relojAnimacion;
    bool finished;
    // Variables para frames de la segunda fila
    int anchoTotal;
    int anchoFrameFila2;
};
