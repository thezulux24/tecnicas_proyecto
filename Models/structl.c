
#include "structl.h"
void apilar(struct Nodo** tope, Carta carta) {
    struct Nodo* nuevoNodo = crearNodo(carta);
    nuevoNodo->siguiente = *tope;
    *tope = nuevoNodo;
}

int turno(struct Enemigo* enemigo, struct Jugador* jugador, ListaEnlazada* mano, struct Nodo** pila_robo, ListaEnlazada* pila_descarte) {
    int seleccion;
    printf("imprimiendo descarte\n");
    imprimirListaCartas(pila_descarte);

    int flag = 1;
    strcpy(enemigo->personaje.nombre, "Kratos");
    jugador->personaje.ataque = 0;
    eliminarEspacios(jugador->personaje.nombre);
    printf("Hola %s, tu vida es %d/%d\n", jugador->personaje.nombre, jugador->personaje.vida_actual, jugador->personaje.vida_total);
    printf("su energia es: %d\n", jugador->energia);
    printf("su defensa es: %d\n", jugador->defensa);
    printf("Su enemigo se llama %s, su vida es de %d/%d\n", enemigo->personaje.nombre, enemigo->personaje.vida_actual, enemigo->personaje.vida_total);
    printf("Su enemigo le hara %d dano\n", enemigo->personaje.ataque);
    printf("-------------------------------------------------------------------- \n");
    printf("Las cartas disponibles son: \n");
    imprimirListaCartas(mano);
    printf("Por favor selecciona tu carta, debes marcar el número de la carta o escribir 0 para finalizar el turno\n");
    printf("-------------------------------------------------------------------- \n");
    scanf("%d", &seleccion);
    if (seleccion == 0) {
        printf("\n ----------------- \n");
        printf("Turno finalizado\n");

        if (jugador->defensa < enemigo->personaje.ataque){
            printf("Su enemigo le genero %d dano\n", -(jugador->defensa-enemigo->personaje.ataque));
            jugador->personaje.vida_actual += jugador->defensa-enemigo->personaje.ataque;
        }
        else {
            printf("su enemigo no le genero dano\n");
        }

        flag = 0;
    }
    else if (seleccion > mano->longitud) {
        printf("La carta no está en el mazo.\n");
    }
    else if (jugador->energia < -(obtenerCartaEnIndice(mano, seleccion - 1).energia)) {
        printf("Energía insuficiente.\n");
    }
    else if ((jugador->energia -(obtenerCartaEnIndice(mano, seleccion - 1).energia)) >= 0) {
        Carta cartaSeleccionada = obtenerCartaEnIndice(mano, seleccion - 1);
        jugador->personaje.ataque += cartaSeleccionada.ataque;
        jugador->defensa += cartaSeleccionada.defensa;
        jugador->energia += cartaSeleccionada.energia;
        jugador->personaje.vida_actual += cartaSeleccionada.vida;
        if (enemigo->personaje.vida_actual > 0) {
            printf("Has generado %d de daño a tu enemigo\n", jugador->personaje.ataque);
            enemigo->personaje.vida_actual -= jugador->personaje.ataque;
        }
        agregarAlFinal(pila_descarte, cartaSeleccionada);
        eliminarCartaLista(mano, seleccion - 1);
    } else {
        printf("ERROR\n");
    }
    return flag;
}

// Función para crear un nuevo nodo
struct Nodo* crearNodo(Carta carta) {
    struct Nodo* nuevoNodo = (struct Nodo*)malloc(sizeof(struct Nodo));
    nuevoNodo->carta = carta;
    nuevoNodo->siguiente = NULL;
    return nuevoNodo;
}

ListaEnlazada* crearListaEnlazada() {
    ListaEnlazada* lista = (ListaEnlazada*)malloc(sizeof(ListaEnlazada));
    lista->cabeza = NULL;
    lista->longitud = 0;
    return lista;
}
// Agrega nodo al final de una lista dada, por ejemplo al final de la pelea al añadir nueva carta al Deck general
void agregarAlFinal(ListaEnlazada* lista, Carta carta) {
    Nodo* nuevoNodo = crearNodo(carta);
    if (lista->cabeza == NULL) {
        lista->cabeza = nuevoNodo;
    } else {
        Nodo* actual = lista->cabeza;
        while (actual->siguiente != NULL) {
            actual = actual->siguiente;
        }
        actual->siguiente = nuevoNodo;
    }
    lista->longitud++;
}



// Función para eliminar un elemento de la parte superior de la pila
Carta desapilar(struct Nodo** tope) {
    if (*tope == NULL) {
        printf("La pila está vacía.\n");
        Carta cartaVacia = {"", 0, 0, 0, 0};
        return cartaVacia; // Valor sentinela para indicar error
    }
    struct Nodo* temp = *tope;
    Carta cartaSacada = temp->carta;
    *tope = (*tope)->siguiente;
    free(temp);
    return cartaSacada;
}

// Función para imprimir los elementos de la pila
void imprimirPila(struct Nodo* tope) {
    printf("Elementos de la pila:\n");
    while (tope != NULL) {
        printf("%s ", tope->carta.nombre);
        tope = tope->siguiente;
    }
    printf("\n");
}

void barajarListaYApilar(ListaEnlazada* lista, struct Nodo** tope) {
    srand(time(NULL));

    int longitud = lista->longitud;

    // Convertimos la lista enlazada en un array de puntero a los nodos
    Nodo** nodos = (Nodo**)malloc(longitud * sizeof(Nodo*));
    Nodo* actual = lista->cabeza;
    int i = 0;
    while (actual != NULL) {
        nodos[i] = actual;
        actual = actual->siguiente;
        i++;
    }

    for (i = longitud - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        Nodo* temp = nodos[i];
        nodos[i] = nodos[j];
        nodos[j] = temp;
    }

    // Recontruir lista enlazada con nodos barajados
    lista->cabeza = nodos[0];
    for (i = 0; i < longitud - 1; i++) {
        nodos[i]->siguiente = nodos[i + 1];
    }
    nodos[longitud - 1]->siguiente = NULL;

    // Se apilan los nodos en la pila de robo
    for (i = 0; i < longitud; i++) {
        apilar(tope, nodos[i]->carta);
    }

    free(nodos);
}



void imprimirListaCartas(ListaEnlazada* lista) {
    Nodo* actual = lista->cabeza;
    int indice = 0;
    while (actual != NULL) {
        printf("[%d] %s (AT: %d, DF: %d, Vida: %d, Energia: %d)\n", indice+1, actual->carta.nombre, actual->carta.ataque, actual->carta.defensa, actual->carta.vida, actual->carta.energia);
        actual = actual->siguiente;
        indice++;
    }
}


/*
La funcion de elegir las 7 cartas del deck general, cabe aclarar que se volvio a implementar el doble ciclo for,
debido a que el metodo de usar un arreglo estatico como fue recomendado hacia que las cartas se pudieran repetir en el deck
*/
void seleccionarDeck(Carta* cartas_disponibles, ListaEnlazada* deck_general, int num_cartas_inicial) {
    srand(time(NULL));
    int cartas_disponibles_count = NUM_CARTAS;

    for (int i = 0; i < num_cartas_inicial; i++) {
        int indice_carta = rand() % cartas_disponibles_count;
        agregarAlFinal(deck_general, cartas_disponibles[indice_carta]);

        for (int j = indice_carta; j < cartas_disponibles_count - 1; j++) {
            cartas_disponibles[j] = cartas_disponibles[j + 1];
        }
        cartas_disponibles_count--;
    }
}
// Roba las cartas de la pila de robo a la mano y si la pila de robo esta vacia baraja la pila de descarte y devuelve las cartas a la pila de robo
void robarCartas(struct Nodo** pila_robo, ListaEnlazada* mano, ListaEnlazada* pila_descarte) {
    if (*pila_robo == NULL) {
        barajarListaYApilar(pila_descarte, pila_robo);
    }

    while (mano->longitud < MANO_JUGADOR && *pila_robo != NULL) {
        Carta carta = desapilar(pila_robo);
        agregarAlFinal(mano, carta);
    }

    while (mano->longitud < MANO_JUGADOR && *pila_robo == NULL && pila_descarte->cabeza != NULL) {
        barajarListaYApilar(pila_descarte, pila_robo);

        while (mano->longitud < MANO_JUGADOR && *pila_robo != NULL) {
            Carta carta = desapilar(pila_robo);
            agregarAlFinal(mano, carta);
        }
    }
}
// funcion vieja que no se uso al final
void robarCartas2(struct Nodo** pila_robo, ListaEnlazada* mano) {
    while (mano->cabeza != NULL) {
        Nodo* temp = mano->cabeza;
        mano->cabeza = mano->cabeza->siguiente;
        free(temp);
    }
    mano->longitud = 0;

    while (mano->longitud < 5 && *pila_robo != NULL) {
        Carta carta = desapilar(pila_robo);
        agregarAlFinal(mano, carta);
    }
}




// Escoge las 3 cartas a elejir al final de la pelea si el jugador gana
Carta* seleccionarTresCartasAleatorias(Carta* cartas_disponibles, ListaEnlazada* deck_general) {
    static Carta cartas_seleccionadas[3];

    char* nombres_en_deck[deck_general->longitud];
    Nodo* actual = deck_general->cabeza;
    int i = 0;
    while (actual != NULL) {
        nombres_en_deck[i] = actual->carta.nombre;
        actual = actual->siguiente;
        i++;
    }

    srand(time(NULL));

    int cartas_seleccionadas_count = 0;
    for (int k = 0; k < NUM_CARTAS && cartas_seleccionadas_count < 3; k++) {
        int encontrado = 0;
        for (int j = 0; j < deck_general->longitud && encontrado == 0; j++) {
            if (strcmp(cartas_disponibles[k].nombre, nombres_en_deck[j]) == 0) {
                encontrado = 1;
            }
        }
        if (!encontrado) {
            cartas_seleccionadas[cartas_seleccionadas_count] = cartas_disponibles[k];
            cartas_seleccionadas_count++;
        }
    }

    return cartas_seleccionadas;
}


Carta obtenerCartaEnIndice(ListaEnlazada* lista, int indice) {
    Carta carta;
    int bool = 0;
    if (lista == NULL || lista->cabeza == NULL || indice < 0) {
        bool = 1;
    }
    if (bool == 0) {
        Nodo *actual = lista->cabeza;
        int contador = 0;

        while (actual != NULL && contador < indice) {
            actual = actual->siguiente;
            contador++;
        }

        if (actual != NULL) {
            carta = actual->carta;
        }
        else{
            printf("fuera de rango\n");
        }
    }
    return  carta;
}


// Mover cartas de la mano a la pila de descarte al final de cada turno
void moverCartasAlFinalizarTurno(ListaEnlazada* mano, ListaEnlazada* pila_descarte) {
    while (mano->cabeza != NULL) {
        Nodo *temp = mano->cabeza;
        mano->cabeza = mano->cabeza->siguiente;
        temp->siguiente = NULL;
        if (pila_descarte->cabeza == NULL) {
            pila_descarte->cabeza = temp;
        } else {
            Nodo *actual = pila_descarte->cabeza;
            while (actual->siguiente != NULL) {
                actual = actual->siguiente;
            }
            actual->siguiente = temp;
        }
        pila_descarte->longitud++;
    }
    mano->longitud = 0;
}
// Vacia la pila de descarte cuando se requiera

void vaciarListaDescarte(ListaEnlazada* pila_descarte) {
    Nodo* actual = pila_descarte->cabeza;
    while (actual != NULL) {
        Nodo* temp = actual;
        actual = actual->siguiente;
        free(temp);
    }
    pila_descarte->cabeza = NULL;
    pila_descarte->longitud = 0;
}


void inicializarCartasDisponibles(Carta* cartas_disponibles) {
    FILE* archivo = fopen("../Text/cartas.txt", "r");
    if (archivo == NULL) {
        printf("No se pudo abrir el archivo ../Text/cartas.txt\n");
        return;
    }

    char linea[256];
    int i = 0;
    while (fgets(linea, sizeof(linea), archivo)) {
        Carta* carta = &cartas_disponibles[i];
        carta->nombre = malloc(50 * sizeof(char)); //liberar esta memoria más tarde
        sscanf(linea, "%[^,],%d,%d,%d,%d", carta->nombre, &carta->ataque, &carta->defensa, &carta->vida, &carta->energia);
        i++;
    }

    fclose(archivo);
}
void eliminarEspacios(char *str) {
    int len = strlen(str);
    while (len > 0 && (str[len - 1] == ' ' || str[len - 1] == '\n' || str[len - 1] == '\r')) {
        str[len - 1] = '\0';
        len--;
    }
}

void eliminarCartaLista(ListaEnlazada* lista, int indice) {
    int eliminado = 0;

    if (lista != NULL && lista->cabeza != NULL && indice >= 0) {
        Nodo *actual = lista->cabeza;
        Nodo *anterior = NULL;

        int indiceActual = 0;

        while (actual != NULL && indiceActual < indice) {
            anterior = actual;
            actual = actual->siguiente;
            indiceActual++;
        }

        if (actual != NULL) {
            eliminado = 1;

            if (anterior == NULL) {
                lista->cabeza = actual->siguiente;
            } else {
                anterior->siguiente = actual->siguiente;
            }

            free(actual);
        }
    }
}