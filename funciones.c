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

    strcpy(carta_nueva->nombre,get_csv_field(linea,3));
    carta_nueva ->tipo = atoi(get_csv_field(linea,4));
    carta_nueva ->habilidad_talisman = atoi(get_csv_field(linea,5));
    carta_nueva ->habilidad_totem = atoi(get_csv_field(linea,6));
    carta_nueva ->habilidad_arma = atoi(get_csv_field(linea,7)) ;
    carta_nueva ->coste = atoi(get_csv_field(linea,8));
    carta_nueva ->fuerza = atoi(get_csv_field(linea,9));

/*
    printf("Nombre:%s\nCoste:%d\nFuerza:%d\nHabilidad Arma:%d\nTipo:",carta_nueva -> nombre,carta_nueva ->coste, carta_nueva ->fuerza, carta_nueva ->habilidad_arma);
    switch(carta_nueva ->tipo){
        case(0):
            printf("Oro\n\n");
            break;
        case(1):
            printf("Aliado\n\n");
            break;
        case(2):
            printf("Talisman\n\n");
            break;
        case(3):
            printf("Arma\n\n");
            break;
        case(4):
            printf("Totem\n\n");
            break;
    }*/
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

void reglas(){//vacio


}

void creditos(){
    int i;
    int j;
    for(i = 0; i<30; i++){
        for(j=0 ; j< i; j++){
            printf("\n");
        }

        printf("       ------Creadores------\n");
        printf("           Matias Osorio\n");
        printf("   Benjamin Ignacio Rojas Henriquez\n");
        printf("   Gabriel Ignacio Alvarez Quintero\n");
        printf("      Ignacio Cortes Gonzalez \n");
        Sleep(550);
        system("cls");
    }

}

void comenzarPartida(){//vacio

}

Area_de_juego * crearAreaDeJuego(){// Nombre, //Area_de_juego * crearAreaDeJuego()
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

    Area_de_juego* Area2 = (Area_de_juego *) malloc (sizeof(Area_de_juego));
    Area2 ->cementerio = createMap(cmp_str_map);
    Area2 ->linea_ataque = createMap(cmp_str_map);
    Area2 ->linea_defensa = createMap(cmp_str_map);
    Area2 ->mano = createMap(cmp_str_map);
    Area2 ->mazo_castillo = createMap(cmp_str_map);
    Area2 ->destierro = list_create_empty();
    Area2 ->linea_de_apoyo = list_create_empty();
    Area2 ->oros = stack_create_empty();
    Area2 ->oro_pagado = 0;
    Area2 ->reserva_de_oro = 0;
    Area2 ->total = 0;

    Area1 ->area_enemiga = Area2;
    Area2 ->area_enemiga = Area1;

    return Area1;
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

void buscarPartida(HashTable* tabla){//Incompleta
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
    strcpy(area ->nombre_jugador,pcurrent ->nombre_Jugador1);
    strcpy(area ->area_enemiga ->nombre_jugador,pcurrent ->nombre_Jugador2);

//    printf("%ld\n", MapCount(area->mano));


//   printf("nombres pepegrillo:%s %s\n",area ->nombre_jugador,area ->area_enemiga ->nombre_jugador);



    carta* busqueda;
    int zona;
    /** Aqui falta*/
    while(fgets(current,150,partida_salvada_escogida)){
        busqueda = (carta*) malloc (sizeof(carta));
        busqueda = searchHashTable(tabla,get_csv_field(current,3));

        if(busqueda == NULL){
            printf("falla %s\n",current);
        }
        else
        {
//            printf("->%s \n",current);
            if(strcmp(area->nombre_jugador,get_csv_field(current,2))== 0){
                zona = atoi(get_csv_field(current,4));
//                printf("%s %s %d\n",area->nombre_jugador,get_csv_field(current,2),zona);
//                printf("%s %x\n",busqueda->nombre, &busqueda);
                ingresoAreaDeJuego(area,busqueda,zona);

            }
            else
            {
                zona = atoi(get_csv_field(current,4));
//                printf("%s %s %d\n",area->area_enemiga->nombre_jugador,get_csv_field(current,2),zona);
//                printf("%s %x\n",busqueda->nombre, &busqueda);
                ingresoAreaDeJuego(area->area_enemiga,busqueda,zona);
            }
        }
//        printf("%s\n",current);

    }

    fclose(partida_salvada_escogida);

    printf("%ld %ld %ld %ld %ld %ld %ld %ld\n", MapCount(area->mano), list_size(area->destierro), area->reserva_de_oro, MapCount(area->cementerio), MapCount(area->linea_defensa), MapCount(area->mazo_castillo), list_size(area->linea_de_apoyo), area->total);
}

void menu(HashTable *tabla){
    char tecla;
    int cont = 1;
    int bandera = 0;

    textbackground(2);
    printf("Empezar Juego\n");
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
                printf("Empezar Juego\n");
                textbackground(0);
                printf("Reglas\n");
                printf("Creditos\n");
                break;

            case (2):
                printf("Empezar Juego\n");
                textbackground(GREEN);
                printf("Reglas\n");
                textbackground(0);
                printf("Creditos\n");
                break;
            case (3):
                printf("Empezar Juego\n");
                printf("Reglas\n");
                textbackground(GREEN);
                printf("Creditos\n");
                textbackground(0);
                break;
            default :
                break;
        }
    }

    switch(bandera){
        case(1):
            empezarJuego(tabla);
            break;

        case(2):
            reglas();
            break;

        case(3):
            creditos();
            break;
    }

}

void empezarJuego(HashTable* table){

    char tecla;
    int cont = 1;
    int bandera = 0;
    system("cls");

    textbackground(2);
    printf("Cargar Partida\n");
    textbackground(0);
    printf("Nueva Partida\n");

    while(bandera == 0){

        tecla = getch();
        system("cls");
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

        }
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


    }
  /** Editar esta funcion importante */
    switch(bandera){
        case (1):
            buscarPartida(table);
            break;
        case (2):
            comenzarPartida();
            break;
    }
    printf("Empezar juego opcion %d\n", bandera);
}
