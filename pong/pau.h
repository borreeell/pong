#include <SFML/Graphics.hpp> // Llibreria gràfica SFML

#include "pablo.h" // Inclou definició pales

// Estructura que representa la pilota
struct Pilota // Defineix la pilota
{ 
    float x, y; // Posició de pilota
    float radi; // Mida del cercle
    float velocitatX, velocitatY; // Vectors de moviment
};

void inicialitzarPilota(Pilota& pilota); // Configura valors inicials
void actualitzarPilota(Pilota& pilota, float tempsTranscorregut); // Mou la pilota
void gestionarCollisions(Pilota& pilota, const Pala& palaEsquerra, const Pala& palaDreta); // Gestiona xocs pales
bool comprovarPuntuacio(const Pilota& pilota, Pala& palaEsquerra, Pala& palaDreta); // Detecta punt marcat
void dibuixarPilota(sf::RenderWindow& finestra, const Pilota& pilota); // Mostra pilota finestra
