#include <stdio.h>
#include <stdlib.h>
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


void comenzarDefensa(Area_de_juego* Area_final, carta* carta_enemiga){

    gotoxy(35,15);
    printf("Defensa Realizada por %s",Area_final->nombre_jugador);
    gotoxy(1,20);
    printf("(Recuerda que solo puedes utlizar Talismanes o Defenderte con algún aliado de tu linea de defensa)\n");
    gotoxy(1,26);
    system("pause");
    system("cls");

    printf("Oros Disponibles: %d\nVer Mano\nVer Caracteristicas del Aliado Enemigo\nVer Linea de defensa\nDejarse Atacar",Area_final->reserva_de_oro);

    char tecla;
    int bandera = 0;
    int cont = 1;
    carta* current= NULL;
    int i;
    int diferencia;
    carta* defensa;

    while(bandera == 0){
        gotoxy(1,cont+1);
        tecla = getch();
        switch(tecla){
            case ('w'):
                if(cont == 1) cont = 4 ;
                else cont--;

                break;
            case ('s'):
                if(cont == 4) cont = 1;
                else cont++;
                break;
            case (13):
                switch(cont){
                    case(1)://verifificar la cantidad de oros
                        defensa = verMano(Area_final->mano,1);//se envia la mano y la etapa(0 para lanzar y 1 para defender)
                        if(defensa && defensa->tipo == 2){

                            activarHabilidadTalisman(defensa,defensa->habilidad_talisman,Area_final);

                            if(defensa->habilidad_talisman == 0 || defensa->habilidad_talisman == 4){
                                if(destruccionAliadoAtacantexTalisman(Area_final,carta_enemiga,defensa)){
                                    return;
                                }
                            }

                        }
                        else
                        {
                            if(defensa)
                            {
                                system("cls");
                                gotoxy(35,15);
                                printf("No se puede Jugar esta Carta Desde tu Mano en este momento\n");
                                system("pause");
                            }
                        }
                        system("cls");
                        printf("\nVer Mano\nVer Caracteristicas del Aliado Enemigo\nVer Linea de defensa\nDejarse Atacar");

                        break;
                    case(2):
                        system("cls");
                        imprimirCaracteristicas(carta_enemiga,carta_enemiga->arma);
                        system("pause");
                        system("cls");
                        printf("\nVer Mano\nVer Caracteristicas del Aliado Enemigo\nVer Linea de defensa\nDejarse Atacar");
                        break;
                    case(3):
                        system("cls");
                        defensa = verLineaDeDefensa(Area_final,1);
                        if(defensa){
                            if(defensa->arma && (defensa->arma->habilidad_arma == 0 || defensa->arma->habilidad_arma == 1 || defensa->arma->habilidad_arma == 2)){
                                activarHabilidadArma(defensa->arma,defensa->arma->habilidad_arma,Area_final,0);
                            }

                            diferencia = defensa->fuerza - carta_enemiga->fuerza;

                            if(diferencia > 0){
                                printf("Destruiste al Aliado Enemigo\n");
                                defensa->fuerza -= carta_enemiga->fuerza;

                                eliminarAliado(Area_final->area_enemiga->linea_defensa,carta_enemiga,Area_final->area_enemiga->cementerio);

                            }

                            if(diferencia < 0){
                                system("cls");
                                printf("%d %d\n", MapCount(Area_final->mazo_castillo),MapCount(Area_final->cementerio));
                                printf("Han destruido a tu aliado y te han enviado %d cartas al cementerio\n",diferencia * -1);

                                carta_enemiga->fuerza -= carta_enemiga->fuerza;

                                moverAliadoDeLugar(Area_final->area_enemiga->linea_defensa,carta_enemiga,Area_final->area_enemiga->linea_ataque);

                                eliminarAliado(Area_final->linea_defensa,defensa,Area_final->cementerio);

                                defensa = firstMap(Area_final->mazo_castillo);

                                for(int i = 0; i < diferencia *-1 && defensa != NULL; i++,defensa = firstMap(Area_final->mazo_castillo)){
                                    eraseMap(Area_final->mazo_castillo,defensa->nombre);
                                    insertMap(Area_final->cementerio,defensa->nombre,defensa);
                                }
                                printf("%d %d\n", MapCount(Area_final->mazo_castillo),MapCount(Area_final->cementerio));
                            }

                            if(diferencia == 0){
                                printf("Ambos Aliados han sido Destuidos\n");

                                eliminarAliado(Area_final->area_enemiga->linea_defensa,carta_enemiga,Area_final->area_enemiga->cementerio);
                                eliminarAliado(Area_final->linea_defensa,defensa,Area_final->cementerio);

                            }

                            printf("pep");
                            system("pause");
                            if(defensa->arma && (defensa->arma->habilidad_arma == 0 || defensa->arma->habilidad_arma == 1 || defensa->arma->habilidad_arma == 2)){
                                activarHabilidadArma(defensa->arma,defensa->arma->habilidad_arma,Area_final,1);
                            }
                            return;
                        }

                        system("cls");
                        printf("\nVer Mano\nVer Caracteristicas del Aliado Enemigo\nVer Linea de defensa\nDejarse Atacar");
                        break;
                    case (4):

                        moverAliadoDeLugar(Area_final->area_enemiga->linea_defensa,carta_enemiga,Area_final->area_enemiga->linea_ataque);

                        printf("%d\n", MapCount(Area_final->mazo_castillo));
                        for(current = firstMap(Area_final->mazo_castillo) ,i=0; current && i < carta_enemiga->fuerza;i++, current = firstMap(Area_final->mazo_castillo)){
                            eraseMap(Area_final->mazo_castillo,current->nombre);
                            insertMap(Area_final->cementerio,current->nombre,current);
                        }
                        printf("%d\n", MapCount(Area_final->mazo_castillo));
                        system("pause");
                        return ;//NULL;
                        break;

                }
        }

    }
}

void comenzarAtaque(Area_de_juego* Area_final, carta* card){
    system("cls");
    gotoxy(40,5);
    printf("Comienzo de la Batalla Mitologica");
    gotoxy(35,15);
    printf("Ataque Iniciado por %s con %s\n\n\n",Area_final->nombre_jugador, card->nombre);
    gotoxy(1,26);
    system("pause");
    system("cls");
    if(card->arma){
        activarHabilidadArma(card->arma,card->arma->habilidad_arma,Area_final,0);
    }
    comenzarDefensa(Area_final->area_enemiga,card);

    if(!verificarMuerteDeAliado(card, Area_final)){

        if(card->arma){
            activarHabilidadArma(card->arma,card->arma->habilidad_arma,Area_final,1);
        }
    }

}

carta* verMano(Map* mano,int etapa){
    system("cls");
    if(MapCount(mano) == 0){
        printf("No tienes Cartas");
        return NULL;
    }

    carta* current= NULL;// = firstMap(mano);
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
                if(etapa == 0){
                    if(opcionesCarta(0)) return current;
                }
                else
                {
                    if(opcionesCarta(4)) return current;
                }

                system("cls");
                printf("\n");
                imprimirMapa(mano);
                break;
            case (8):
                return NULL;
                break;
        }
    }

    return NULL;
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
    }
    fclose(partidas);

    Partida* pcurrent = list_first(lista_de_partidas);
    for(;pcurrent != NULL; pcurrent = list_next(lista_de_partidas)){
        printf("%s\n",pcurrent->nombre_partida);
    }

    int i = 0;
    long limite = list_size(lista_de_partidas);
    char tecla;
    int opcion_escogida = -1;
    long newcont = 0;

    system("cls");

    for(i = 0, pcurrent = list_first(lista_de_partidas); i < limite; i++, pcurrent = list_next(lista_de_partidas)) printf("%s\n",pcurrent->nombre_partida);

    while(opcion_escogida == -1){

        gotoxy(1,newcont+1);
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

    i=0;
    pcurrent = list_first(lista_de_partidas);
    do{
        if(i == opcion_escogida) break;
        i++;
        pcurrent = list_next(lista_de_partidas);

    }while(i < opcion_escogida);
    system("cls");

    char direccion[150] = "Partidas\\";
    strcat(direccion,pcurrent->nombre_partida);
    strcat(direccion,".csv");

    FILE* partida_salvada_escogida = fopen(direccion,"r");
    if(partida_salvada_escogida == NULL){
        printf("falla\n");
        return NULL;
    }

    fgets(current,100,partida_salvada_escogida);

    Area_de_juego* area = crearAreaDeJuego();
    Area_de_juego* area2 = crearAreaDeJuego();

    strcpy(area2->nombre_partida,pcurrent->nombre_partida);
    strcpy(area->nombre_partida,pcurrent->nombre_partida);

    area ->area_enemiga = area2;
    area2 ->area_enemiga = area;

    strcpy(area ->nombre_jugador,get_csv_field(current,2));//pcurrent ->nombre_Jugador1);
    strcpy(area2->nombre_jugador,get_csv_field(current,3));//pcurrent ->nombre_Jugador2);

    carta* busqueda;
    int zona;
    char nombre_aliado[100];
    int zona_del_aliado = 0 ;

    while(fgets(current,150,partida_salvada_escogida)){
        busqueda = (carta*) malloc (sizeof(carta));
        *busqueda = *((carta *) searchHashTable(tabla,get_csv_field(current,2)));

        if(busqueda == NULL){
            printf("falla %s %s\n",current,get_csv_field(current,2));
            system("pause");
        }
        else
        {


            if(strcmp(area->nombre_jugador , get_csv_field(current,1))== 0){
                zona = atoi(get_csv_field(current,3));
                strcpy(nombre_aliado,get_csv_field(current,4));
                zona_del_aliado = atoi(get_csv_field(current,5));

                if(strcmp(get_csv_field(current,4),"nada") != 0){
                    busqueda -> fuerza += atoi(get_csv_field(current,4));
                }

                ingresoAreaDeJuego(area,busqueda,zona,nombre_aliado,zona_del_aliado);
            }
            else
            {

                zona = atoi(get_csv_field(current,3));
                if(zona == 10){
                    busqueda->tipo = atoi(get_csv_field(current,4));
                    busqueda->coste = atoi(get_csv_field(current,5));
                    busqueda->habilidad_arma = atoi(get_csv_field(current,6));
                    busqueda->fuerza = atoi(get_csv_field(current,7));
                    busqueda->habilidad_talisman = atoi(get_csv_field(current,8));
                    busqueda->habilidad_totem = atoi(get_csv_field(current,9));
                }
                strcpy(nombre_aliado,get_csv_field(current,4));
                zona_del_aliado = atoi(get_csv_field(current,5));

                if(strcmp(get_csv_field(current,4),"nada") != 0 && zona != 10){
                    busqueda -> fuerza += atoi(get_csv_field(current,4));
                }

                ingresoAreaDeJuego(area2,busqueda,zona,nombre_aliado,zona_del_aliado);
            }
        }

    }

    fclose(partida_salvada_escogida);

 //   printf("%ld %ld %ld %ld %ld %ld %ld %ld\n", MapCount(area->mano), list_size(area->destierro), area->reserva_de_oro, MapCount(area->cementerio), MapCount(area->linea_defensa), MapCount(area->mazo_castillo), list_size(area->linea_de_apoyo), area->total);
 //   area= area2;
 //   printf("%ld %ld %ld %ld %ld %ld %ld %ld\n", MapCount(area->mano), list_size(area->destierro), area->reserva_de_oro, MapCount(area->cementerio), MapCount(area->linea_defensa), MapCount(area->mazo_castillo), list_size(area->linea_de_apoyo), area->total);
 //   system("pause");
    return area;
}

carta* verLineaAtaqueEnemigo(Area_de_juego* Area, int modo){//modo solo ver(0) o escoger(1)
    system("cls");
    if(MapCount(Area->area_enemiga->linea_ataque) == 0){
        printf("El usuario rival no tiene Cartas en la linea de ataque\n");
        system("pause");
        return NULL;
    }
    Map* lineaAtaque = Area ->area_enemiga->linea_ataque;
    printf("\n");
    imprimirMapa(lineaAtaque);

    int cont = 1;
    char tecla;
    unsigned short bandera = 0;

    while(bandera == 0){

        gotoxy(1,cont+1);

        tecla = getch();
        if(modo == 0)
        {
            eleccionMapa(tecla,lineaAtaque,&cont,0);
            if(cont == -1) return NULL;
        }
        if(modo == 1){
            carta* card = eleccionMapa(tecla,lineaAtaque,&cont,1);
            if(card) return card;
            else{
                if(cont == -1){
                    return NULL;
                }
            }
        }
    }

    return NULL;

}

void agruparOros(Area_de_juego* Area){
    system("cls");

    printf("%d %d",Area->oro_pagado, Area->reserva_de_oro);
    Area ->reserva_de_oro+= Area->oro_pagado;
    Area ->oro_pagado = 0;
    gotoxy(52,15);
    printf("Oros Agrupados\n");
    gotoxy(1,25);
    system("pause");
}

void agruparAliados(Area_de_juego* Area){
    system("cls");

    if(MapCount(Area->linea_ataque) == 0){
        printf("Tus aliados ya se encuentran agrupados\n");
        system("pause");
        system("cls");
        return;
    }

    carta* current = NULL;
    for(current = firstMap(Area->linea_ataque);current;current = nextMap(Area->linea_ataque)){
        insertMap(Area->linea_defensa,current->nombre,current);
        eraseMap(Area->linea_ataque,current->nombre);
        current->estado = false;
    }

    printf("Tus aliados han sido agrupados\n");
    system("pause");
    system("cls");

}

void verLineaDeAtaque(Area_de_juego* Area){
    system("cls");
    printf("\n");
    if(MapCount(Area->linea_ataque) == 0){
        printf("No tienes jugadores en la linea de ataque\n");
        system("pause");
        return;
    }

    Map* ataque = Area->linea_ataque;
    imprimirMapa(ataque);

    int cont = 1;
    char tecla;
    unsigned short bandera = 0;

    while(bandera == 0){

        gotoxy(1,cont+1);

        tecla = getch();
        eleccionMapa(tecla,ataque,&cont,0);
        if(cont == -1){
            return;
        }
    }
}

void verDestierro(Area_de_juego* Area){
    system("cls");
    printf("\n");
    if(list_size(Area->destierro) == 0){
        printf("No tienes cartas en el destierro\n");
        system("pause");
        return;
    }
    list* destierro = Area->destierro;
    carta* current = NULL;
    for(current = list_first(destierro); current; current = list_next(destierro)) printf("%s\n",current->nombre);

    printf("\n");
    int cont = 1;
    char tecla;
    unsigned short bandera = 0;

    while(bandera == 0){

        gotoxy(1,cont+1);
        tecla = getch();
        if(!eleccionLista(tecla,destierro,&cont,0)) return;

    }

}

carta* verLineaDeDefensa(Area_de_juego* Area, int etapa){
    system("cls");
    if(MapCount(Area->linea_defensa) == 0){
        printf("No tienes aliados en la linea de defensa\n");
        system("pause");
        return NULL;
    }

    carta* current;
    printf("\n");
    Map* Defensa = Area->linea_defensa;
    imprimirMapa(Defensa);
    unsigned short i;
    unsigned short cont = 1;
    char tecla;
    unsigned short bandera = 0;

    while(bandera == 0){

        gotoxy(1,cont+1);


        tecla = getch();

        switch(tecla){
            case ('w'):
                if(cont == 1) cont = MapCount(Defensa);
                else cont--;

                break;
            case ('s'):
                if(cont == MapCount(Defensa)) cont = 1;
                else cont++;
                break;
            case (13):
                for(i = 0, current = firstMap(Defensa); i < cont-1 ; i++,current = nextMap(Defensa));
                system("cls");
                imprimirCaracteristicas(current,current->arma);

                switch(etapa){
                    case (0):
                        if(opcionesCarta(3))
                        {
                            return current;
                        }
                        break;
                    case (1):
                        if(opcionesCarta(4)){
                            return current;
                        }
                        break;
                }
                system("cls");
                printf("\n");
                imprimirMapa(Defensa);
                break;
            case (8):
                return NULL;
                break;
        }
    }
    return NULL;
}

carta* verLineaDeDefensaEnemiga(Area_de_juego *Area,int modo){

    system("cls");
    if(MapCount(Area->area_enemiga->linea_defensa) == 0){
        printf("El usuario rival no tiene Cartas en la linea de Defensa\n");
        system("pause");
        return NULL;
    }


    Map* lineaDefensa = Area->area_enemiga->linea_defensa;
    printf("\n");
    imprimirMapa(lineaDefensa);
    int cont = 1;
    char tecla;
    unsigned short bandera = 0;

    while(bandera == 0){

        gotoxy(1,cont+1);

        tecla = getch();

        if(modo == 0){
            eleccionMapa(tecla,lineaDefensa,&cont,0);
            if(cont == -1) return NULL;

        }

        if(modo == 1){
            carta* card = eleccionMapa(tecla,lineaDefensa,&cont,1);
            if(card) return card;
            else{
                if(cont == -1){
                    return NULL;
                }
            }
        }
    }
    return NULL;

}

void verDestierroEnemigo(Area_de_juego *Area){

    system("cls");
    printf("\n");
    if(list_size(Area->area_enemiga->destierro) == 0){
        printf("Tu oponente no tiene Cartas en el destierro\n");
        system("pause");
        return;
    }
    list* destierro = Area->area_enemiga->destierro;
    carta* current = NULL;
    for(current = list_first(destierro); current; current = list_next(destierro)) printf("%s\n",current->nombre);

    printf("\n");

    int cont = 1;
    char tecla;
    unsigned short bandera = 0;

    while(bandera == 0){

        gotoxy(1,cont+1);

        tecla = getch();
        if(!eleccionLista(tecla,destierro,&cont,0)) return;

    }

}

carta* verLineaDeApoyoEnemigo(Area_de_juego* Area, int modo){
    system("cls");
    printf("\n");

    if(list_size(Area->area_enemiga->linea_de_apoyo) == 0){
        printf("Tu oponente no tiene Cartas en la linea de apoyo\n");
        system("pause");
        return NULL;
    }
    list* apoyo = Area->area_enemiga->linea_de_apoyo;
    carta* current = NULL;
    for(current = list_first(apoyo); current; current = list_next(apoyo)) printf("%s\n",current->nombre);

    printf("\n");

    int cont = 1;
    char tecla;
    unsigned short bandera = 0;

    while(bandera == 0){

        gotoxy(1,cont+1);

        tecla = getch();
        if(modo == 0){
            eleccionLista(tecla,apoyo,&cont,0);
            if(cont == -1) return NULL;
        }
        else
        {
            carta* eleccion = eleccionLista(tecla,apoyo,&cont,1);
            if(eleccion) return eleccion;
            else{
                if(cont == -1) return NULL;
            }
        }
    }
    return NULL;
}

bool verLineaDeApoyo(Area_de_juego* Area){
    system("cls");
    printf("\n");

    if(list_size(Area->area_enemiga->linea_de_apoyo) == 0){
        printf("No tienes Cartas en la linea de apoyo\n");
        system("pause");
        return false;
    }
    list* apoyo = Area->linea_de_apoyo;
    carta* current = NULL;
    for(current = list_first(apoyo); current; current = list_next(apoyo)) printf("%s\n",current->nombre);

    printf("\n");
    int i;
    int cont = 1;
    char tecla;
    unsigned short bandera = 0;

    while(bandera == 0){

        gotoxy(1,cont+1);

        tecla = getch();

        switch(tecla){
            case ('w'):
                if(cont == 1) cont = list_size(apoyo);
                else cont--;

                break;
            case ('s'):
                if(cont == list_size(apoyo)) cont = 1;
                else cont++;
                break;
            case (13):
                for(i = 0, current = list_first(apoyo); i < cont-1 ; i++,current = list_next(apoyo));
                system("cls");
                imprimirCaracteristicas(current,current->arma);

                if((current->habilidad_totem == 1 || current->habilidad_totem == 6 || current->habilidad_totem == 7) && opcionesCarta(1)){

                        return true;
                        activarHabilidadTotem(current,current->habilidad_totem,Area);

                }
                else
                {
                    printf("\n\n\n\n");
                    system("pause");
                }

                    system("cls");
                    printf("\n");

                for(current = list_first(apoyo); current; current = list_next(apoyo)) printf("%s\n",current->nombre);
                break;
            case (8):
                return false;
                break;

        }

    }
    return false;
}

void guardarPartida(Area_de_juego* area, HashTable* Tabla_Hash){//**********

    system("cls");

    char direccion[200];
    strcpy(direccion,"Partidas\\");
    strcat(direccion,area->nombre_partida);
    strcat(direccion,".csv");

    FILE * archivo = fopen(direccion,"w");

    fprintf(archivo,",%s,%s,%s,nada,0,\n",area->nombre_partida,area->nombre_jugador,area->area_enemiga->nombre_jugador);
    escribirEnArchivoCSV(area,archivo,Tabla_Hash);
    escribirEnArchivoCSV(area->area_enemiga,archivo,Tabla_Hash);
    fclose(archivo);

    return;

}

void terminarTurno(Area_de_juego* Area_final){
    carta* current;

    if(list_size(Area_final->linea_de_apoyo) > 0){
        for(current=list_first(Area_final->linea_de_apoyo);current;current=list_next(Area_final->linea_de_apoyo)){
            if(current->habilidad_totem == 1 || current->habilidad_totem == 6 || current->habilidad_totem == 7){
                current ->estado = false;
            }
        }
    }

    if(MapCount(Area_final->mano) < 8){
        carta* Carta = firstMap(Area_final->mazo_castillo);
        insertMap(Area_final->mano,Carta->nombre,Carta);
        eraseMap(Area_final->mazo_castillo,Carta->nombre);
    }
    else
    {
        if(MapCount(Area_final->mano) > 8){
            do{

                descartarCarta(Area_final,0);

            }while(MapCount(Area_final->mano) > 8);
        }
    }

}

void comenzarJuego(Area_de_juego* Area_final, HashTable* Tabla_Hash){

    char tecla;
    unsigned short bandera = 0;
    unsigned short b_agrupacion_oro = 0;//bandera si ya se agruparon los oros toma valor 1, sino toma valor 0
    unsigned short b_agrupacion_aliado = 0;
    unsigned short cont = 1;

    carta* cartaJugada = NULL;

    carta* estado_bandera = eraseMap(Area_final->area_enemiga->mazo_castillo,"Bandera");

    if(estado_bandera == NULL){
        estado_bandera = crearCarta(",band,Bandera,0,0,0,0,0,0,");
        system("pause");
    }
    else
    {
        Area_final->reserva_de_oro = estado_bandera->fuerza;
        Area_final->oro_pagado = estado_bandera->habilidad_arma;
        b_agrupacion_oro = estado_bandera->tipo;
        b_agrupacion_aliado = estado_bandera->coste;
        Area_final->area_enemiga->oro_pagado  = estado_bandera->habilidad_talisman;
        Area_final->area_enemiga->reserva_de_oro = estado_bandera->habilidad_totem ;
    }


    printf("\n%d",stack_size(Area_final->oros));

    do{
        restaurarAliados(Area_final->cementerio, Tabla_Hash);

        if(MapCount(Area_final->mazo_castillo) == 0 || MapCount(Area_final->area_enemiga->mazo_castillo) == 0){
            if(MapCount(Area_final->mazo_castillo) == 0) imprimirJugadorGanador(Area_final->area_enemiga->nombre_jugador);
            else imprimirJugadorGanador(Area_final->nombre_jugador);
            guardarPartida(Area_final,Tabla_Hash);
            return;
        }

        imprimirMenucomenzarJuego(Area_final->nombre_jugador, Area_final->reserva_de_oro);

        while(bandera == 0){
            gotoxy(1,cont+1);

            tecla = getch();

            switch(tecla){

                case('w'):
                    if(cont == 1) cont = 13;
                    else cont--;

                    break;
                case('s'):
                    if(cont == 13) cont = 1;
                    else cont++;

                    break;
                case(13):
                    bandera = cont;
                    break;
                case(8):
                    cont = 13;
                    bandera = cont;
                    break;
            }
        }

        switch(bandera){


            case 1:
                cartaJugada = verMano(Area_final->mano, 0);

                if(cartaJugada){
                    analizarYLanzarCarta(cartaJugada,Area_final);
                    b_agrupacion_aliado = 1;
                    b_agrupacion_oro = 1;
                }
                bandera = 0;
                break;
            case 2:
                if(b_agrupacion_oro == 0)agruparOros(Area_final);
                else
                {
                    system("cls");
                    gotoxy(48,15);
                    printf("Los oros ya han sido agrupados\n");
                    gotoxy(1,25);
                    system("pause");
                }
                b_agrupacion_oro = 1;
                bandera = 0;
                break;
            case 3:
                if(b_agrupacion_aliado == 0){
                    agruparAliados(Area_final);
                }
                else
                {
                    system("cls");
                    printf("No puedes agrupar a Tus Aliados\n");
                    system("pause");
                }
                b_agrupacion_aliado = 1;

                bandera = 0;
                break;
            case 4://Ver destierro
                verDestierro(Area_final);
                bandera = 0;
                break;
            case 5://Ver destierro enemigo
                verDestierroEnemigo(Area_final);
                bandera = 0;
                break;
            case 6://Ver linea de ataque
                verLineaDeAtaque(Area_final);
                bandera = 0;
                break;
            case 7://Ver linea de ataque enemigo
                verLineaAtaqueEnemigo(Area_final,0);
                bandera = 0;
                break;
            case 8://Ver linea de defensa
                cartaJugada = NULL;
                cartaJugada = verLineaDeDefensa(Area_final,0);
                if(cartaJugada){
                    comenzarAtaque(Area_final,cartaJugada);
                    b_agrupacion_aliado = 1;
                }
                bandera = 0;
                break;
            case 9://Ver linea de defensa enemiga
                verLineaDeDefensaEnemiga(Area_final,0);
                bandera = 0;
                break;
            case 10://Ver linea de apoyo
                if (verLineaDeApoyo(Area_final))
                {
                    b_agrupacion_aliado = 1;
                    b_agrupacion_oro = 1;
                }
                bandera = 0;
                break;
            case 11://Ver linea de apoyo enemiga
                verLineaDeApoyoEnemigo(Area_final,0);
                bandera = 0;
                break;

            case 12:// Terminar Turno
                terminarTurno(Area_final);

                b_agrupacion_oro = 0;
                b_agrupacion_aliado = 0;
                Area_final = Area_final->area_enemiga;
                system("cls");
                gotoxy(1,15);
                printf("%50s Turno de %s"," ",Area_final->nombre_jugador);
                gotoxy(1,22);
                system("pause");
                bandera = 0;
                break;
            case 13: // Se guarda la Partida y se va al menú principal
                estado_bandera->tipo = b_agrupacion_oro;
                estado_bandera->coste = b_agrupacion_aliado;
                estado_bandera->habilidad_arma = Area_final->oro_pagado;
                estado_bandera->fuerza = Area_final->reserva_de_oro;
                estado_bandera->habilidad_talisman = Area_final->area_enemiga->oro_pagado;
                estado_bandera->habilidad_totem = Area_final->area_enemiga->reserva_de_oro;

                insertMap(Area_final->area_enemiga->mazo_castillo,estado_bandera->nombre,estado_bandera);

                guardarPartida(Area_final, Tabla_Hash);
                system("cls");
                imprimirCuadrado();
                gotoxy(53,16);
                printf("Partida Guardada");
                gotoxy(1,25);
                system("pause");
                system("cls");
                return;
                break;
            default:
                break;

        }

    }while(bandera != 10);
}
