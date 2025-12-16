# Ping Pong Retro Challenge

Projecte **Ping Pong Retro Challenge**, una recreació del clàssic joc arcade desenvolupada en C++ utilitzant la llibreria gràfica SFML.

## Autors
* **Pau Borrell**
* **Pablo Abad**

---
## Descripció
Aquest projecte consisteix en un joc de Ping Pong funcional amb gràfics bàsics i moviment fluid. L'objectiu és colpejar la pilota amb la teva barra per evitar que surti pel teu costat del camp. El joc inclou una petita lògica per a un oponent automàtic i detecció de col·lisions amb els límits de la pantalla.

## Disseny Descendent (Estructura)
Hem dividit el desenvolupament en tres nivells lògics:

* **Nivell 1 (Interfície i Finestra):** Gestió de la finestra principal amb SFML i control del bucle d'esdeveniments (tancar finestra, lectura de tecles).
* **Nivell 2 (Lògica d'Entitats):** Funcions dedicades al moviment de les pales, el control de la pilota i la gestió de les col·lisions.
* **Nivell 3 (Utilitats):** Càlculs matemàtics per als rebots i generació de moviments aleatoris (IA i inici de ronda).
---

## Tasques Realitzades
El repartiment i execució de les tasques principals ha estat el següent:

- **Configuració inicial:** Preparació de l'entorn de codi i integració de llibreries.
- **Moviment del jugador:** Implementació dels controls per teclat (`W` i `S`) per a la pala del jugador.
- **IA/Moviment Random:** Creació d'un sistema automàtic amb `rand()` perquè la pilota i la pala rival tinguin comportaments autònoms.
- **Control de límits:** Restriccions físiques per mantenir els elements dins de la finestra de **800x600**.

---

## Compilació i Execució

### Requisits
És necessari tenir configurada la llibreria **SFML** a Visual Studio:
1. Afegir els directoris `include` al projecte.
2. Enllaçar les llibreries `.lib` corresponents.
3. Assegurar que els fitxers `.dll` de SFML estiguin al directori de l'executable.

### Instruccions a Visual Studio
* **Compilar:** Prem `F7`
* **Executar:** Prem `F5`

---

## Controls
Acció i Tecla
Moure Amunt --> `W`
Moure Avall --> `S`
Sortir --> `Esc` (Tancar Finestra)
