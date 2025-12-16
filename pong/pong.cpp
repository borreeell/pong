// PROGRAMA --> Ping Pong
// AUTOR --> Pablo Abad Ortega
// FECHA --> 11/12/2025

#include <iostream> //  entrada/salida
#include <SFML/Graphics.hpp> // para gráficos
#include <cstdlib> 
#include <ctime>   

using namespace sf; // espacio de nombres de SFML
using namespace std; // espacio de nombres estándar

// DECLARACIONES DE LAS FUNCIONES
void mover_pala1(RectangleShape& p, float dy) // mueve la pala1
{
	// posicion vertical actual i hacer moverla (dy)
	float nueva_y = p.getPosition().y + dy;

	// restricciones limites de 0 a 600 (altura pala)
	float altura_pala = p.getSize().y;
	float altura_ventana = 600.0f;

	if (nueva_y < 0.0f) // limite de altura
	{
		nueva_y = 0.0f;
	}
	else if (nueva_y > altura_ventana - altura_pala) // limite inferior
	{
		nueva_y = altura_ventana - altura_pala;
	}
	
	p.setPosition({ p.getPosition().x, nueva_y });
}


void mover_pala2(RectangleShape& p, float dy) // mueve la pala2
{
	// posicion vertical actual i hacer moverla (dy)
	float nueva_y = p.getPosition().y + dy;

	// restricciones limites de 0 a 600 (altura pala)
	float altura_pala = p.getSize().y;
	float altura_ventana = 600.0f;

	if (nueva_y < 0.0f) // limite de altura
	{
		nueva_y = 0.0f;
	}
	else if (nueva_y > altura_ventana - altura_pala) // limite inferior
	{
		nueva_y = altura_ventana - altura_pala;
	}

	p.getPosition();
}

void actualizar_pelota(CircleShape& b, float dt); // actualiza movimiento de la pelota
bool checkCollision(const RectangleShape& p, const CircleShape& b); // comprueba si la pala está tocando la pelota 

void resolveCollision(RectangleShape& p, CircleShape& b); // cambia la dirección de la pelota

void resetBall(CircleShape& b); // coloca la pelota de nuevo en el centro de la pantalla después de que se anote un punto


int main()
{
	srand(time(0)); 
	const float velocidad_random = 6.0f;
	const float velocidad_pala_jugador = 8.0f;

	// CREAR VENTANA 
	RenderWindow window(VideoMode({ 800, 600 }), "PING PONG"); // crea ventana con las midas (800, 600)
	window.setFramerateLimit(60); // 60 cuadros/seg

	// CREAR FORMAS - CIRCULOS
	CircleShape pelota(10.f); // Círculo de radio 30
	pelota.setFillColor(Color::Red);
	pelota.setPosition({ 30.f, 30.f });
	window.draw(pelota); // dibuja círculo 

	// RECTANGULOS - PALA1
	RectangleShape pala1({ 10.f, 120.f }); // midas del rectangulo 
	pala1.setFillColor(Color::White); // color blanco
	pala1.setPosition({ 30.f, 30.f }); // posicion en la ventana
	window.draw(pala1); // dibuja rectangulo 

	// RECTANGULOS - PALA2
	RectangleShape pala2({ 10.f, 120.f }); // midas del rectangulo 
	pala2.setFillColor(Color::White); // color blanco
	pala2.setPosition({ 750.f, 470.f }); // posicion en la ventana
	window.draw(pala2); // dibuja rectangulo 
	float movimiento_pala1_dy;
	while (window.isOpen()) // bucle principal se ejecuta mientras la ventana esté abierta
	{

		// Bucle para eventos
		while (const optional event = window.pollEvent())
		{
			if (event->is<Event::Closed>()) window.close();

			if (const auto* key = event->getIf<Event::KeyPressed>()) {
				// CONTROLES DEL JUGADOR (PALA1)
				 movimiento_pala1_dy = 0.0f;
				if (key-> scancode == Keyboard::Scancode::W)
				{
					movimiento_pala1_dy -= velocidad_pala_jugador;
				}
				else if (key->scancode == Keyboard::Scancode::S)

				{
					movimiento_pala1_dy += velocidad_pala_jugador;
				}

			}
		}	
		if (movimiento_pala1_dy != 0.0f)
				{
					mover_pala1(pala1, movimiento_pala1_dy);
				}
		// MOVIMIENTO RANDOM PALA2
		float centrar_pala_y = pala2.getPosition().y + (pala2.getSize().y / 2.0f);
		float centrar_pelota_y = pelota.getPosition().y + (pelota.getRadius());
		float dy = centrar_pelota_y - centrar_pala_y;

		if (dy > 0)
		{
			dy = min(dy, velocidad_random);
		}
		else if (dy < 0)
		{
			dy = max(dy, -velocidad_random);
		}
		mover_pala2(pala2, dy);

	
		pelota.setPosition({ 30.f + 10, 30.f }); // cambiar la posicion de la pelota

		// DIBUJAR OBJETOS EN PANTALLA
		window.draw(pelota);
		window.draw(pala1);
		window.draw(pala2);

		window.display(); // actualiza la pantalla
		sleep(seconds(1));

		// CONFIG. VENTANA
		window.clear(); // limpia la ventana con el color por defecto de negro
	}

	
}



void actualizar_pelota(CircleShape& b, float dt)
{
}

bool checkCollision(const RectangleShape& p, const CircleShape& b)
{
	return false;
}

void resolveCollision(RectangleShape& p, CircleShape& b)
{
}

void resetBall(CircleShape& b)
{
	float velocidad_pelota_X = 0.0f;
	float velocidad_pelota_Y = 0.0f;
	float velocidad_pelota = 8.0f;

	// REPOSICIONAR PELOTA EN EL CENTRO DE LA PANTALLA
	b.setPosition({ 400.0f - b.getRadius(), 300.0f - b.getRadius()});

	// DIRECCION EN VERTICAL (velocidad_pelota_y)
	float movimiento_vertical_random = 4.0f + static_cast<float>(rand() % 5);

	// positivo o negativo en random
	if (rand() % 2 == 0) // 50% de probable
	{
		velocidad_pelota_X = movimiento_vertical_random; // direccion hacia abajo
	}
	else
	{
		velocidad_pelota_Y = -movimiento_vertical_random; // direccion hacia arriba
	}

	// DIRECCION EN VERTICAL (velocidad_pelota_X)
	if (rand() % 2 == 0) // 50% de probable
	{
		velocidad_pelota_X = velocidad_pelota; 
	}
	else
	{
		velocidad_pelota_X = -velocidad_pelota; // se dirije a la izquierda (pala2)
	}
}
