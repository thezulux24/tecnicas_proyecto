
#include "Models/structl.h"

int main() {
    int seleccionCarta;
    int flagJuego = 1;
    int flagTurno = 1;
    Carta cartas_disponibles[NUM_CARTAS];
    inicializarCartasDisponibles(cartas_disponibles);

    Jugador jugador;
    Enemigo enemigo;

    jugador.personaje.vida_actual = 50;
    jugador.personaje.vida_total = 150;
    jugador.oro = 10;
    jugador.nivel = 1;
    printf("\n");
    printf("************************************\n");
    printf("*                                  *\n");
    printf("*   Bienvenido a Battle of Codes!  *\n");
    printf("*                                  *\n");
    printf("************************************\n");
    printf("\n");
    printf("Ingresa el nombre del jugador: ");
    fgets(jugador.personaje.nombre, sizeof(jugador.personaje.nombre), stdin);

    int dificultad;
    printf("Hola, %s. Por favor, selecciona la dificultad del juego (1: facil, 2: medio, 3: dificil): ", jugador.personaje.nombre);    scanf("%d", &dificultad);
    Nivel* niveles;
    switch(dificultad) {
        case 1:
            niveles = leerNiveles("../Text/niveles.txt");
            break;
        case 2:
            niveles = leerNiveles("../Text/niveles2.txt");
            break;
        case 3:
            niveles = leerNiveles("../Text/niveles3.txt");
            break;
        default:
            printf("Dificultad no reconocida. Cargando niveles por defecto...\n");
            niveles = leerNiveles("../Text/niveles.txt");
    }


    ListaEnlazada *deck_general = crearListaEnlazada();
    seleccionarDeck(cartas_disponibles, deck_general, INICIAL_DECK);
    struct Nodo* pila_robo = NULL; // Cambiado de Pila* a struct Nodo*
    barajarListaYApilar(deck_general, &pila_robo); // Ahora pasamos la dirección de pila_robo


    ListaEnlazada *pila_descarte = crearListaEnlazada();
    ListaEnlazada *mano = crearListaEnlazada();
    Nivel* nivel_actual = niveles;
    int nuevo_enemigo = 1;

    robarCartas2(&pila_robo, mano); // Ahora pasamos la dirección de pila_robo

    printf("Recuerde que, AT=Ataque, DF=Defensa,LF= Efecto en vida  y EN=Costo de energia \n");

    while (flagJuego == 1 && nivel_actual != NULL) {
        printf("-------------------------------------------------------------------- \n");
        printf("imprimiendo Deck general para el nivel\n");
        imprimirListaCartas(deck_general);
        printf("-------------------------------------------------------------------- \n");

        printf("su oro es: %d\n", jugador.oro);
        printf("El nivel %d: %s\n", jugador.nivel, nivel_actual->tipo);
        if (strcmp(nivel_actual->tipo, "combate") == 0) {
            if (nuevo_enemigo) {
                enemigo = nivel_actual->enemigo;
                nuevo_enemigo = 0; // Establecer el indicador en 0 para no crear un nuevo enemigo en el próximo turno
            }
            jugador.defensa = 0;
            jugador.energia = 3;
            enemigo.personaje.ataque = rand() % 8 + 5;
            while (flagTurno == 1 && enemigo.personaje.vida_actual>0) {
                flagTurno = turno(&enemigo, &jugador, mano, &pila_robo, pila_descarte); // Ahora pasamos la dirección de pila_robo
            }
            moverCartasAlFinalizarTurno(mano,pila_descarte);
            robarCartas(&pila_robo, mano, pila_descarte); // Ahora pasamos la dirección de pila_robo
            vaciarListaDescarte(pila_descarte);


            if (jugador.personaje.vida_actual <= 0) {
                printf("HAS PERDIDO\n");
                flagJuego = 0;
            }
            else if (enemigo.personaje.vida_actual <= 0) {

                if (jugador.nivel == 10) {
                    printf("HAS GANADO EL JUEGO\n");
                    flagJuego = 0;
                }
                else {
                    int pasar = 0;
                    printf("HAS  GANADO, SELECIONA UNA DE LAS 3 CARTAS\n");
                    Carta *cartas3 = seleccionarTresCartasAleatorias(cartas_disponibles, deck_general);
                    printf("Cartas a seleccionar:\n");
                    for (int i = 0; i < 3; i++) {
                        printf("%s (AT: %d, DF: %d, Vida: %d, Energia: %d)\n", cartas3[i].nombre,
                               cartas3[i].ataque, cartas3[i].defensa,
                               cartas3[i].vida, cartas3[i].energia);
                    }
                    while(pasar == 0) {
                        scanf("%d", &seleccionCarta);
                        if (seleccionCarta < 1 || seleccionCarta > 3) {
                            printf("Selecciona una carta válida\n");
                        }
                        else {
                            agregarAlFinal(deck_general, cartas3[seleccionCarta - 1]);
                            printf("Se ha agregado %s al deck\n", cartas3[seleccionCarta - 1].nombre);
                            jugador.nivel++;
                            nivel_actual = nivel_actual->siguiente;
                            nuevo_enemigo = 1;
                            jugador.oro += (rand() % 11) + 10;
                            pasar = 1;
                        }


                    }
                }
            }

        }
        else if (strcmp(nivel_actual->tipo, "descanso") == 0) {
            // Si el nivel es de descanso, llamar a la función eventoDescanso
            eventoDescanso(deck_general, cartas_disponibles, &jugador);
            nivel_actual = nivel_actual->siguiente;
            jugador.nivel++;
        }

        else if (strcmp(nivel_actual->tipo, "tienda") == 0) {
            // Si el nivel es de tienda, llamar a la función eventoTienda
            eventoTienda(cartas_disponibles, deck_general, &jugador);
            nivel_actual = nivel_actual->siguiente;
            jugador.nivel++;

        }


        flagTurno= 1;
    }
    free(deck_general);
    while(pila_robo != NULL) { // Cambiado para liberar la nueva implementación de la pila
        struct Nodo* temp = pila_robo;
        pila_robo = pila_robo->siguiente;
        free(temp);
    }
    free(pila_descarte);
    return 0;
}

