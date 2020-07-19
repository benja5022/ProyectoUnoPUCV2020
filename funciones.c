#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <conio.h>
#include <ctype.h>
#include <windows.h>
#include "HashTable.h"
#include "stack.h"
#include "list.h"
#include "Map.h"
#include "habilidades.h"
#include "funciones.h"
#include "funcionesdejuego.h"


struct regla{
char* nombre;
};

int cmp_str_map(const void * key1, const void * key2){
    const char * Key1 = key1;
    const char * Key2 = key2;
    if (strcmp(Key1,Key2) == 0) return 1;

    else return 0;

}

carta * crearCarta(char * linea){
    carta * carta_nueva = (carta *) malloc (sizeof(carta));

    strcpy(carta_nueva->nombre,get_csv_field(linea,2));
    carta_nueva -> tipo = atoi(get_csv_field(linea,3));
    carta_nueva -> habilidad_talisman = atoi(get_csv_field(linea,4));
    carta_nueva -> habilidad_totem = atoi(get_csv_field(linea,5));
    carta_nueva -> habilidad_arma = atoi(get_csv_field(linea,6)) ;
    carta_nueva -> coste = atoi(get_csv_field(linea,7));
    carta_nueva -> fuerza = atoi(get_csv_field(linea,8));
    carta_nueva -> arma = NULL;
    carta_nueva -> estado = false;

    return carta_nueva;
}

void imprimirTipoCarta(int tipo,carta * card ){

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
    for (tok = strtok (line, ","); tok && *tok; tok = strtok (NULL, ",\n")) {
        if (!--i) {
            return tok;
        }
    }
    return NULL;
}

Area_de_juego * crearAreaDeJuego(){

    Area_de_juego* Area = (Area_de_juego *) malloc (sizeof(Area_de_juego));
    Area ->cementerio = createMap(cmp_str_map);
    Area ->linea_ataque = createMap(cmp_str_map);
    Area ->linea_defensa = createMap(cmp_str_map);
    Area ->mano = createMap(cmp_str_map);
    Area ->mazo_castillo = createMap(cmp_str_map);
    Area ->destierro = list_create_empty();
    Area ->linea_de_apoyo = list_create_empty();
    Area ->oros = stack_create_empty();
    Area ->oro_pagado = 0;
    Area ->reserva_de_oro = 0;
    Area ->total = 0;

    return Area;
}

void logo(){
    gotoxy(41,10);
    printf("%38s","BIENVENIDOS A MITOS & LEYENDAS  \n\n");
//    char tecla;
    printf("%65s","INSTRUCCIONES\n");
    printf("%70s","W,A,D y S para moverse\n");
    printf("%71s","ENTER para selecionar\n\n");
    system("pause");
//    printf("%78s","presione cualquier boton para comenzar\n");
//    tecla = getch();
}

void imprimirCaracteristicas(carta* card, carta* arma){

    int tipo = card->tipo;

    printf("Caracteristicas:\n\n");
    printf("Nombre: %s\n",card->nombre);
    printf("Fuerza: %d\n",card->fuerza);
    printf("Coste: %d\n",card->coste);
    printf("Tipo: ");

    switch(tipo){
        case(0):
            imprimirTipoCarta(card->tipo,card);
            printf("Habilidad: No");
            break;
        case(1):

            imprimirTipoCarta(card->tipo,card);
            printf("Habilidad: No\n");

            if(arma)
            {
                printf("Arma: %s\n",card->arma->nombre);
                gotoxy(40,1);
                printf("Caracteristicas del Arma:");
                gotoxy(40,3);
                printf("Nombre: %s\n",arma->nombre);
                gotoxy(40,4);
                printf("Fuerza: %d\n",arma->fuerza);
                gotoxy(40,5);
                printf("Coste: %d\n",arma->coste);
                gotoxy(40,6);
                printf("Habilidad: ");
                imprimirHabilidadArma(arma->habilidad_arma);
            }
            else
            {
                if(card->tipo == 1) printf("\nArma: No\n");
            }
            break;
        case(2):

            imprimirTipoCarta(card->tipo,card);
            printf("Habilidad: ");
            imprimirHabilidadTalisman(card->habilidad_talisman);
            break;
        case(3):

            imprimirTipoCarta(card->tipo,card);
            printf("Habilidad: ");
            imprimirHabilidadArma(card->habilidad_arma);
            break;
        case(4):
            imprimirTipoCarta(card->tipo,card);
            printf("Habilidad: ");
            imprimirHabilidadTotem(card->habilidad_totem);
            break;


    }

    gotoxy(1,20);

}

bool mostrarYEscoger(carta* card){ // elegirCartas

    imprimirCaracteristicas(card,card->arma);
    int cont = 9;
    int bandera = 0;
    char tecla;

    gotoxy(1,9);

    printf("%cLa escoges?",168);
    gotoxy(1,13);
    printf("Si\nNo");
    while(bandera == 0){
        gotoxy(1,cont+4);
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
            case(8):
                return false;
                break;

        }
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

Map* elegirCartas(HashTable* tablahash, list* lista_todas_las_cartas,int* cont){

    system("cls");
    int newcont = 1;
    int i = 0;
    Map* lista_cartas_escogidas= createMap(cmp_str_map);
    carta* current = list_first(lista_todas_las_cartas);
    carta* aux = NULL;

    int paginas;
    int pagina_actual = 1;

    carta* carta_bandera = list_pop_back(lista_todas_las_cartas);


    if(list_size(lista_todas_las_cartas) % 23) paginas = 1 + list_size(lista_todas_las_cartas) / 23;
    else paginas = list_size(lista_todas_las_cartas) / 23;

    int cantCarxpag = 23;

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

                if(newcont == 1) newcont = cantCarxpag;
                else newcont--;

                break;
            case('s'):

                if(newcont == cantCarxpag) newcont = 1;
                else newcont++;

                break;

            case('d'):


                if(pagina_actual < paginas) pagina_actual++;
                else break;

                if(pagina_actual * 23 > list_size(lista_todas_las_cartas)){

                    cantCarxpag = list_size(lista_todas_las_cartas) - (pagina_actual-1) * 23;
                    if(newcont > cantCarxpag){
                        newcont = cantCarxpag;
                    }
                }
                else cantCarxpag = 23;

                system("cls");
                printf("%d",cantCarxpag);
                printf("Cartas Escogidas: %d     Pagina: %d\\%d\n\n", cartas_escogidas,pagina_actual,paginas);
                imprimirLista(lista_todas_las_cartas,pagina_actual);
                eleccionDePaginas(0,pagina_actual,paginas);

                break;
            case('a'):


                if(pagina_actual > 1) pagina_actual--;
                else break;

                if(pagina_actual * 23 > list_size(lista_todas_las_cartas)){

                    cantCarxpag = list_size(lista_todas_las_cartas) - (pagina_actual-1) * 23;
                    if(newcont > cantCarxpag){
                        newcont = cantCarxpag;
                    }
                }
                else cantCarxpag = 23;

                system("cls");
                printf("Cartas Escogidas: %d     Pagina: %d\\%d\n\n", cartas_escogidas,pagina_actual,paginas);
                imprimirLista(lista_todas_las_cartas,pagina_actual);
                eleccionDePaginas(1,pagina_actual,paginas);
                break;
            case(8):
                list_push_back(lista_todas_las_cartas,carta_bandera);
                return NULL;
                break;

            case(13):
                system("cls");

                for(i= 0, current=list_first(lista_todas_las_cartas); i <(pagina_actual-1)*23+newcont-1; i++,current = list_next(lista_todas_las_cartas));

                if(mostrarYEscoger(current)){
                    aux = (carta*) malloc (sizeof(carta));
                    aux = current;
                    (*cont)++;
                    insertMap(lista_cartas_escogidas,aux->nombre,aux);
                    cartas_escogidas++;
                }
                system("cls");
                printf("Cartas Escogidas: %d\n\n", cartas_escogidas);
                imprimirLista(lista_todas_las_cartas,pagina_actual);
                break;
        }

    }
    list_push_back(lista_todas_las_cartas,carta_bandera);
    return lista_cartas_escogidas;
}

void reglas(){


    list* reglamento = list_create_empty();
    FILE* reglamentos = fopen ("Instrucciones//reglas.csv","r");
    char linea [1000];
    char tecla;
    int cont = 0;
    if(reglamento == NULL){
        printf("NO");
        system("pause");
    }

    while (fgets (linea,1000, reglamentos)){
        char* nombre;
        nombre = get_csv_field(linea,1);
        regla *r = crear_reglas(nombre);
        list_push_back(reglamento,r);
    }

    system("cls");

    regla*aux = list_first(reglamento);

    while(aux!=NULL){

        FILE *fp = fopen(aux->nombre,"r");
        char line[1024];

        while(fgets(line , 1024 , fp)){

        printf("%s\n" , line);

    }

        printf("\n| presione d para continuar | a para retroceder | retroceso para salir |\n");

        tecla = getch();

        if(tecla=='d' && cont!=6){
            aux=list_next(reglamento);
            cont++;
        }

        if(tecla=='a' && cont!=0){
            aux=list_prev(reglamento);
            cont--;
        }

        if(tecla==8){
            system("cls");
            return;
        }


        system("cls");
    }

}

regla* crear_reglas (char* nombre){

    regla *r = malloc (sizeof(regla));
    r->nombre= nombre;
    return r;

}

void creditos(){
        system("cls");
        printf("%60s","------Creadores------\n");
        printf("%65s","Benjamin Ignacio Rojas Henriquez\n");
        printf("%64s","Matias Ezequiel Osorio Quinones\n");
        printf("%65s","Gabriel Ignacio Alvarez Quintero\n");
        printf("%62s","Ignacio Cortes Gonzalez \n\n\n");
        system("pause");
        system("cls");
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

Area_de_juego* comenzarPartida(HashTable* tabla_hash, list* lista){
    system("cls");
    char nombrePartida[100];
    char nombre1[100];
    char nombre2[100];

    int cont=0;
    int cont2 =0;

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

    gotoxy(42,13);
    printf("Ingresa el nombre del Segundo jugador\n");
    imprimirCuadrado();
    gotoxy(43,16);
    getchar();
    scanf("%99[^\n]s",nombre2);

    printf("%s %s %s\n",nombrePartida,nombre1,nombre2);
    system("pause");

    Map* lista1 = elegirCartas(tabla_hash,lista,&cont);
    getchar();
    if(lista1 == NULL) return NULL;

    Barajar_Mazo(lista1);

    Map* lista2 = elegirCartas(tabla_hash,lista,&cont2);

    if(lista2 == NULL) return NULL;

    Barajar_Mazo(lista2);

    Area_de_juego* Area1 = crearAreaDeJuego();
    Area_de_juego* Area2 = crearAreaDeJuego();

    strcpy(Area1->nombre_jugador,nombre1);
    strcpy(Area2->nombre_jugador,nombre2);

    strcpy(Area1->nombre_partida,nombrePartida);
    strcpy(Area2->nombre_partida,nombrePartida);

    Area1 ->area_enemiga = Area2;
    Area2 ->area_enemiga = Area1;

    carta* current = NULL;

    Area1 ->mazo_castillo = lista1;
    Area2 ->mazo_castillo = lista2;

    for(current = firstMap(Area1->mazo_castillo); current; current = nextMap(Area1->mazo_castillo))
    {
        if(current->tipo == 0) break;
    }

    stack_push(Area1->oros,current);
    eraseMap(Area1->mazo_castillo,current->nombre);

    for(current = firstMap(Area2->mazo_castillo); current; current = nextMap(Area2->mazo_castillo))
    {
        if(current->tipo == 0) break;
    }

    stack_push(Area2->oros,current);
    eraseMap(Area2->mazo_castillo,current->nombre);

    Area1 ->reserva_de_oro++;
    Area2 ->reserva_de_oro++;

    int i;

    current = firstMap(Area1->mazo_castillo);

    for(i=0 ; i<8; i++){

        insertMap(Area1->mano, current->nombre,current);
        current = nextMap(Area1->mazo_castillo);
    }

    for(current = firstMap(Area1->mano);current; current = nextMap(Area1->mano)) eraseMap(Area1->mazo_castillo,current->nombre);

    current = firstMap(Area2->mazo_castillo);

    for(i=0 ; i<8; i++){

        insertMap(Area2->mano, current->nombre,current);
        current = nextMap(Area2->mazo_castillo);
    }

    for(current = firstMap(Area2->mano);current; current = nextMap(Area2->mano)) eraseMap(Area2->mazo_castillo,current->nombre);

    Area1->total = cont;
    Area2->total = cont2;

    FILE* archivo_de_texto = fopen("Partidas\\Partidas.txt","r+");
    if(archivo_de_texto == NULL){
        printf("Falla\n");
    }
    else
    {
        char linea[500];
        char palabra_completa[500];
        strcpy(palabra_completa,"\n");
        strcat(palabra_completa,nombrePartida);
        strcat(palabra_completa,",");
        strcat(palabra_completa,nombre1);
        strcat(palabra_completa,",");
        strcat(palabra_completa,nombre2);

        while(fgets(linea,500,archivo_de_texto)){
            continue;
        }

        fprintf(archivo_de_texto,palabra_completa);
    }

    fclose(archivo_de_texto);

    return Area1;

}

void ingresoAreaDeJuego(Area_de_juego* area, carta* card, int zona, char* nombre_aliado, int posicion_aliado){

    carta* carta_duena = NULL;

    switch(zona){
        case 0:
            insertMap(area->cementerio,card->nombre,card);

            break;
        case 1:
            insertMap(area->mazo_castillo,card->nombre,card);
            break;

        case 2:
            insertMap(area->mano,card->nombre,card);
            break;

        case 3:
            stack_push(area->oros,card);
            area->reserva_de_oro++;
            break;

        case 4:
            stack_push(area->oros,card);
            area->oro_pagado++;
            break;

        case 5:
            insertMap(area->linea_defensa,card->nombre,card);
            break;

        case 6:
            card->estado= true;
            insertMap(area->linea_ataque,card->nombre,card);
            break;

        case 7:
            list_push_back(area->linea_de_apoyo,card);
            break;

        case 8:
            list_push_back(area->destierro,card);
            break;

        case 9:

            if(posicion_aliado == 5){
                carta_duena = searchMap(area->linea_defensa,nombre_aliado);
            }
            else
            {
                carta_duena = searchMap(area->linea_ataque,nombre_aliado);
            }
            if(carta_duena == NULL){
                printf("carta duena no existe %s\n",nombre_aliado);
                system("pause");
            }
            else{
                carta_duena->arma = card;
                card->arma = carta_duena;
            }

            break;

        case(10):
            insertMap(area->mazo_castillo,card->nombre,card);
            break;

        default:
            break;

    }

    area->total++;

}

int menu(HashTable *tabla){
    char tecla;
    int cont = 1;
    int bandera = 0;
    system("cls");
    printf("Jugar\n");
    printf("Reglas\n");
    printf("Creditos\n");
    printf("Salir del Juego\n");
    gotoxy(1,20);

    while(bandera == 0){
        gotoxy(1,cont);
        tecla = getch();
        switch(tecla){

            case('w'):
                if(cont == 1) cont = 4;
                else cont--;
                break;

            case('s'):
                if(cont == 4) cont = 1;
                else cont++;
                break;
            case (13):
                bandera = cont;
                cont =0 ;
                break;

            case (8):
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

    system("cls");
    printf("Cargar Partida\n");
    printf("Nueva Partida\n");

    while(bandera == 0 && Area == NULL)
    {
        gotoxy(1,cont);

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
            if(Area == NULL){
                system("cls");
                printf("Cargar Partida\n");
                printf("Nueva Partida\n");
            }
        }
    }
    return Area;
}

bool descartarOpciones(){

    gotoxy(1,9);
    printf("Descartar Volver\n");

    char tecla;
    unsigned short cont = 1;
    unsigned short bandera = 0;

    while(bandera == 0){
        if(cont == 1) gotoxy(cont,9);
        else gotoxy(cont + 9 , 9);

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
            case (8):
                return false;
                break;

        }
    }

    if(bandera == 1){
        return true;
    }
    else return false;

}

bool opcionesCarta(int num){

    gotoxy(1,9);

    switch(num){
        case (0):
            printf("Lanzar Volver\n");
            break;
        case (1):
            printf("Activar Volver\n");
            break;
        case (2):
            printf("Atacar/Defender Volver Activar Habilidad de la Arma");
            break;
        case (3):
            printf("Atacar Volver\n");
            break;
        case (4):
            printf("Defender Volver\n");
            break;
        case (5):
            printf("Elegir Volver\n");
            break;
    }

    char tecla;
    unsigned short cont = 1;
    unsigned short bandera = 0;

    while(bandera == 0){

        if(cont == 1) gotoxy(cont,9);
        else
        {
            if((num == 0 || num == 3 || num == 5)) gotoxy(cont + 5 , 9);

            if(num == 1 || num == 4) gotoxy(cont + 7 , 9);
        }

        tecla = getch();
        switch(tecla){
            case ('a'):
                if(num != 2 && cont == 1) cont = 2;
                else cont--;

                if(num == 2 && cont == 1) cont = 3;
                else cont--;
                break;
            case ('d'):
                if(num != 2 && cont == 2) cont = 1;
                else cont++;

                if(num == 2 && cont == 3) cont = 1;
                else cont++;
                break;

            case (13):
                bandera = cont;
                break;
            case (8):
                return false;
                break;

        }
    }
    if(bandera == 1){
        return true;
    }
    else return false;
}

void imprimirMapa(Map* mapa){
    carta* current;
    for(current = firstMap(mapa);current != NULL ; current = nextMap(mapa)) printf("%s\n",current->nombre);
}

carta* eleccionMapa(char tecla, Map * mapa, int* cont, int modo){
        carta* current = NULL;
        unsigned short i;
        switch(tecla){
            case ('w'):
                if((*cont) == 1) *cont = MapCount(mapa);
                else (*cont)--;

                break;
            case ('s'):
                if((*cont) == MapCount(mapa)) (*cont) = 1;
                else (*cont)++;
                break;
            case (13):

                for(i = 0, current = firstMap(mapa); i < (*cont)-1 ; i++,current = nextMap(mapa));

                system("cls");
                imprimirCaracteristicas(current,current->arma);

                if(modo == 0){
                    system("pause");
                    system("cls");
                    printf("\n");
                }else
                {
                    if(opcionesCarta(5)){
                        return current;
                    }
                    system("cls");
                    printf("\n");
                }

                imprimirMapa(mapa);
                break;
            case (8):
                (*cont) = -1;
                return NULL;
                break;
        }
        return NULL;
}

carta* eleccionLista(char tecla, list * lista, int* cont, int modo){
    int i;
    carta* current = NULL;
        switch(tecla){
            case ('w'):
                if((*cont) == 1) (*cont) = list_size(lista);
                else (*cont)--;

                break;
            case ('s'):
                if((*cont) == list_size(lista)) (*cont) = 1;
                else (*cont)++;
                break;
            case (13):
                for(i = 0, current = list_first(lista); i < (*cont)-1 ; i++,current = list_next(lista));
                system("cls");
                imprimirCaracteristicas(current,current->arma);
                if(modo != 0){
                    if(opcionesCarta(5)){
                        return current;
                    }
                }
                printf("\n\n\n\n");
                system("pause");
                system("cls");
                printf("\n");
                for(current = list_first(lista); current; current = list_next(lista)) printf("%s\n",current->nombre);
                break;
            case (8):
                (* cont) = -1;
                return NULL;
                break;
        }
    return NULL;

}

void imprimirMenucomenzarJuego(char* nombre, int oros_disponibles){
    system("cls");
    printf("%45s%s      Oros Disponibles: %d","Nombre Jugador:",nombre,oros_disponibles);
    printf("\nVer Mano\n");//1
    printf("Agrupar Oros\n");//2
    printf("Agrupar aliados\n");//3
    printf("Ver destierro\n");//4
    printf("Ver destierro enemigo\n");//5
    printf("Ver linea de ataque\n");//6
    printf("Ver linea de ataque enemiga\n");//7
    printf("Ver linea de defensa\n");//8
    printf("Ver linea de defensa enemiga\n");//9
    printf("Ver Totems\n");//11
    printf("Ver Totems Enemigos\n");//12
    printf("Terminar turno\n");//12
    printf("Salir y guardar\n");//13
}

bool escogerAliado(Map* linea_defensa, carta* card){
    carta* current= NULL;// = firstMap(mano);
    system("cls");
    printf("\n");
    imprimirMapa(linea_defensa);

    int cont = 1;
    char tecla;
    unsigned short bandera = 0;
    int i = 0;

    while(bandera == 0){

        gotoxy(1,cont+1);

        tecla = getch();
        switch(tecla){
            case('w'):
                if(cont == 1) cont = MapCount(linea_defensa);
                else cont--;
                break;
            case('s'):
                if(cont == MapCount(linea_defensa)) cont = 1;
                else cont++;
                break;
            case(13):
                system("cls");
                for(i = 0, current = firstMap(linea_defensa); i < cont-1 && current;i++, current = nextMap (linea_defensa));

                if(mostrarYEscoger(current)){
                    if(current->arma == NULL){
                        current->arma = card;
                        card->arma = current;
                        return true;
                    }
                    else
                    {
                        system("cls");
                        printf("El aliado Ya tiene un arma\n");
                        system("pause");
                    }
                }
                system("cls");
                printf("\n");
                imprimirMapa(linea_defensa);
                break;
            case(8):
                bandera = 1;
        }
    }
    return false;
}

void analizarYLanzarCarta(carta* card, Area_de_juego* area){
    unsigned short tipo = card -> tipo;


    switch(tipo){
        case(0)://oro
            eraseMap(area->mano,card->nombre);
            stack_push(area->oros,card);
            area->reserva_de_oro++;
            break;
        case(1)://aliado
            if(area->reserva_de_oro >= card->coste){
                area->reserva_de_oro = area->reserva_de_oro - card->coste;
                area->oro_pagado+= card->coste;
                eraseMap(area->mano,card->nombre);
                insertMap(area->linea_defensa,card->nombre,card);
                system("cls");
                printf("Carta Ingresada a la Zona de Defensa\n");
                system("pause");

            }
            else
            {
                system("cls");
                printf("No tienes oros suficientes para jugar esta carta\n");
                system("pause");
            }
            break;
        case(2)://talisman
            if(area->reserva_de_oro >= card->coste){
                area->reserva_de_oro = area->reserva_de_oro - card->coste;
                area->oro_pagado+= card->coste;
                activarHabilidadTalisman(card,card->habilidad_talisman,area);
            }
            else
            {
                system("cls");
                printf("No tienes oros suficientes para jugar esta carta\n");
                system("pause");
            }
            break;
        case(3)://arma
            if(area->reserva_de_oro >= card->coste && MapCount(area->linea_defensa) > 0){

                if(escogerAliado(area->linea_defensa,card)){
                    area->oro_pagado += card->coste;
                    area->reserva_de_oro -= card->coste;

                    eraseMap(area->mano,card->nombre);

                    if(card->habilidad_arma == 3) activarHabilidadArma(card,card->habilidad_arma,area,0);

                    system("cls");
                    printf("Le has puesto una arma al aliado\n");
                    system("pause");
                }
                else
                {
                    system("cls");
                    printf("No le entregaste la carta al Aliado\n");
                    system("pause");
                    break;
                }
            }
            else
            {
                if(area->reserva_de_oro < card->coste){
                    system("cls");
                    printf("No tienes oros suficientes para jugar esta carta\n");
                    system("pause");
                }
                else
                {
                    system("cls");
                    printf("No Hay Aliados en la zona de defensa\n");
                    system("pause");

                }
            }
            break;
        case(4)://totem
            if(area->reserva_de_oro >= card->coste){
                area->reserva_de_oro -= card->coste;
                area->oro_pagado+= card->coste;
                eraseMap(area->mano,card->nombre);
                list_push_back(area->linea_de_apoyo,card);

                if(card->habilidad_totem == 0 || card->habilidad_totem == 3 ||card->habilidad_totem == 4){
                        activarHabilidadTotem(card,card->habilidad_totem,area);
                }
                system("cls");
                printf("Totem ingresado a la linea de apoyo\n");
                system("pause");
            }
            else
            {
                system("cls");
                printf("No tienes oros suficientes para jugar esta carta\n");
                system("pause");
            }
            break;
        default:
            break;
    }

 //   printf("que sucede\n");
//    imprimirTipoCarta(tipo,card);
 //   system("pause");

}

void descartarCarta(Area_de_juego* area,int modo){//modo 0 para enviar al mazo castillo y 1 para enviar al cementerio
    if(modo == 0){
        system("cls");
        printf("Tienes mas de 8 cartas, debes descartar una\\s carta\\s\n");
        system("pause");
        system("cls");
    }
    Map* mano = area -> mano;

    carta* current = NULL;
    printf("\n");
    imprimirMapa(mano);

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
                imprimirCaracteristicas(current,current->arma);
                if(modo == 0){
                    if(descartarOpciones()){
                        eraseMap(mano,current->nombre);
                        insertMap(area->mazo_castillo,current->nombre,current);
                        bandera = 1;
                    }
                }
                else
                {
                    if(descartarOpciones()){
                        eraseMap(mano,current->nombre);
                        insertMap(area->cementerio,current->nombre,current);
                        bandera = 1;
                    }
                }
                system("cls");
                printf("\n");
                imprimirMapa(mano);
                break;
            case (8):
                break;
        }
    }


}

void Barajar_Mazo(Map *mazo){

    carta **arreglocartas = (carta**) malloc (50 * sizeof(carta*));
    int i = 0;
    carta *tmp = firstMap(mazo);
    int indice;
    int desp;

    while(tmp != NULL){

        arreglocartas[i] = tmp;
        i++;
        eraseMap(mazo,tmp->nombre);
        tmp = firstMap(mazo);

    }

    float max = RAND_MAX;

    for( i = 0; i < 50 ; i++){

        desp=i;

        indice = (rand()/max * (50 - i)) + desp;
        //Intercambio valores de variables
        tmp=arreglocartas[i];
        arreglocartas[i]=arreglocartas[indice];
        arreglocartas[indice]=tmp;

    }

    for(i = 0 ; i < 50 ; i++) insertMap(mazo , arreglocartas[i]->nombre , arreglocartas[i]);

    free(arreglocartas);

    return ;

}

const char* ImpresionPartidaCSVsa(char* palabra, char * nombre_jugador,char* nombre_carta ,char lugar, char bonus,int signo){
    palabra[0] = ',';
    palabra[1] = '\0';
    strcat(palabra,nombre_jugador);
    strcat(palabra,",");
    strcat(palabra,nombre_carta);
    strcat(palabra,",");
    int numero = strlen(palabra);
    palabra[numero] = lugar;
    palabra[numero+1] = '\0';

    if(bonus != 'N'){
        if(signo < 0){
            char aux[4];
            aux[0] = ',';
            aux[1] = '-';
            aux[2] = bonus;
            aux[3] = ',';
            aux[4] = '\0';
            strcat(palabra,aux);
            strcat(palabra,"0,\n");
        }
        else
        {
            char aux[4];
            aux[0] = ',';
            aux[1] = bonus;
            aux[2] = ',';
            aux[3] = '\0';
            strcat(palabra,aux);
            strcat(palabra,"0,\n");
        }

    }
    else{
        strcat(palabra,",nada,0,\n");
    }

    return palabra;
}

const char* ImpresionPartidaCSVca(char* palabra, char * nombre_jugador,char* nombre_carta ,char lugar,char* nombre_aliado,char area_aliado){
    palabra[0] = ',';
    palabra[1] = '\0';
    strcat(palabra,nombre_jugador);
    strcat(palabra,",");
    strcat(palabra,nombre_carta);
    strcat(palabra,",");
    int numero = strlen(palabra);
    palabra[numero] = lugar;
    palabra[numero+1] = '\0';
    strcat(palabra,",");

    strcat(palabra,nombre_aliado);
    strcat(palabra,",");
    numero = strlen(palabra);
    palabra[numero] = area_aliado;
    palabra[numero+1] = '\0';

    strcat(palabra,",\n");

    return palabra;
}

void escribirEnArchivoCSV(Area_de_juego* area, FILE* archivo, HashTable* Tabla_Hash){
    carta* current = NULL;
    char palabra[200];

    while(stack_size(area->oros) > 0){

        current = stack_pop(area->oros);
        strcpy(palabra, ImpresionPartidaCSVsa(palabra,area->nombre_jugador,current->nombre,'3','N',0));
        fprintf(archivo,palabra);

    }

    current = lastMap(area->cementerio);
    while(MapCount(area->cementerio) > 0 && current!= NULL){
        ImpresionPartidaCSVsa(palabra,area->nombre_jugador,current->nombre,'0','N',0);

        fprintf(archivo,palabra);
        current = prevMap(area->cementerio);
    }

    removeAllMap(area->cementerio);

    current = lastMap(area->mano);
    while(MapCount(area->mano) > 0 && current!= NULL ){
        ImpresionPartidaCSVsa(palabra,area->nombre_jugador,current->nombre,'2','N',0);

        fprintf(archivo,palabra);
        current = prevMap(area->mano);
    }
    removeAllMap(area->mano);

    current = lastMap(area->linea_ataque);
    while(MapCount(area->linea_ataque) > 0 && current!= NULL){

        if(current->arma != NULL){


            carta* carta_original = searchHashTable(Tabla_Hash,current->nombre);

            if(carta_original->fuerza != current->fuerza){

                if(carta_original->fuerza > current->fuerza){
                    ImpresionPartidaCSVsa(palabra,area->nombre_jugador,current->nombre,'6',carta_original->fuerza- current->fuerza +48,-1);
                }
                else
                {
                    ImpresionPartidaCSVsa(palabra,area->nombre_jugador,current->nombre,'6', current->fuerza - carta_original->fuerza +48,1);
                }
            }
            else
            {
                    ImpresionPartidaCSVsa(palabra,area->nombre_jugador,current->nombre,'6','N',0);

            }

            fprintf(archivo,palabra);

            ImpresionPartidaCSVca(palabra,area->nombre_jugador,current->arma->nombre,'9',current->nombre,'6');
            fprintf(archivo,palabra);
            current->arma = NULL;
        }
        else
        {
            carta* carta_original = searchHashTable(Tabla_Hash,current->nombre);

            if(carta_original->fuerza != current->fuerza){

                if(carta_original->fuerza > current->fuerza){
                    ImpresionPartidaCSVsa(palabra,area->nombre_jugador,current->nombre,'6',carta_original->fuerza - current->fuerza + 48,-1);
                }
                else
                {
                    ImpresionPartidaCSVsa(palabra,area->nombre_jugador,current->nombre,'6',current->fuerza - carta_original->fuerza + 48,-1);
                }
            }
            else
            {
                ImpresionPartidaCSVsa(palabra,area->nombre_jugador,current->nombre,'6','N',0);
            }
            fprintf(archivo,palabra);
        }

        current = prevMap(area->linea_ataque);
    }
    removeAllMap(area->linea_ataque);

    current = lastMap(area->linea_defensa);
    while(MapCount(area->linea_defensa) > 0 && current!= NULL){
        if(current->arma != NULL){

            carta* carta_original = searchHashTable(Tabla_Hash,current->nombre);

            if(carta_original->fuerza != current->fuerza){

                if(carta_original->fuerza > current->fuerza){
                    ImpresionPartidaCSVsa(palabra,area->nombre_jugador,current->nombre,'5',carta_original->fuerza - current->fuerza + 48,-1);
                }
                else{
                    ImpresionPartidaCSVsa(palabra,area->nombre_jugador,current->nombre,'5',current->fuerza - carta_original->fuerza + 48,1);
                }
            }
            else{
                    ImpresionPartidaCSVsa(palabra,area->nombre_jugador,current->nombre,'5','N',0);
            }
            fprintf(archivo,palabra);

            ImpresionPartidaCSVca(palabra,area->nombre_jugador,current->arma->nombre,'9',current->nombre,'5');
            fprintf(archivo,palabra);

            current->arma = NULL;
        }
        else
        {

            carta* carta_original = searchHashTable(Tabla_Hash,current->nombre);

            if(carta_original->fuerza != current->fuerza){

                if(carta_original->fuerza > current->fuerza){
                    ImpresionPartidaCSVsa(palabra,area->nombre_jugador,current->nombre,'5',carta_original->fuerza - current->fuerza +48,-1);
                }
                else
                {
                    ImpresionPartidaCSVsa(palabra,area->nombre_jugador,current->nombre,'5',current->fuerza - carta_original->fuerza +48,1);
                }
            }
            else
            {
                ImpresionPartidaCSVsa(palabra,area->nombre_jugador,current->nombre,'5','N',0);
            }
            fprintf(archivo,palabra);
        }
        current = prevMap(area->linea_defensa);
    }
    removeAllMap(area->linea_defensa);

    current = list_last(area->destierro);
    while(list_size(area->destierro) > 0 && current!= NULL){

        current = list_pop_back(area->destierro);
        ImpresionPartidaCSVsa(palabra,area->nombre_jugador,current->nombre,'8','N',0);

        fprintf(archivo,palabra);
    }
    area->destierro = NULL;

    current = list_last(area->linea_de_apoyo);
    while(list_size(area->linea_de_apoyo) > 0 && current!= NULL){

        current = list_pop_back(area->linea_de_apoyo);
        ImpresionPartidaCSVsa(palabra,area->nombre_jugador,current->nombre,'7','N',0);
        fprintf(archivo,palabra);

    }
    area->linea_de_apoyo = NULL;

    current = lastMap(area->mazo_castillo);
    while(MapCount(area->mazo_castillo) > 0 && current!= NULL){

        if(strcmp(current->nombre,"Bandera") == 0){

            fprintf(archivo,",%s,%s,%s,%d,%d,%d,%d,%d,%d,",area->nombre_jugador,"Bandera","10",current->tipo,current->coste,current->habilidad_arma,current->fuerza,current->habilidad_talisman,current->habilidad_totem);
            current = prevMap(area->mazo_castillo);
        }
        else
        {

            ImpresionPartidaCSVsa(palabra,area->nombre_jugador,current->nombre,'1','N',0);
            fprintf(archivo,palabra);
            current = prevMap(area->mazo_castillo);

        }
    }
    removeAllMap(area->mazo_castillo);
}

void moverAliadoDeLugar(Map* mapa1, carta* card, Map* mapa2){
    char* nombre = card->nombre;
    char idcaracter = nombre[strlen(nombre)-1];
    nombre[strlen(nombre)-1] = 64;

    eraseMap(mapa1,card->nombre);

    insertMap(mapa2,card->nombre,card);

    nombre[strlen(nombre)-1] = idcaracter;
}

void eliminarAliado(Map* linea,carta* card,Map* cementerio){ // El aliado debe Pertenecer a la linea de defensa/ataque y al cementerio
    char* nombre = card->nombre;
    char idcaracter = nombre[strlen(nombre)-1];
    nombre[strlen(nombre)-1] = 64;

    eraseMap(linea,card->nombre);
    nombre[strlen(nombre)-1] = idcaracter;

    card->estado = false;

    if(card->arma){
        insertMap(cementerio,card->arma->nombre,card->arma);
        card->arma = NULL;
    }
    insertMap(cementerio,card->nombre,card);
}

bool verificarMuerteDeAliado(carta* card,Area_de_juego* area){
    char* nombre = card->nombre;
    int tamano = strlen(card->nombre);
    char aux = nombre[tamano-1];
    nombre[tamano-1] = 64;

    if(searchMap(area->linea_defensa, card->nombre) == NULL){
        nombre[tamano-1] = aux;
        return true;
    }

    nombre[tamano-1] = aux;

    return false;
}

bool destruccionAliadoAtacantexTalisman(Area_de_juego* area, carta* carta_enemiga, carta* defensa){
    char* nombre = carta_enemiga->nombre;
    int tamano = strlen(carta_enemiga->nombre);
    char aux = nombre[tamano-1];
    nombre[tamano-1] = 64;

    if(searchMap(area->area_enemiga->linea_defensa,carta_enemiga->nombre) == NULL){

//        eliminarAliado(area->area_enemiga->linea_defensa,carta_enemiga,area->area_enemiga->cementerio);
        nombre[tamano-1] = aux;
        system("cls");
        printf("El ataque de %s ha fallado\n\n", area->area_enemiga->nombre_jugador);
        system("pause");
        return true;
    }
    return false;
}

void imprimirJugadorGanador(char* nombre_jugador){
    int espacios_faltantes;
    system("cls");

    espacios_faltantes = (45 - strlen(nombre_jugador) - 18)/2 -2;

    gotoxy(35,15);
    printf("%c",201);
    for(int i = 0; i<45; i++) printf("%c",205);
    printf("%c\n",187);
    gotoxy(35,16);
    printf("%c",186);

    gotoxy(50,16);
    printf("%c%c%cFelicidades!!!",173,173,173);
    for(int i = 0; i<14; i++) printf(" ");//****

    printf("%c\n",186);
    gotoxy(35,17);
    printf("%c",186);

    for(int i = 0; i<espacios_faltantes; i++) printf(" ");//******
    printf("%s has ganado la partida",nombre_jugador);
//    for(int i = 0; i<espacios_faltantes; i++) printf(" ");
    gotoxy(80,17);
    printf(" ");
    printf("%c\n",186);
    gotoxy(35,18);
    printf("%c",200);
    for(int i = 0; i<45; i++) printf("%c",205);
    printf("%c",188);

    gotoxy(1,1);
    system("pause");
}

void restaurarAliados(Map* Cementerio, HashTable* tabla){
    carta* current = NULL;
    carta* fuerza;

    current = firstMap(Cementerio);

    for(;current;current= nextMap(Cementerio)){
        if(current->tipo == 1){
            fuerza = searchHashTable(tabla,current->nombre);
            current->fuerza = fuerza -> fuerza;
        }
    }
}


