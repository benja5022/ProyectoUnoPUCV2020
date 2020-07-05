#ifndef funciones_h
#define funciones_h
typedef struct Partida Partida;

typedef struct Area_de_juego Area_de_juego;

typedef struct carta carta;

carta * crearCarta(char * linea);

char * _strdup (const char *s);

const char* get_csv_field (char * tmp, int i);

void reglas();

void creditos();

int menu(HashTable* hash);

list* elegirCartas(HashTable* tablahash, list* lista_todas_las_cartas);

Area_de_juego* Jugar(HashTable* hash, list* lista);

Area_de_juego* buscarPartida(HashTable* hash);

void ingresoAreaDeJuego(Area_de_juego* area, carta* card, int zona);

int cmp_str_map(const void * key1, const void * key2);

Area_de_juego * crearAreaDeJuego(); //Area_de_juego * crearAreaDeJuego()

void imprimirMenucomenzarJuego();

void comenzarJuego(Area_de_juego* Area_final);



#endif // FUNCIONES_H_INCLUDED
