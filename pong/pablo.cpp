#include "pablo.h" // Inclou llibreria pròpia

const float AMPLADA_PALA = 15.0f; // Amplada de pala
const float ALCADA_PALA = 100.0f; // Alçada de pala
const float VELOCITAT_PALA = 400.0f; // Velocitat de moviment
const int ALCADA_FINESTRA = 600; // Límit vertical finestra

void inicialitzarPala(Pala& pala, float x, float y) { // Funció configuració inicial
    pala.x = x; // Assigna posició horitzontal
    pala.y = y; // Assigna posició vertical
    pala.amplada = AMPLADA_PALA; // Defineix l'amplada
    pala.alcada = ALCADA_PALA; // Defineix l'alçada
    pala.puntuacio = 0; // Inicialitza el marcador
}

void mourePala(Pala& pala, float tempsTranscorregut, bool amunt, bool avall) { // Control manual pala
    if (amunt && pala.y > 0) { // Si prem amunt
        pala.y -= VELOCITAT_PALA * tempsTranscorregut; // Mou cap amunt
    }
    if (avall && pala.y + pala.alcada < ALCADA_FINESTRA) { // Si prem avall
        pala.y += VELOCITAT_PALA * tempsTranscorregut; // Mou cap avall
    }
}

void moureIA(Pala& pala, float pilotaX, float pilotaY, float tempsTranscorregut) { // Lògica intel·ligència artificial
    float centrePala = pala.y + pala.alcada / 2.0f; // Calcula centre vertical

    if (centrePala < pilotaY - 20) { // Pilota per sota
        pala.y += VELOCITAT_PALA * tempsTranscorregut * 0.7f; // Segueix cap avall
    }
    else if (centrePala > pilotaY + 20) { // Pilota per sobre
        pala.y -= VELOCITAT_PALA * tempsTranscorregut * 0.7f; // Segueix cap amunt
    }

    if (pala.y < 0) pala.y = 0; // Bloqueja límit superior
    if (pala.y + pala.alcada > ALCADA_FINESTRA) { // Fora límit inferior
        pala.y = ALCADA_FINESTRA - pala.alcada; // Corregeix posició inferior
    }
}

void dibuixarPala(sf::RenderWindow& finestra, const Pala& pala) { // Renderitzat del gràfic
    sf::RectangleShape forma(sf::Vector2f(pala.amplada, pala.alcada)); // Crea forma rectangular
    forma.setPosition({ pala.x, pala.y }); // Situa el rectangle
    forma.setFillColor(sf::Color::White); // Color de pala
    finestra.draw(forma); // Dibuixa a finestra
}
