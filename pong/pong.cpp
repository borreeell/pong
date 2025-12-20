#include <iostream> // Entrada i sortida
#include <cstdlib> // Utilitats estàndard
#include <ctime> // Control de temps
#include <string> // Gestió de textos

#include <SFML/Graphics.hpp> // Motor gràfic SFML

#include "pablo.h" // Capçalera pales
#include "pau.h" // Capçalera pilota

using namespace std; // Estil estàndard
using namespace sf; // Estil SFML

// Constants del joc
const int AMPLADA_FINESTRA = 800; // Ample pantalla
const int ALCADA_FINESTRA = 600; // Alt pantalla
const float AMPLADA_PALA = 15.0f; // Ample rectangle
const float ALCADA_PALA = 100.0f; // Alt rectangle

void dibuixarLiniaCentral(RenderWindow& finestra) // Dibuixa camp
{ 
    for (int i = 0; i < ALCADA_FINESTRA; i += 20) // Bucle línies
    { 
        RectangleShape linia(Vector2f(2, 10)); // Crea segment
        linia.setPosition({ AMPLADA_FINESTRA / 2.0f, static_cast<float>(i) }); // Centra segment
        linia.setFillColor(Color(100, 100, 100)); // Color gris
        finestra.draw(linia); // Renderitza segment
    }
}

void dibuixarPuntuacio(RenderWindow& finestra, const Pala& palaEsquerra, const Pala& palaDreta, Font& font) // Mostra marcadors
{ 
    Text puntuacioEsquerra(font); // Text esquerre
    puntuacioEsquerra.setString(std::to_string(palaEsquerra.puntuacio)); // Text a string
    puntuacioEsquerra.setCharacterSize(50); // Mida lletra
    puntuacioEsquerra.setFillColor(sf::Color::White); // Color blanc
    puntuacioEsquerra.setPosition({ AMPLADA_FINESTRA / 4.0f, 20 }); // Posició esquerra

    Text puntuacioDreta(font); // Text dret
    puntuacioDreta.setFont(font); // Assigna font
    puntuacioDreta.setString(std::to_string(palaDreta.puntuacio)); // Valor marcador
    puntuacioDreta.setCharacterSize(50); // Mida lletra
    puntuacioDreta.setFillColor(sf::Color::White); // Color blanc
    puntuacioDreta.setPosition({ 3 * AMPLADA_FINESTRA / 4.0f, 20 }); // Posició dreta

    finestra.draw(puntuacioEsquerra); // Dibuixa esquerre
    finestra.draw(puntuacioDreta); // Dibuixa dret
}

int main() // Funció principal
{ 
    srand(static_cast<unsigned>(time(0))); // Llavor aleatòria

    VideoMode vm({ 800, 600 }); // Mode vídeo
    RenderWindow window(vm, "Pong"); // Crea finestra

    Font font("KOMIKAP_.ttf"); // Carrega tipografia

    Pala palaEsquerra, palaDreta; // Declara pales
    Pilota pilota; // Declara pilota

    inicialitzarPala(palaEsquerra, 30, ALCADA_FINESTRA / 2 - ALCADA_PALA / 2); // Inicia esquerra
    inicialitzarPala(palaDreta, AMPLADA_FINESTRA - 30 - AMPLADA_PALA, ALCADA_FINESTRA / 2 - ALCADA_PALA / 2); // Inicia dreta
    inicialitzarPilota(pilota); // Inicia pilota

    Clock rellotge; // Control fotogrames

    bool amuntPremut = false; // Estat tecla W
    bool avallPremut = false; // Estat tecla S

    while (window.isOpen()) // Bucle joc
    { 
        float tempsTranscorregut = rellotge.restart().asSeconds(); // Delta time

        while (const optional event = window.pollEvent()) { // Gestió events
            if (event->is<Event::Closed>()) window.close(); // Tanca finestra

            if (const auto* key = event->getIf<Event::KeyPressed>()) // Tecla premuda
            {
                if (key->scancode == Keyboard::Scancode::W) amuntPremut = true; // Activa amunt
                if (key->scancode == Keyboard::Scancode::S) avallPremut = true; // Activa avall
            }

            if (const auto* key = event->getIf<Event::KeyReleased>()) // Tecla soltada
            { 
                if (key->scancode == Keyboard::Scancode::W) amuntPremut = false; // Atura amunt
                if (key->scancode == Keyboard::Scancode::S) avallPremut = false; // Atura avall
            }
        }

        mourePala(palaEsquerra, tempsTranscorregut, amuntPremut, avallPremut); // Actualitza jugador
        moureIA(palaDreta, pilota.x, pilota.y, tempsTranscorregut); // Actualitza IA
        actualitzarPilota(pilota, tempsTranscorregut); // Actualitza pilota
        gestionarCollisions(pilota, palaEsquerra, palaDreta); // Comprova xocs

        if (comprovarPuntuacio(pilota, palaEsquerra, palaDreta)) // Si gol
        {
            inicialitzarPilota(pilota); // Reinicia pilota
        }

        window.clear(Color::Black); // Neteja fons
        dibuixarLiniaCentral(window); // Dibuixa camp
        dibuixarPala(window, palaEsquerra); // Dibuixa esquerra
        dibuixarPala(window, palaDreta); // Dibuixa dreta
        dibuixarPilota(window, pilota); // Dibuixa pilota
        dibuixarPuntuacio(window, palaDreta, palaEsquerra, font); // Dibuixa punts

        window.display(); // Mostra canvis
    }

    return 0; // Finalitza programa
}
