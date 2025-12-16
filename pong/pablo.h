#pragma once

#include <SFML/Graphics.hpp>

// Estructura per a les pales
struct Pala {
    float x, y;
    float amplada, alcada;
    int puntuacio;
};

// Inicialitzar la pala
void inicialitzarPala(Pala& pala, float x, float y);

// Moure la pala del jugador
void mourePala(Pala& pala, float tempsTranscorregut, bool amunt, bool avall);

// IA simple per a la pala de l'ordinador
void moureIA(Pala& pala, float pilotaX, float pilotaY, float tempsTranscorregut);

// Dibuixar la pala
void dibuixarPala(sf::RenderWindow& finestra, const Pala& pala);