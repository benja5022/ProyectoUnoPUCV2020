#include "funciones.h"

/*
struct Area_de_juego{
    struct Area_de_juego * area_enemiga;
    char nombre_jugador[100];
    Mapa * cementerio;
    Mapa * mazo_castillo;
    Mapa * linea_defensa;
    Mapa * linea_ataque;
    Mapa * mano;
    unsigned int reserva_de_oro;
    unsigned int oro_pagado;
    pila * oros;
    lista * linea_de_apoyo;
    lista * destierro;
};
*/
struct carta{

    int tipo;
    int coste;
    int habilidad_talisman;
    int habilidad_totem;
    int habilidad_arma;
    int fuerza;
    char nombre[100];
    char id[6];

};

carta * crearCarta(char * linea){
    carta * carta_nueva = (carta *) malloc (sizeof(carta));

    carta_nueva ->coste = atoi(get_csv_field(linea,7));
    carta_nueva ->fuerza = atoi(get_csv_field(linea,8));
    carta_nueva ->habilidad_arma = atoi(get_csv_field(linea,6)) ;
    carta_nueva ->habilidad_talisman = atoi(get_csv_field(linea,4));
    carta_nueva ->habilidad_totem = atoi(get_csv_field(linea,5));
    carta_nueva ->tipo = atoi(get_csv_field(linea,3));
    strcpy(carta_nueva->nombre,get_csv_field(linea,2));


//    printf("Nombre:%s\nCoste:%d\nFuerza:%d\nTipo:%d\nHabilidad Arma:%d\n\n",carta_nueva -> nombre,carta_nueva ->coste, carta_nueva ->fuerza, carta_nueva ->tipo, carta_nueva ->habilidad_arma);

    return carta_nueva;
}

char * _strdup (const char *s) {
	size_t len = strlen (s) + 1;
    void *new = malloc (len);

	if (new == NULL)
	    return NULL;

	return (char *) memcpy (new, s, len);
}

const char* get_csv_field (char * tmp, int i) {

    char * line = _strdup (tmp);
    const char * tok;
    for (tok = strtok (line, ";"); tok && *tok; tok = strtok (NULL, ";\n")) {
        if (!--i) {
            return tok;
        }
    }
    return NULL;
}

