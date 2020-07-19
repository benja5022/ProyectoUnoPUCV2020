#ifndef funciones_h
#define funciones_h

typedef struct regla regla;

void reglas();

regla* crear_reglas (char* nombre);

void creditos();

int cmp_str_map(const void * key1, const void * key2);

void logo();

carta * crearCarta(char * linea);

void imprimirTipoCarta(int tipo,carta * card );

char * _strdup (const char *s);

const char* get_csv_field (char * tmp, int i);

Area_de_juego * crearAreaDeJuego();

void imprimirCaracteristicas(carta* card, carta* card2);

bool mostrarYEscoger(carta* card);

void imprimirLista(list* lista, int pagina_actual);

void eleccionDePaginas(int i, int pagina_actual, int paginas);

Map* elegirCartas(HashTable* tablahash, list* lista_todas_las_cartas, int* num);

void imprimirCuadrado();

Area_de_juego* comenzarPartida(HashTable* tabla_hash, list* lista);

void ingresoAreaDeJuego(Area_de_juego* area, carta* card, int zona, char* nombre_aliado, int posicion_aliado);

Area_de_juego* buscarPartida(HashTable* tabla);

int menu(HashTable *tabla);

Area_de_juego* jugar(HashTable* table, list* lista);

bool descartarOpciones();

bool opcionesCarta(int num);

void imprimirMapa(Map* mapa);

carta* verMano(Map* mano, int i);

carta* eleccionMapa(char tecla, Map * mapa, int* cont, int modo);

carta* eleccionLista(char tecla, list * lista, int* cont, int modo);

void imprimirMenucomenzarJuego(char* nombre, int oros_disponibles);

void analizarYLanzarCarta(carta* card, Area_de_juego* Area);

void descartarCarta(Area_de_juego* area, int modo);

void Barajar_Mazo(Map *mazo);

const char* palabraQueSeImprimira(char* palabra, char * nombre_jugador,char* nombre_carta ,char lugar);

void escribirEnArchivoCSV(Area_de_juego* area, FILE* archivo, HashTable* hash);

void eliminarAliado(Map* linea,carta* card,Map* cementerio);

void moverAliadoDeLugar(Map* mapa1, carta* card, Map* mapa2);

bool verificarMuerteDeAliado(carta* card,Area_de_juego* area);

void restaurarAliados(Map* Cementerio, HashTable* tabla);

void imprimirJugadorGanador(char* nombre_jugador);

bool destruccionAliadoAtacantexTalisman(Area_de_juego* area, carta* carta_enemiga, carta* defensa);
#endif // funciones_h_INCLUDED
