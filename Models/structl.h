//
// Created by MacBook Pro on 10/05/24.
//


#ifndef TECNICAS_PROYECTO_STRUCTL_H
#define TECNICAS_PROYECTO_STRUCTL_H


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define NUM_CARTAS 20
#define MANO_JUGADOR 5
#define INICIAL_DECK 7

typedef struct Carta {
    char* nombre;
    int ataque;
    int defensa;
    int vida;
    int energia;
    int precio;
} Carta;

typedef struct Nodo {
    Carta carta;
    struct Nodo* siguiente;
} Nodo;

typedef struct ListaEnlazada {
    Nodo* cabeza;
    int longitud;
} ListaEnlazada;

typedef struct Personaje {
    char nombre[20];
    int vida_actual;
    int vida_total;
    int ataque;

} Personaje;

typedef struct Jugador {
    Personaje personaje;
    int energia;
    int defensa;
    int oro;
    int nivel;
} Jugador;

typedef struct Enemigo {
    Personaje personaje;
} Enemigo;

typedef struct Nivel {
    char tipo[10];
    Enemigo enemigo;
    struct Nivel* siguiente;
} Nivel;



// Prototipos de funciones
Nivel* leerNiveles();
void imprimirPila(struct Nodo* tope);
Nodo* crearNodo(Carta carta);
ListaEnlazada* crearListaEnlazada();
void agregarAlFinal(ListaEnlazada* lista, Carta carta);
void apilar(struct Nodo** tope, Carta carta);
Carta desapilar(struct Nodo** tope);
void barajarListaYApilar(ListaEnlazada* lista, struct Nodo** tope);
void seleccionarDeck (Carta* cartas_disponibles, ListaEnlazada* deck_general, int num_cartas_inicial);
void imprimirListaCartas(ListaEnlazada* lista);
void robarCartas(struct Nodo** tope, ListaEnlazada* mano, ListaEnlazada* pila_descarte);
Carta* seleccionarTresCartasAleatorias(Carta* cartas_disponibles, ListaEnlazada* deck_general);
Carta obtenerCartaEnIndice(ListaEnlazada* lista, int indice);
void moverCartasAlFinalizarTurno(ListaEnlazada* mano, ListaEnlazada* pila_descarte);
int turno(struct Enemigo* enemigo, struct Jugador* jugador, ListaEnlazada* mano, struct Nodo** tope, ListaEnlazada* pila_descarte);
void inicializarCartasDisponibles(Carta* cartas_disponibles);
void eliminarCartaLista(ListaEnlazada* lista, int indice);
void robarCartas2(struct Nodo** tope, ListaEnlazada* mano);
void vaciarListaDescarte(ListaEnlazada* pila_descarte);
void eventoTienda(Carta* cartas_disponibles, ListaEnlazada* deck_general, struct Jugador* jugador);
void eventoDescanso(ListaEnlazada* deck_general, Carta* cartas_disponibles, struct Jugador* jugador);

#endif // TECNICAS_PROYECTO_STRUCTL_H
