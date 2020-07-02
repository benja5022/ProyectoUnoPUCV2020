#ifndef funciones_h
#define funciones_h

typedef struct carta carta;

carta * crearCarta(char * linea);

char * _strdup (const char *s);

const char* get_csv_field (char * tmp, int i);

void reglas();

void creditos();

void menu();

void empezarJuego();

#endif // FUNCIONES_H_INCLUDED
