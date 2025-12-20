#pragma once 

#include <SFML/Graphics.hpp> // Llibreria gràfica

// Estructura per a les pales
struct Pala // Defineix pala
{ 
    float x, y; // Posició actual
    float amplada, alcada; // Mides pala
    int puntuacio; // Punts jugador
};

// INICIAR LA PALA
void inicialitzarPala(Pala& pala, float x, float y); // Valors inicials

// MOURE PALA JUGADOR
void mourePala(Pala& pala, float tempsTranscorregut, bool amunt, bool avall); // Moviment jugador

// MOURE PALA AMB RANDOM
void moureIA(Pala& pala, float pilotaX, float pilotaY, float tempsTranscorregut); // Moviment IA

// DIBUIX DE LA PALA
void dibuixarPala(sf::RenderWindow& finestra, const Pala& pala); // Renderitza pala
