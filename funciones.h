#ifndef funciones_h
#define funciones_h

typedef struct carta carta;

typedef struct Area_de_juego Area_de_juego;

typedef struct Partida Partida;

carta * crearCarta(char * linea);


char * _strdup (const char *s);

const char* get_csv_field (char * tmp, int i);

void reglas();

void creditos();

void menu(HashTable* hash);

void empezarJuego(HashTable* hash);

void buscarPartida(HashTable* hash);

void ingresoAreaDeJuego(Area_de_juego* area, carta* card, int zona);

int cmp_str_map(const void * key1, const void * key2);

Area_de_juego * crearAreaDeJuego(); //Area_de_juego * crearAreaDeJuego()

#endif // FUNCIONES_H_INCLUDED
