#ifndef HABILIDADES_H
#define HABILIDADES_H

typedef struct carta carta;

typedef struct Partida Partida;

typedef struct Area_de_juego Area_de_juego;

struct carta{

    int tipo;
    int coste;
    int habilidad_talisman;
    int habilidad_totem;
    int habilidad_arma;
    int fuerza;
    char nombre[100];
    struct carta * arma;
    bool estado; //si es bool, significa que ha sido usado

};

struct Partida{
    char nombre_partida[50];
    char nombre_Jugador1[50];
    char nombre_Jugador2[50];

};

struct Area_de_juego{
    struct Area_de_juego * area_enemiga;
    char nombre_jugador[100];
    char nombre_partida[100];
    Map * cementerio;
    Map * mazo_castillo;
    Map * linea_defensa;
    Map * linea_ataque;
    Map * mano;
    unsigned int reserva_de_oro;
    unsigned int oro_pagado;
    stack * oros;
    list * linea_de_apoyo;
    list * destierro;
    unsigned short total;
};

void h_totem_cero(carta* card, Area_de_juego* Area);

void h_totem_uno(carta* card, Area_de_juego* Area);

void h_totem_dos(carta* card,Area_de_juego* Area);

void h_totem_tres(carta* card, Area_de_juego* Area);

void h_totem_cuatro(carta* card, Area_de_juego* Area);

void h_totem_cinco(carta* card, Area_de_juego* Area);

void h_totem_seis(carta* card, Area_de_juego* Area);

void h_totem_siete(carta* card, Area_de_juego* Area);


void h_talisman_cuatro(carta* card,Area_de_juego* Area);

void imprimirHabilidadTotem(int habilidad);

void imprimirHabilidadTalisman(int habilidad);

void imprimirHabilidadArma(int habilidad);

void activarHabilidadTalisman(carta* card, int habilidad, Area_de_juego* area);

void activarHabilidadTotem(carta* card, int habilidad, Area_de_juego* area);

void activarHabilidadArma(carta* card, int habilidad, Area_de_juego* area, int valor);

#endif // HABILIDADES_H_INCLUDED
