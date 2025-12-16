// main.cpp
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>

#include <SFML/Graphics.hpp>

#include "pablo.h"
#include "pau.h"

using namespace std;
using namespace sf; 

const int AMPLADA_FINESTRA = 800;
const int ALCADA_FINESTRA = 600;
const float AMPLADA_PALA = 15.0f;
const float ALCADA_PALA = 100.0f;

void dibuixarLiniaCentral(RenderWindow& finestra) {
    for (int i = 0; i < ALCADA_FINESTRA; i += 20) {
        RectangleShape linia(Vector2f(2, 10));
        linia.setPosition({ AMPLADA_FINESTRA / 2.0f, static_cast<float>(i) });
        linia.setFillColor(Color(100, 100, 100));
        finestra.draw(linia);
    }
}

void dibuixarPuntuacio(RenderWindow& finestra, const Pala& palaEsquerra, const Pala& palaDreta, Font& font) {
    Text puntuacioEsquerra(font);
    puntuacioEsquerra.setString(std::to_string(palaEsquerra.puntuacio));
    puntuacioEsquerra.setCharacterSize(50);
    puntuacioEsquerra.setFillColor(sf::Color::White);
    puntuacioEsquerra.setPosition({ AMPLADA_FINESTRA / 4.0f, 20 });

    Text puntuacioDreta(font);
    puntuacioDreta.setFont(font);
    puntuacioDreta.setString(std::to_string(palaDreta.puntuacio));
    puntuacioDreta.setCharacterSize(50);
    puntuacioDreta.setFillColor(sf::Color::White);
    puntuacioDreta.setPosition({ 3 * AMPLADA_FINESTRA / 4.0f, 20 });

    finestra.draw(puntuacioEsquerra);
    finestra.draw(puntuacioDreta);
}

int main() {
    srand(static_cast<unsigned>(time(0)));

    // Crear finestra
    VideoMode vm({ 800, 600 });
    RenderWindow window(vm, "Pong");

    // Carregar font
    Font font("KOMIKAP_.ttf");

    // Inicialitzar elements del joc
    Pala palaEsquerra, palaDreta;
    Pilota pilota;

    inicialitzarPala(palaEsquerra, 30, ALCADA_FINESTRA / 2 - ALCADA_PALA / 2);
    inicialitzarPala(palaDreta, AMPLADA_FINESTRA - 30 - AMPLADA_PALA, ALCADA_FINESTRA / 2 - ALCADA_PALA / 2);
    inicialitzarPilota(pilota);

    Clock rellotge;

    // Input del jugador
    bool amuntPremut = false;
    bool avallPremut = false;

    // Bucle principal
    while (window.isOpen()) {
        float tempsTranscorregut = rellotge.restart().asSeconds();

        // Gestionar events
        while (const optional event = window.pollEvent()) {
            if (event->is<Event::Closed>()) window.close();

            if (const auto* key = event->getIf<Event::KeyPressed>()) {
                if (key->scancode == Keyboard::Scancode::W) {
                    amuntPremut = true;
                }

                if (key->scancode == Keyboard::Scancode::S) {
                    avallPremut = true;
                }
            }

            if (const auto* key = event->getIf<Event::KeyReleased>()) {
                if (key->scancode == Keyboard::Scancode::W) {
                    amuntPremut = false;
                }

                if (key->scancode == Keyboard::Scancode::S) {
                    avallPremut = false;
                }
            }
        }

        // Actualitzar
        mourePala(palaEsquerra, tempsTranscorregut, amuntPremut, avallPremut);
        moureIA(palaDreta, pilota.x, pilota.y, tempsTranscorregut);
        actualitzarPilota(pilota, tempsTranscorregut);
        gestionarCollisions(pilota, palaEsquerra, palaDreta);

        // Comprovar si s'ha marcat
        if (comprovarPuntuacio(pilota, palaEsquerra, palaDreta)) {
            inicialitzarPilota(pilota);
        }

        // Dibuixar
        window.clear(Color::Black);
        dibuixarLiniaCentral(window);
        dibuixarPala(window, palaEsquerra);
        dibuixarPala(window, palaDreta);
        dibuixarPilota(window, pilota);
        dibuixarPuntuacio(window, palaDreta, palaEsquerra, font);
 
        window.display();
    }

    return 0;
}