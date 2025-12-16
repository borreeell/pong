#include "pablo.h"

const float AMPLADA_PALA = 15.0f;
const float ALCADA_PALA = 100.0f;
const float VELOCITAT_PALA = 400.0f;
const int ALCADA_FINESTRA = 600;

void inicialitzarPala(Pala& pala, float x, float y) {
    pala.x = x;
    pala.y = y;
    pala.amplada = AMPLADA_PALA;
    pala.alcada = ALCADA_PALA;
    pala.puntuacio = 0;
}

void mourePala(Pala& pala, float tempsTranscorregut, bool amunt, bool avall) {
    if (amunt && pala.y > 0) {
        pala.y -= VELOCITAT_PALA * tempsTranscorregut;
    }
    if (avall && pala.y + pala.alcada < ALCADA_FINESTRA) {
        pala.y += VELOCITAT_PALA * tempsTranscorregut;
    }
}

void moureIA(Pala& pala, float pilotaX, float pilotaY, float tempsTranscorregut) {
    float centrePala = pala.y + pala.alcada / 2.0f;

    if (centrePala < pilotaY - 20) {
        pala.y += VELOCITAT_PALA * tempsTranscorregut * 0.7f;
    }
    else if (centrePala > pilotaY + 20) {
        pala.y -= VELOCITAT_PALA * tempsTranscorregut * 0.7f;
    }

    // Mantenir dins dels límits
    if (pala.y < 0) pala.y = 0;
    if (pala.y + pala.alcada > ALCADA_FINESTRA) {
        pala.y = ALCADA_FINESTRA - pala.alcada;
    }
}

void dibuixarPala(sf::RenderWindow& finestra, const Pala& pala) {
    sf::RectangleShape forma(sf::Vector2f(pala.amplada, pala.alcada));
    forma.setPosition({ pala.x, pala.y });
    forma.setFillColor(sf::Color::White);
    finestra.draw(forma);
}