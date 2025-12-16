#include <iostream>
#include <cmath>
#include <cstdlib>

#include "pau.h"

using namespace std;

const int AMPLADA_FINESTRA = 800;
const int ALCADA_FINESTRA = 600;
const float RADI_PILOTA = 8.0f;
const float VELOCITAT_PILOTA = 300.0f;

void inicialitzarPilota(Pilota& pilota) {
    pilota.x = AMPLADA_FINESTRA / 2.0f;
    pilota.y = ALCADA_FINESTRA / 2.0f;
    pilota.radi = RADI_PILOTA;

    // Direcció aleatòria inicial
    float angle = (rand() % 60 - 30) * 3.14159f / 180.0f;
    int direccio = (rand() % 2) * 2 - 1; // -1 o 1

    pilota.velocitatX = direccio * VELOCITAT_PILOTA * cos(angle);
    pilota.velocitatY = VELOCITAT_PILOTA * sin(angle);
}

void actualitzarPilota(Pilota& pilota, float tempsTranscorregut) {
    pilota.x += pilota.velocitatX * tempsTranscorregut;
    pilota.y += pilota.velocitatY * tempsTranscorregut;

    // Rebot amb les parets superior i inferior
    if (pilota.y - pilota.radi <= 0 || pilota.y + pilota.radi >= ALCADA_FINESTRA) {
        pilota.velocitatY = -pilota.velocitatY;
    }
}

// Comprovar col·lisió amb les pales
bool comprovarCollisioPala(const Pilota& pilota, const Pala& pala) {
    return pilota.x - pilota.radi < pala.x + pala.amplada &&
        pilota.x + pilota.radi > pala.x &&
        pilota.y + pilota.radi > pala.y &&
        pilota.y - pilota.radi < pala.y + pala.alcada;
}

void gestionarCollisions(Pilota& pilota, const Pala& palaEsquerra, const Pala& palaDreta) {
    if (comprovarCollisioPala(pilota, palaEsquerra)) {
        if (pilota.velocitatX < 0) {
            pilota.velocitatX = -pilota.velocitatX * 1.05f; // Augmentar velocitat
            float posicioRelativa = (pilota.y - (palaEsquerra.y + palaEsquerra.alcada / 2)) / (palaEsquerra.alcada / 2);
            pilota.velocitatY += posicioRelativa * 200.0f;
        }
    }

    if (comprovarCollisioPala(pilota, palaDreta)) {
        if (pilota.velocitatX > 0) {
            pilota.velocitatX = -pilota.velocitatX * 1.05f;
            float posicioRelativa = (pilota.y - (palaDreta.y + palaDreta.alcada / 2)) / (palaDreta.alcada / 2);
            pilota.velocitatY += posicioRelativa * 200.0f;
        }
    }
}

bool comprovarPuntuacio(const Pilota& pilota, Pala& palaEsquerra, Pala& palaDreta) {
    if (pilota.x < 0) {
        palaEsquerra.puntuacio++;

        std::cout << "La pala dreta ha marcat" << endl;

        return true;
    }
    if (pilota.x > AMPLADA_FINESTRA) {
        palaDreta.puntuacio++;

        std::cout << "La pala esquerra ha marcat" << endl;

        return true;
    }
    return false;
}

void dibuixarPilota(sf::RenderWindow& finestra, const Pilota& pilota) {
    sf::CircleShape forma(pilota.radi);
    forma.setPosition({ pilota.x - pilota.radi, pilota.y - pilota.radi });
    forma.setFillColor(sf::Color::White);
    finestra.draw(forma);
}