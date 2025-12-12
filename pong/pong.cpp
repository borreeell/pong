// PROGRAMA --> Ping Pong
// AUTOR --> Pablo Abad Ortega
// FECHA --> 11/12/2025

#include <iostream> //  entrada/salida
#include <SFML/Graphics.hpp> // para gráficos

using namespace sf; // espacio de nombres de SFML
using namespace std; // espacio de nombres estándar

int main()
{

	// CREAR VENTANA 
	RenderWindow window(VideoMode({ 500, 500 }), "PING PONG");


	// CREAR FORMAS - CIRCULOS
	CircleShape pelota(10.f);   // Círculo de radio 30
	pelota.setFillColor(Color::Red);
	pelota.setPosition({ 30.f, 30.f });
	window.draw(pelota); // dibuja círculo verde

	// RECTANGULOS - PALAS
	RectangleShape pala1({ 10.f, 30.f });
	pala1.setFillColor(Color::White);
	pala1.setPosition({ 30.f, 30.f });
	window.draw(pala1); // dibuja rectangulo verde


	int contador = 0; // contador en 0


	while (window.isOpen()) // bucle principal se ejecuta mientras la ventana esté abierta
	{
		// Bucle para eventos
		while (const optional event = window.pollEvent())
		{
			// Si el evento es cerrar la ventana...
			if (event->is<Event::Closed>()) window.close(); // ...cierra la ventana
		}

		contador++;
		pelota.setPosition({ 30.f + 10 * contador, 30.f }); // cambiar la posicion de la pelota



		window.draw(pelota); // dibuja círculo verde
		window.draw(pala1); // dibuja rectangulo verde

		window.display(); // actualiza la pantalla
		sleep(seconds(1));

		// CONFIG. VENTANA
		window.clear(); // limpia la ventana con el color por defecto de negro
	}
}