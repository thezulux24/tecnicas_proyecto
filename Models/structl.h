//
// Created by MacBook Pro on 10/05/24.
//


#ifndef TECNICAS_PROYECTO_STRUCTL_H
#define TECNICAS_PROYECTO_STRUCTL_H


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define NUM_CARTAS 14
#define MANO_JUGADOR 5
#define INICIAL_DECK 7

typedef struct Carta {
    char* nombre;
    int ataque;
    int defensa;
    int vida;
    int energia;
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
} Jugador;

typedef struct Enemigo {
    Personaje personaje;
} Enemigo;

typedef struct Pila {
    Carta* cartas;
    int tope;
    int capacidad;
} Pila;

// Prototipos de funciones
Nodo* crearNodo(Carta carta);
ListaEnlazada* crearListaEnlazada();
void agregarAlFinal(ListaEnlazada* lista, Carta carta);
Pila* inicializarPila(int capacidad);
void apilar(Pila* pila, Carta carta);
Carta desapilar(Pila* pila);
void barajarListaYApilar(ListaEnlazada* lista, Pila* pila_robo);
void seleccionarDeck (Carta* cartas_disponibles, ListaEnlazada* deck_general, int num_cartas_inicial);
void imprimirListaCartas(ListaEnlazada* lista);
void robarCartas(Pila* pila_robo, ListaEnlazada* mano, ListaEnlazada* pila_descarte);
void imprimirPila(Pila* pila);
Carta* seleccionarTresCartasAleatorias(Carta* cartas_disponibles, ListaEnlazada* deck_general);
Carta obtenerCartaEnIndice(ListaEnlazada* lista, int indice);
void moverCartasAlFinalizarTurno(ListaEnlazada* mano, ListaEnlazada* pila_descarte);
int turno(struct Enemigo* enemigo, struct Jugador* jugador, ListaEnlazada* mano, Pila* pila_robo, ListaEnlazada* pila_descarte);
void inicializarCartasDisponibles(Carta* cartas_disponibles);
void eliminarEspacios(char *str);
void eliminarCartaLista(ListaEnlazada* lista, int indice);
void robarCartas2(Pila* pila_robo, ListaEnlazada* mano);
void vaciarListaDescarte(ListaEnlazada* pila_descarte);

#endif // TECNICAS_PROYECTO_STRUCTL_H