
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
    jugador.personaje.vida_total = 50;
    enemigo.personaje.vida_actual = 20;
    enemigo.personaje.vida_total = 20;

    printf("Ingresa el nombre del jugador: ");
    fgets(jugador.personaje.nombre, sizeof(jugador.personaje.nombre), stdin);
    ListaEnlazada *deck_general = crearListaEnlazada();
    seleccionarDeck(cartas_disponibles, deck_general, INICIAL_DECK);
    Pila *pila_robo = inicializarPila(NUM_CARTAS);
    barajarListaYApilar(deck_general, pila_robo);
    printf("Pila de robado:\n");
    imprimirPila(pila_robo);

    ListaEnlazada *pila_descarte = crearListaEnlazada();
    ListaEnlazada *mano = crearListaEnlazada();
    robarCartas2(pila_robo, mano);
    printf("Recuerde que, AT=Ataque, DF=Defensa,LF= Efecto en vida  y EN=Costo de energia \n");
    while (flagJuego == 1) {
        jugador.defensa = 0;
        jugador.energia = 3;
        enemigo.personaje.ataque = rand() % 8 + 5;
        while (flagTurno == 1 && enemigo.personaje.vida_actual>0) {
            flagTurno = turno(&enemigo, &jugador, mano, pila_robo, pila_descarte);
        }
        moverCartasAlFinalizarTurno(mano,pila_descarte);
        robarCartas(pila_robo, mano,pila_descarte);
        vaciarListaDescarte(pila_descarte);

        if (jugador.personaje.vida_actual <= 0) {
            printf("HAS PERDIDO\n");
            flagJuego = 0;
        }
        else if (enemigo.personaje.vida_actual <= 0){
            printf("HAS  GANADO, SELECIONA UNA DE LAS 3 CARTAS\n");
            Carta *cartas3 = seleccionarTresCartasAleatorias(cartas_disponibles, deck_general);
            printf("Cartas a seleccionar:\n");
            for (int i = 0; i < 3; i++) {
                printf("%s (AT: %d, DF: %d, Vida: %d, Energia: %d)\n", cartas3[i].nombre,
                       cartas3[i].ataque, cartas3[i].defensa,
                       cartas3[i].vida, cartas3[i].energia);
            }
            scanf("%d", &seleccionCarta);
            agregarAlFinal(deck_general, cartas3[seleccionCarta-1]);
            printf("Se ha agregado %s al deck\n", cartas3[seleccionCarta-1].nombre);
            flagJuego = 0;


        }
        flagTurno= 1;
    }
    free(deck_general);
    free(pila_robo->cartas);
    free(pila_robo);
    free(pila_descarte);
    return 0;
}

