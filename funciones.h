#ifndef funciones_h
#define funciones_h

typedef struct carta carta;

typedef struct Partida Partida;

typedef struct Area_de_juego Area_de_juego;


int cmp_str_map(const void * key1, const void * key2);

carta * crearCarta(char * linea);

void imprimirTipoCarta(int tipo,carta * card );

char * _strdup (const char *s);

const char* get_csv_field (char * tmp, int i);

Area_de_juego * crearAreaDeJuego();

void imprimirCaracteristicas(carta* card);

bool mostrarYEscoger(carta* card);

void imprimirLista(list* lista, int pagina_actual);

void eleccionDePaginas(int i, int pagina_actual, int paginas);

Map* elegirCartas(HashTable* tablahash, list* lista_todas_las_cartas, int* num);

void reglas();

void creditos();

void imprimirCuadrado();

Area_de_juego* comenzarPartida(HashTable* tabla_hash, list* lista);

void ingresoAreaDeJuego(Area_de_juego* area, carta* card, int zona);

Area_de_juego* buscarPartida(HashTable* tabla);

int menu(HashTable *tabla);

Area_de_juego* jugar(HashTable* table, list* lista);

bool descartarOpciones();

bool opcionesCarta();

void imprimirMapa(Map* mapa);

carta* verMano(Map* mano);

bool eleccionMapa(char tecla, Map * mapa, int* cont);

bool eleccionLista(char tecla, list * lista, int* cont);

void imprimirMenucomenzarJuego(char* nombre);

void analizarYLanzarCarta(carta* card, Area_de_juego* Area);

void verLineaAtaqueEnemigo(Area_de_juego* Area);

void agruparOros(Area_de_juego* Area);

void agruparAliados(Area_de_juego* Area);

void verLineaDeAtaque(Area_de_juego* Area);

void verDestierro(Area_de_juego* Area);

void verLineaDeDefensa(Area_de_juego* Area);

void descartarCarta(Area_de_juego* area);

void Barajar_Mazo(Map *mazo);

void verLineaDeDefensaEnemiga(Area_de_juego *Area);

void verDestierroEnemigo(Area_de_juego *Area);

const char* palabraQueSeImprimira(char* palabra, char * nombre_jugador,char* nombre_carta ,char lugar);

void escribirEnArchivoCSV(Area_de_juego* area, FILE* archivo);

void guardarPartida(Area_de_juego* area);

void comenzarJuego(Area_de_juego* Area_final);


#endif // FUNCIONES_H_INCLUDED
