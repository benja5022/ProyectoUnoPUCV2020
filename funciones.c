#include "funciones.h"


struct Partida{
    char nombre_partida[50];
    char nombre_Jugador1[50];
    char nombre_Jugador2[50];

};

struct Area_de_juego{
    struct Area_de_juego * area_enemiga;
    char nombre_jugador[100];
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

int cmp_str_map(const void * key1, const void * key2){
    const char * Key1 = key1;
    const char * Key2 = key2;
    if (strcmp(Key1,Key2) == 0) return 1;

    else return 0;

}

carta * crearCarta(char * linea){
    carta * carta_nueva = (carta *) malloc (sizeof(carta));

    strcpy(carta_nueva->id,get_csv_field(linea,2));
    strcpy(carta_nueva->nombre,get_csv_field(linea,3));
    carta_nueva ->tipo = atoi(get_csv_field(linea,4));
    carta_nueva ->habilidad_talisman = atoi(get_csv_field(linea,5));
    carta_nueva ->habilidad_totem = atoi(get_csv_field(linea,6));
    carta_nueva ->habilidad_arma = atoi(get_csv_field(linea,7)) ;
    carta_nueva ->coste = atoi(get_csv_field(linea,8));
    carta_nueva ->fuerza = atoi(get_csv_field(linea,9));

    return carta_nueva;
}

void imprimirTipoCarta(int tipo,carta * card ){

    //printf("Nombre:%s\nCoste:%d\nFuerza:%d\nHabilidad Arma:%d\nTipo:",card -> nombre,card ->coste, card ->fuerza, card ->habilidad_arma);
    switch(tipo){
        case(0):
            printf("Oro\n");
            break;
        case(1):
            printf("Aliado\n");
            break;
        case(2):
            printf("Talisman\n");
            break;
        case(3):
            printf("Arma\n");
            break;
        case(4):
            printf("Totem\n");
            break;
    }
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

Area_de_juego * crearAreaDeJuego(){
    Area_de_juego* Area1 = (Area_de_juego *) malloc (sizeof(Area_de_juego));
    Area1 ->cementerio = createMap(cmp_str_map);
    Area1 ->linea_ataque = createMap(cmp_str_map);
    Area1 ->linea_defensa = createMap(cmp_str_map);
    Area1 ->mano = createMap(cmp_str_map);
    Area1 ->mazo_castillo = createMap(cmp_str_map);
    Area1 ->destierro = list_create_empty();
    Area1 ->linea_de_apoyo = list_create_empty();
    Area1 ->oros = stack_create_empty();
    Area1 ->oro_pagado = 0;
    Area1 ->reserva_de_oro = 0;
    Area1 ->total = 0;

    return Area1;
}

void imprimirCaracteristicas(carta* card){
    printf("Caracteristicas:\n\n");
    printf("Nombre: %s\n",card->nombre);
    printf("Fuerza: %d\n",card->fuerza);
    printf("Coste: %d\n",card->coste);
    printf("ID: %s\n",card->id);
    printf("Tipo: ");
    imprimirTipoCarta(card->tipo,card);
}

bool mostrarYEscoger(carta* card){ // elegirCartas

    imprimirCaracteristicas(card);
    int cont = 9;
    int bandera = 0;
    char tecla;


    printf("\nLa escoges?\n\nSi\nNo");
    gotoxy(1,11);
    while(bandera == 0){
        tecla = getch();
        switch(tecla){
            case('w'):
                if(cont == 9) cont = 10;
                else cont--;
                break;
            case('s'):
                if(cont == 10) cont = 9;
                else cont++;
                break;
            case(13):
                bandera = cont;
                break;
        }
        gotoxy(1,cont+2);
    }
    if(bandera == 9) return true;
    else return false;

}

void imprimirLista(list* lista, int pagina_actual){
    int i;
    carta * current;

    for(i = 0, current = list_first(lista); current != NULL; i++,current = list_next(lista)){
        if(current && i >= ((pagina_actual-1)*23) && i < ((pagina_actual)*23))
        printf("%s\n",current->nombre);
    }

}

void eleccionDePaginas(int i, int pagina_actual, int paginas){
    if(i == 0){
        if(pagina_actual == paginas) printf("Para Ver La siguiente pagina teclea \"a\"");
        else  printf("Para Ver La Pagina Anterior teclea \"a\" Para Ver La siguiente pagina teclea \"d\"");
    }
    else
    {
        if(pagina_actual == 1) printf("Para Ver La siguiente pagina teclea \"d\"");
        else printf("Para Ver La Pagina Anterior teclea \"a\" Para Ver La siguiente pagina teclea \"d\"");
    }

}

list* elegirCartas(HashTable* tablahash, list* lista_todas_las_cartas){
    //*************
    system("cls");
    int newcont = 1;
    int i = 0;
    list* lista_cartas_escogidas= list_create_empty();
    carta* current = list_first(lista_todas_las_cartas);
    carta* aux = NULL;

    int paginas;
    int pagina_actual = 1;

    if(list_size(lista_todas_las_cartas) % 23) paginas = 1 + list_size(lista_todas_las_cartas) / 23;
    else paginas = list_size(lista_todas_las_cartas) / 23;

    printf("Cartas Escogidas: %d     Pagina: %d\\%d\n\n",0,pagina_actual,paginas);

    imprimirLista(lista_todas_las_cartas,pagina_actual);
    eleccionDePaginas(1,pagina_actual,paginas);

    int cartas_escogidas = 0;
    char tecla;

    while(cartas_escogidas < 50 && tecla != 8){
        gotoxy(1,newcont+2);
        tecla = getch();

        switch(tecla){

            case('w'):
                if(newcont == 1) newcont = 23;
                else newcont--;
                break;
            case('s'):
                if(newcont == 23) newcont = 1;
                else newcont++;
                break;

            case('d'):
                if(pagina_actual < paginas) pagina_actual++;
                else break;

                system("cls");
                printf("Cartas Escogidas: %d     Pagina: %d\\%d\n\n", cartas_escogidas,pagina_actual,paginas);
                imprimirLista(lista_todas_las_cartas,pagina_actual);
                eleccionDePaginas(0,pagina_actual,paginas);

                break;
            case('a'):
                if(pagina_actual > 1) pagina_actual--;
                else break;

                system("cls");
                printf("Cartas Escogidas: %d     Pagina: %d\\%d\n\n", cartas_escogidas,pagina_actual,paginas);
                imprimirLista(lista_todas_las_cartas,pagina_actual);
                eleccionDePaginas(1,pagina_actual,paginas);
                break;
            case(8):
                return NULL;
                break;

            case(13):
                system("cls");

                for(i= 0, current=list_first(lista_todas_las_cartas); i <(pagina_actual-1)*23+newcont-1; i++,current = list_next(lista_todas_las_cartas));

                if(mostrarYEscoger(current)){
                    aux = (carta*) malloc (sizeof(carta));
                    aux = current;
                    list_push_front(lista_cartas_escogidas,aux);
                    cartas_escogidas++;
                }
                system("cls");
                printf("Cartas Escogidas: %d\n\n", cartas_escogidas);
                imprimirLista(lista_todas_las_cartas,pagina_actual);
                newcont = 1;
                break;
        }

    }

    return lista_cartas_escogidas;
}

void reglas(){//vacio


}

void creditos(){
    int i;
    int j;
    for(i = 0; i<25; i++){
        for(j=0 ; j< i; j++){
            printf("\n");
        }

        printf("%60s","------Creadores------\n");
        printf("%64s","Matias Ezequiel Osorio Quinones\n");
        printf("%65s","Benjamin Ignacio Rojas Henriquez\n");
        printf("%65s","Gabriel Ignacio Alvarez Quintero\n");
        printf("%62s","Ignacio Cortes Gonzalez \n");
        Sleep(450);
        system("cls");
    }

}

void imprimirCuadrado(){
    gotoxy(42,15);
    printf("%c",201);
    for(int i = 0; i<35; i++) printf("%c",205);
    printf("%c\n",187);
    gotoxy(42,16);
    printf("%c",186);
    for(int i = 0; i<35; i++) printf(" ");
    printf("%c\n",186);
    gotoxy(42,17);
    printf("%c",200);
    for(int i = 0; i<35; i++) printf("%c",205);
    printf("%c",188);

}

Area_de_juego* comenzarPartida(HashTable* tabla_hash, list* lista){//Incompleto
    system("cls");
    char nombrePartida[100];
    char nombre1[100];
    char nombre2[100];

    gotoxy(45,13);
    printf("Ingresa el nombre de la partida\n");
    imprimirCuadrado();
    gotoxy(43,16);
    scanf("%99[^\n]s",nombrePartida);

    getchar();
    gotoxy(42,13);
    printf("Ingresa el nombre del primer jugador\n");
    imprimirCuadrado();
    gotoxy(43,16);
    scanf("%99[^\n]s",nombre1);

    system("cls");

    getchar();
    gotoxy(42,13);
    printf("Ingresa el nombre del Segundo jugador\n");
    imprimirCuadrado();
    gotoxy(43,16);
    scanf("99[^\n]%s",nombre2);

    list* lista1 = elegirCartas(tabla_hash,lista);

    if(lista1 == NULL) return NULL;

    list* lista2 = elegirCartas(tabla_hash,lista);

    if(lista2 == NULL) return NULL;

    return NULL;

}

void ingresoAreaDeJuego(Area_de_juego* area, carta* card, int zona){

    switch(zona){
        case 0:
//            printf("1");
            insertMap(area->cementerio,card->nombre,card);

            break;
        case 1:
  //          printf("2");
            insertMap(area->mazo_castillo,card->nombre,card);
            break;
        case 2:
 //           printf("3");
            insertMap(area->mano,card->nombre,card);
            break;
        case 3:
   //         printf("4");
            stack_push(area->oros,card);
            area->reserva_de_oro++;
            break;
        case 4:
            area->oro_pagado++;
     //       printf("5");
            break;
        case 5:
            insertMap(area->linea_defensa,card->nombre,card);
    //        printf("6");
            break;
        case 6:
            insertMap(area->linea_ataque,card->nombre,card);
     //       printf("7");
            break;
        case 7:
            list_push_back(area->linea_de_apoyo,card);
     //       printf("8");
            break;
        case 8:
            list_push_back(area->linea_de_apoyo,card);
      //      printf("9");
            break;
        case 9:
     //       printf("10");
            break;

        default:
            break;

    }

//    printf("%hu\n",area->total);
    area->total++;

}

Area_de_juego* buscarPartida(HashTable* tabla){
    FILE* partidas = fopen("Partidas\\Partidas.txt","r");
    Partida* punto_de_partida;
    list* lista_de_partidas = list_create_empty();
    char current[150];
    while(fgets(current,100,partidas)){
        punto_de_partida = (Partida*) malloc (sizeof(Partida));

        strcpy(punto_de_partida->nombre_partida,get_csv_field(current,1));
        strcpy(punto_de_partida->nombre_Jugador1,get_csv_field(current,2));
        strcpy(punto_de_partida->nombre_Jugador2,get_csv_field(current,3));

        list_push_back(lista_de_partidas,punto_de_partida);
 //       printf("%s %s %s\n",get_csv_field(current,1),get_csv_field(current,2),get_csv_field(current,3));
 //       printf("%s\n",current);
    }
    fclose(partidas);

    Partida* pcurrent = list_first(lista_de_partidas);
    for(;pcurrent != NULL; pcurrent = list_next(lista_de_partidas)){
        printf("%s\n",pcurrent->nombre_partida);
    }


    //**********
    int i = 0;
    long limite = list_size(lista_de_partidas);
    char tecla;
    int opcion_escogida = -1;
    long newcont = 0;

    while(opcion_escogida == -1){
        system("cls");
        for(i = 0, pcurrent = list_first(lista_de_partidas); i < limite; i++, pcurrent = list_next(lista_de_partidas)){

                if(i == newcont){
                    textbackground(4);
                    printf("%s",pcurrent->nombre_partida);
                    textbackground(0);
                    printf("\n");
                }
                else printf("%s\n",pcurrent->nombre_partida);
        }

        tecla = getch();
        switch(tecla){

            case('w'):
                if(newcont == 0) newcont = limite-1;
                else newcont--;
                break;
            case('s'):
                if(newcont == limite-1) newcont = 0;
                else newcont++;
                break;
            case(13):
                opcion_escogida = newcont;
                break;
            case(8):
                return NULL;
            default:
                break;
        }

    }
    system("cls");
    //*******
    i=0;
    pcurrent = list_first(lista_de_partidas);
    do{
        if(i == opcion_escogida) break;
        i++;
        pcurrent = list_next(lista_de_partidas);

    }while(i < opcion_escogida);
    system("cls");
//    printf("%s\n",pcurrent->nombre_partida);

    char direccion[150] = "Partidas\\";
    strcat(direccion,pcurrent->nombre_partida);
    strcat(direccion,".csv");

    FILE* partida_salvada_escogida = fopen(direccion,"r");
    if(partida_salvada_escogida == NULL) printf("falla\n");

    fgets(current,100,partida_salvada_escogida);


    Area_de_juego* area = crearAreaDeJuego();
    Area_de_juego* area2 = crearAreaDeJuego();

    area ->area_enemiga = area2;
    area2 ->area_enemiga = area;
    strcpy(area ->nombre_jugador,pcurrent ->nombre_Jugador1);
    strcpy(area2->nombre_jugador,pcurrent ->nombre_Jugador2);

    carta* busqueda;
    int zona;

    while(fgets(current,150,partida_salvada_escogida)){
        busqueda = (carta*) malloc (sizeof(carta));
        busqueda = searchHashTable(tabla,get_csv_field(current,3));

        if(busqueda == NULL){
            printf("falla %s\n",current);
        }
        else
        {
            if(strcmp(area->nombre_jugador,get_csv_field(current,2))== 0){
                zona = atoi(get_csv_field(current,4));
                ingresoAreaDeJuego(area,busqueda,zona);

            }
            else
            {
                zona = atoi(get_csv_field(current,4));
                ingresoAreaDeJuego(area2,busqueda,zona);
            }
        }

    }

    fclose(partida_salvada_escogida);

    printf("%ld %ld %ld %ld %ld %ld %ld %ld\n", MapCount(area->mano), list_size(area->destierro), area->reserva_de_oro, MapCount(area->cementerio), MapCount(area->linea_defensa), MapCount(area->mazo_castillo), list_size(area->linea_de_apoyo), area->total);

    return area;
}

int menu(HashTable *tabla){
    char tecla;
    int cont = 1;
    int bandera = 0;

    textbackground(2);
    printf("Jugar\n");
    textbackground(0);
    printf("Reglas\n");
    printf("Creditos\n");

    while(bandera == 0){
        tecla = getch();
        switch(tecla){

            case('w'):
                if(cont == 1) cont = 3;
                else cont--;
                break;

            case('s'):
                if(cont == 3) cont = 1;
                else cont++;
                break;
            case (13):
                bandera = cont;
                cont =0 ;
                break;

            case (8):
                printf("Retroceso\n");
                //cont = 4;
                break;
        }

        system("cls");
        switch(cont){
            case (1):
                textbackground(GREEN);
                printf("Jugar\n");
                textbackground(0);
                printf("Reglas\n");
                printf("Creditos\n");
                break;

            case (2):
                printf("Jugar\n");
                textbackground(GREEN);
                printf("Reglas\n");
                textbackground(0);
                printf("Creditos\n");
                break;
            case (3):
                printf("Jugar\n");
                printf("Reglas\n");
                textbackground(GREEN);
                printf("Creditos\n");
                textbackground(0);
                break;
            default :
                break;
        }
    }

    return bandera;
}

Area_de_juego* jugar(HashTable* table, list* lista){
    Area_de_juego* Area = NULL;
    char tecla;
    int cont = 1;
    int bandera = 0;

    while(bandera == 0 && Area == NULL)
    {
            system("cls");
                switch(cont){

                    case (1):
                        textbackground(2);
                        printf("Cargar Partida\n");
                        textbackground(0);
                        printf("Nueva Partida\n");
                        break;
                    case (2):

                        printf("Cargar Partida\n");
                        textbackground(2);
                        printf("Nueva Partida\n");
                        textbackground(0);
                        break;

                    default :
                        break;
                }

                tecla = getch();

                switch(tecla){

                case('w'):
                    if(cont == 1) cont = 2;
                    else cont--;
                    break;

                case('s'):
                    if(cont == 2) cont = 1;
                    else cont++;
                    break;
                case (13):
                    bandera = cont;
                    cont = 0;
                    break;
                case (8):
                    system("cls");
                    return NULL;
            }

  /** Editar esta funcion importante */
        if(bandera != 0){
            switch(bandera){
                case (1):
                    Area = buscarPartida(table);
                    break;
                case (2):
                    Area = comenzarPartida(table,lista);
                    break;
            }
            bandera = 0;
            cont = 1;
        }
    }
    return Area;
}

bool opcionesCarta(){

    gotoxy(1,9);
    printf("Lanzar Volver\n");

    char tecla;
    unsigned short cont = 1;
    unsigned short bandera = 0;

    while(bandera == 0){
        if(cont == 1) gotoxy(cont,9);
        else gotoxy(cont + 6 , 9);

        tecla = getch();
        switch(tecla){
            case ('a'):
                if(cont == 1) cont = 2;
                else cont--;
                break;
            case ('d'):
                if(cont == 2) cont = 1;
                else cont++;
                break;

            case (13):
                bandera = cont;
                break;

        }
    }

    if(bandera == 1){
        return true;
    }
    else return false;
}

carta* verMano(Map* mano){
    system("cls");
    if(MapCount(mano) == 0){
        printf("No tienes Cartas");
        return NULL;
    }

    carta* current = firstMap(mano);
    printf("\n");
    for(;current != NULL;current = nextMap(mano)) printf("%s\n",current->nombre);

    unsigned short i;
    unsigned short cont = 1;
    char tecla;
    unsigned short bandera = 0;


    while(bandera == 0){
        gotoxy(1,cont+1);

        tecla = getch();

        switch(tecla){
            case ('w'):
                if(cont == 1) cont = MapCount(mano);
                else cont--;

                break;
            case ('s'):
                if(cont == MapCount(mano)) cont = 1;
                else cont++;
                break;
            case (13):
                for(i = 0, current = firstMap(mano); i < cont-1 ; i++,current = nextMap(mano));

                system("cls");
                imprimirCaracteristicas(current);
                if(opcionesCarta()) return current;

                system("cls");
                printf("\n");
                for(current = firstMap(mano);current != NULL;current = nextMap(mano)) printf("%s\n",current->nombre);
                break;
            case (8):
                return NULL;
                break;
        }
    }

    return NULL;
}

void imprimirMenucomenzarJuego(){
    system("cls");
    printf("\nVer Mano\n");
    printf("Agrupar Oros\n");
    printf("Agrupar aliados\n");
    printf("Ver destierro\n");
    printf("Ver destierro enemigo\n");
    printf("Ver linea de ataque\n");
    printf("Ver linea de ataque enemiga\n");
    printf("Ver linea de defensa\n");
    printf("Ver linea de defensa enemiga\n");
    printf("Terminar turno\n");
    printf("Salir y guardar\n");
}

void analizarYLanzarCarta(carta* card){ // incompleto
    unsigned short tipo = card -> tipo;

    printf("que sucede\n");
    imprimirTipoCarta(tipo,card);

}

void comenzarJuego(Area_de_juego* Area_final){

    imprimirMenucomenzarJuego();

    char tecla;
    unsigned short bandera = 0;
    unsigned short cont = 1;
    carta* cartaJugada = NULL;

    do{
        while(bandera == 0){
            gotoxy(1,cont+1);

            tecla = getch();

            switch(tecla){

                case('w'):
                    if(cont == 1) cont = 11;
                    else cont--;

                    break;
                case('s'):
                    if(cont == 11) cont = 1;
                    else cont++;

                    break;
                case(13):
                    bandera = cont;
                    break;
            }
        }

        switch(bandera){
            case 1:
                cartaJugada = verMano(Area_final->mano);

                if(cartaJugada) analizarYLanzarCarta(cartaJugada);

                bandera = 0;
                break;
            case 2:
                bandera = 0;
                break;
            case 3:
                bandera = 0;
                break;
            case 4:
                bandera = 0;
                break;
            case 5:
                bandera = 0;
                break;
            case 6:
                bandera = 0;
                break;
            case 7:
                bandera = 0;
                break;
            case 8:
                bandera = 0;
                break;
            case 9:
                bandera = 0;
                break;
            case 10:

                break;
            case 11:
                bandera = 0;
                break;

        }

        imprimirMenucomenzarJuego();

    }while(bandera != 10);


}
