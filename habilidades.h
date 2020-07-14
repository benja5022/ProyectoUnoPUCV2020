#ifndef HABILIDADES_H
#define HABILIDADES_H

typedef struct carta carta;

typedef struct Partida Partida;

typedef struct Area_de_juego Area_de_juego;

void h_totem_cero(carta* card, Area_de_juego* Area);

void h_totem_uno(carta* card, Area_de_juego* Area);

void h_totem_dos(carta* card);

void h_totem_tres(carta* card);

void h_totem_cuatro(carta* card);

void h_totem_cinco(carta* card);

void h_totem_seis(carta* card, Area_de_juego* Area);

void h_totem_siete(carta* card, Area_de_juego* Area);


void h_talisman_cuatro(carta* card,Area_de_juego* Area);

void imprimirHabilidadTotem(int habilidad);

void imprimirHabilidadTalisman(int habilidad);

void imprimirHabilidadArma(int habilidad);

#endif // HABILIDADES_H_INCLUDED
