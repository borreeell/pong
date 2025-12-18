#include <SFML/Graphics.hpp>

#include "pablo.h"

// Estructura que representa la pilota
struct Pilota {
    float x, y;
    float radi;
    float velocitatX, velocitatY;
};

void inicialitzarPilota(Pilota& pilota);
void actualitzarPilota(Pilota& pilota, float tempsTranscorregut);
void gestionarCollisions(Pilota& pilota, const Pala& palaEsquerra, const Pala& palaDreta);
bool comprovarPuntuacio(const Pilota& pilota, Pala& palaEsquerra, Pala& palaDreta);
void dibuixarPilota(sf::RenderWindow& finestra, const Pilota& pilota);
