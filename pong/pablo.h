#pragma once // Evita duplicats

#include <SFML/Graphics.hpp> // Llibreria gràfica

// Estructura per a les pales
struct Pala { // Defineix pala
    float x, y; // Posició actual
    float amplada, alcada; // Mides pala
    int puntuacio; // Punts jugador
};

// Inicialitzar la pala
void inicialitzarPala(Pala& pala, float x, float y); // Valors inicials

// Moure la pala del jugador
void mourePala(Pala& pala, float tempsTranscorregut, bool amunt, bool avall); // Moviment jugador

// IA simple per a la pala de l'ordinador
void moureIA(Pala& pala, float pilotaX, float pilotaY, float tempsTranscorregut); // Moviment IA

// Dibuixar la pala
void dibuixarPala(sf::RenderWindow& finestra, const Pala& pala); // Renderitza pala
