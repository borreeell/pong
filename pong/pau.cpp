#include <iostream> // Entrada i sortida
#include <cmath> // Funcions matemàtiques
#include <cstdlib> // Funcions aleatòries

#include "pau.h" // Inclou capçalera

using namespace std; // Espai de noms

const int AMPLADA_FINESTRA = 800; // Amplada de pantalla
const int ALCADA_FINESTRA = 600; // Alçada de pantalla
const float RADI_PILOTA = 8.0f; // Radi del cercle
const float VELOCITAT_PILOTA = 300.0f; // Velocitat base pilota

void inicialitzarPilota(Pilota& pilota) // Configura inici pilota
{ 
    pilota.x = AMPLADA_FINESTRA / 2.0f; // Centre horitzontal
    pilota.y = ALCADA_FINESTRA / 2.0f; // Centre vertical
    pilota.radi = RADI_PILOTA; // Defineix radi

    float angle = (rand() % 60 - 30) * 3.14159f / 180.0f; // Angle aleatori
    int direccio = (rand() % 2) * 2 - 1; // Direcció inicial

    pilota.velocitatX = direccio * VELOCITAT_PILOTA * cos(angle); // Velocitat horitzontal
    pilota.velocitatY = VELOCITAT_PILOTA * sin(angle); // Velocitat vertical
}

void actualitzarPilota(Pilota& pilota, float tempsTranscorregut) // Actualitza moviment
{ 
    pilota.x += pilota.velocitatX * tempsTranscorregut; // Mou horitzontalment
    pilota.y += pilota.velocitatY * tempsTranscorregut; // Mou verticalment

    if (pilota.y - pilota.radi <= 0 || pilota.y + pilota.radi >= ALCADA_FINESTRA) // Rebota dalt/baix
    {
        pilota.velocitatY = -pilota.velocitatY; // Inverteix sentit vertical
    }
}

bool comprovarCollisioPala(const Pilota& pilota, const Pala& pala) // Detecta xoc
{
    return pilota.x - pilota.radi < pala.x + pala.amplada && // Límit dret pala
           pilota.x + pilota.radi > pala.x && // Límit esquerre pala
           pilota.y + pilota.radi > pala.y && // Límit superior pala
           pilota.y - pilota.radi < pala.y + pala.alcada; // Límit inferior pala
}

void gestionarCollisions(Pilota& pilota, const Pala& palaEsquerra, const Pala& palaDreta) // Gestiona rebots
{
    if (comprovarCollisioPala(pilota, palaEsquerra)) // Xoc pala esquerra
    { 
        if (pilota.velocitatX < 0) // Si va esquerra
        { 
            pilota.velocitatX = -pilota.velocitatX * 1.05f; // Rebota i accelera
            float posicioRelativa = (pilota.y - (palaEsquerra.y + palaEsquerra.alcada / 2)) / (palaEsquerra.alcada / 2); // Calcula angle
            pilota.velocitatY += posicioRelativa * 200.0f; // Modifica vertical
        }
    }

    if (comprovarCollisioPala(pilota, palaDreta)) // Xoc pala dreta
    { 
        if (pilota.velocitatX > 0) // Si va dreta
        { 
            pilota.velocitatX = -pilota.velocitatX * 1.05f; // Rebota i accelera
            float posicioRelativa = (pilota.y - (palaDreta.y + palaDreta.alcada / 2)) / (palaDreta.alcada / 2); // Calcula angle
            pilota.velocitatY += posicioRelativa * 200.0f; // Modifica vertical
        }
    }
}

bool comprovarPuntuacio(const Pilota& pilota, Pala& palaEsquerra, Pala& palaDreta) // Comprova gols
{ 
    if (pilota.x < 0) // Surt per l'esquerra
    { 
        palaEsquerra.puntuacio++; // Punt per dreta
        std::cout << "La pala dreta ha marcat" << endl; // Missatge consola
        return true; // Gol marcat
    }
    if (pilota.x > AMPLADA_FINESTRA) // Surt per dreta
    { 
        palaDreta.puntuacio++; // Punt per esquerra
        std::cout << "La pala esquerra ha marcat" << endl; // Missatge consola
        return true; // Gol marcat
    }
    return false; // No hi ha gol
}

void dibuixarPilota(sf::RenderWindow& finestra, const Pilota& pilota) // Dibuixa pilota
{ 
    sf::CircleShape forma(pilota.radi); // Crea cercle
    forma.setPosition({ pilota.x - pilota.radi, pilota.y - pilota.radi }); // Posa posició
    forma.setFillColor(sf::Color::White); // Color blanc
    finestra.draw(forma); // Renderitza cercle
}
