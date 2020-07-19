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


void imprimirHabilidadTotem(int habilidad){
    switch(habilidad){
        case(0):
            printf("Tus Aliados ganan 2 a la fuerza.");
            break;
        case(1):
            printf("Una vez por turno, Baraja 2 cartas de tu cementerio en tu Mazo Castillo.");
            break;
        case(2):
            printf("Destruye un totem enemigo Cuando entra en juego.");
            break;
        case(3):
            printf("Aliados oponentes pierden 1 a la fuerza.");
            break;
        case(4):
            printf("Cuando Entra en juego, roba tantas cartas como Totems controles.");
            break;
        case(5):
            printf("Cuando entra en juego, Puedes destruir un tótem o arma en juego.");
            break;
        case(6):
            printf("Una vez por turno, Baraja 2 cartas de tu cementerio en tu Mazo Castillo y robar una carta.");
            break;
        case(7):
            printf("Una vez por turno, puedes generar 2 oros.");
            break;

    }
}

void imprimirHabilidadTalisman(int habilidad){
    switch(habilidad){

        case(0):
            printf("Destruye a un aliado oponente");//**
            break;
        case(1):
            printf("Saca Una carta del mazo");//****
            break;
        case(2):
            printf("Genera 3 oros");
            break;
        case(3):
            printf("Un jugador bota una carta por cada aliado en juego");
            break;
        case(4):
            printf("Destruye un Aliado");//****
            break;
        case(5):
            printf("Para jugar esta carta debes botar 5 cartas, Un jugador bota 5 cartas");
            break;
        case(6):
            printf("Roba 2 cartas de tu Mazo Castillo");//***
            break;
        case(7):
            printf("Los Aliados que controles ganan dos a la fuerza");
            break;
        case(8):
            printf("Roba 1 Carta de Tu mazo Castillo");//***
            break;
        case(9):
            printf("Descarta tu mano, luego busca una carta en tu castillo o cementerio y ponla en tu mano");
            break;
        case(10):
            printf("Cuando juegues esta carta, descarta tu mano. Juega un aliado desde tu castillo y//o Cementerio de coste igual o menor a total de cartas descartadas sin pagar su coste");
            break;
        case(11):
            printf("Baraja tantas cartas de tu cementerio en tu castillo como cartas haya en juego");
            break;
        case(12):
            printf("Al momento de jugar esta Carta, puedes destruir cualquier numero de aliados que controles. Un jugador bota tantas cartas como Aliados hayan sido destruidos de esta manera");
            break;







    }
}

void imprimirHabilidadArma(int habilidad){
    switch(habilidad){

        case(0):
            printf("Aliado gana 1 a la fuerza");
            break;
        case(1):
            printf("Aliado gana 2 a la fuerza");
            break;
        case(2):
            printf("Aliado gana 3 a la fuerza");
            break;
        case(3):
            printf("Cuando entra en juego todas las armas del cementerio pasan a la mano");
            break;
        case(4):
            printf("Una vez por turno, puedes desterrar una carta del cementerio");
            break;
        case(5):
            printf("En tu vigilia,Una vez por turno, un Jugador bota tantas cartas como aliados controles");
            break;
        case(6):
            printf("Puedes desterrar un aliado de tu mano para buscar en tu Castillo/Cementerio y ponerlo en tu mano(1 vez por turno)");
            break;
        case(7):
            printf("Cuando el Portador haga daño de combate a un castillo oponente, puedes ganar el control de un aliado oponente");
            break;

    }
}

void h_totem_cero(carta* card, Area_de_juego* Area){
    if(MapCount(Area->linea_ataque)==0 && MapCount(Area->linea_defensa) == 0){
        printf("No tienes Aliados");
        return;
    }

    carta* current = NULL;
    for(current=firstMap(Area->linea_ataque);current;current=nextMap(Area->linea_ataque)){
        current->fuerza+=2;
    }

    for(current=firstMap(Area->linea_defensa);current;current=nextMap(Area->linea_defensa)){
        current->fuerza+=2;
    }

}

void h_totem_uno(carta* card, Area_de_juego* area){
    if(card->estado){
        printf("Esta Carta ya se ha Utilizado en este turno\n");
        system("pause");
        return;
    }

    if(MapCount(area->cementerio) > 1 ){
        int i=0;
        carta* current = NULL;
        for (i=0, current = firstMap(area->cementerio) ; i<2 && current!= NULL ;i++, current = nextMap(area->cementerio)){
            if(current){
                eraseMap(area->cementerio,current->nombre);
                insertMap(area->mazo_castillo,current->nombre,current);

            }
        }
        card ->estado = true;
    }
    else
    {
        printf("No tienes Cartas en el Cementerio\n");
        system("pause");
    }
}

void h_totem_dos(carta* card){//vacio

}

void h_totem_tres(carta* card){//vacio

}

void h_totem_cuatro(carta* card){//vacio

}

void h_totem_cinco(carta* card){//vacio

}

void h_totem_seis(carta* card, Area_de_juego* area){

    carta* current = NULL;

    if(card->estado == true){
        printf("Esta Carta ya se ha Utilizado en este turno\n");
        system("pause");
        return;
    }


    if(MapCount(area->cementerio) >= 1 ){
        int i=0;
        carta* current = NULL;
        for (i=0, current = firstMap(area->cementerio) ; i<2 && current!= NULL ;i++, current = nextMap(area->cementerio)){
            if(current){
                eraseMap(area->cementerio,current->nombre);
                insertMap(area->mazo_castillo,current->nombre,current);

            }
        }
    }
    else
    {
        printf("No tienes Cartas en el Cementerio\n");
        system("pause");
    }

    if(MapCount(area->mazo_castillo) > 0 ){
        current = firstMap(area->mazo_castillo);
        eraseMap(area->mazo_castillo, current->nombre);
        insertMap(area->mano,current->nombre,current);
    }

    card ->estado = true;
}

void h_totem_siete(carta* card, Area_de_juego* area){

    if(card->estado){
        printf("Esta Carta ya se ha Utilizado en este turno\n");
        system("pause");

    }
    else{
        area->reserva_de_oro += 2;
        card ->estado = true;
    }


}

void activarHabilidadTotem(carta* card, int habilidad, Area_de_juego* area){
    system("cls");
    switch(habilidad){
        case(0):
            h_totem_cero(card, area);
            break;
        case(1):
            h_totem_uno(card,area);
            break;
        case(2):
            //h_totem_dos(card);
            break;
        case(3):
            //h_totem_tres(card);
            break;
        case(4):
            //h_totem_cuatro(card);
            break;
        case(5):
            //h_totem_cinco(card);
            break;
        case(6):
            h_totem_seis(card,area);
            break;
        case(7):
            h_totem_siete(card,area);
            break;

    }
}


void h_arma_cero(carta* card, int valor){// el valor indica si la habilidad siendo activada o desactivada
    carta* carta_aliado = card->arma;

    if(valor == 0) carta_aliado->fuerza++;
    else carta_aliado->fuerza--;
}

void h_arma_uno(carta* card, int valor){// el valor indica si la habilidad siendo activada o desactivada
    carta* carta_aliado = card->arma;

    if(valor == 0) carta_aliado->fuerza+=2;
    else carta_aliado->fuerza -=2;
}

void h_arma_dos(carta* card, int valor){

    carta* carta_aliado = card->arma;// el valor indica si la habilidad siendo activada o desactivada
    if(valor==0) carta_aliado->fuerza+=3;
    else carta_aliado->fuerza -=3;
}

void h_arma_tres(carta* card , Area_de_juego *Areafinal){//

    carta *nav = firstMap(Areafinal->cementerio);

    Map* aux = createMap(cmp_str_map);

    while(nav != NULL){

        if(nav->tipo == 3){

            insertMap(Areafinal->mano , nav->nombre , nav);
            insertMap(aux,nav->nombre,nav);

        }
        nav = nextMap(Areafinal->cementerio);

    }

    for(nav = firstMap(aux); nav; nav = nextMap(aux)) eraseMap(Areafinal->cementerio,nav->nombre);
    Areafinal->oro_pagado += card->coste;
    Areafinal->reserva_de_oro -= card->coste;
    removeAllMap(aux);


}


void h_arma_cuatro(carta* card, Area_de_juego* area){//vacio

}

void h_arma_cinco(Area_de_juego *area){

    long total = MapCount(area->linea_defensa) + MapCount(area->linea_ataque);
    long i = 0;

    carta* card = firstMap(area->area_enemiga->mazo_castillo);

    while(card != NULL && i < total){

        insertMap(area->area_enemiga->cementerio,card->nombre,card);
        eraseMap(area->area_enemiga->mazo_castillo,card->nombre);

        card = firstMap(area->area_enemiga->mazo_castillo);
        i++;

    }

}

void h_arma_seis(Area_de_juego *area){
/*
    carta *current = NULL;
    char tecla;
    unsigned short cont = 1;
    unsigned short bandera = 0;
    imprimirMapa(area->mano);

    while(bandera == 0){
        gotoxy(1,cont+1);
        tecla = getch();

        switch(tecla){
            case ('w'):
                if(cont == 1) cont = MapCount(area->mano);
                else cont--;

                break;
            case ('s'):
                if(cont == MapCount(area->mano)) cont = 1;
                else cont++;
                break;
            case (13):
                for(i = 0, current = firstMap(area->mano); i < cont-1 ; i++,current = nextMap(area->mano));
                eraseMap(area->mano , current->nombre);
                bandera = 1;
                break;

            case (8):
                return NULL;
                break;
        }

    }

    system("cls");
    imprimirMapa(area->mazo_castillo);
    current = NULL
    cont = 1;

    while(bandera == 0){
        gotoxy(1,cont+1);
        tecla = getch();

        switch(tecla){
            case ('w'):
                if(cont == 1) cont = MapCount(area->mazo_castillo);
                else cont--;

                break;
            case ('s'):
                if(cont == MapCount(area->mazo_castillo)) cont = 1;
                else cont++;
                break;
            case (13):
                for(i = 0, current = firstMap(area->mazo_castillo); i < cont-1 ; i++,current = nextMap(area->mazo_castillo));
                insertMap(area->mano , current->nombre , current);
                eraseMap(area->mazo_castillo , current->nombre);
                bandera = 1;
                return;

        }

    }
*/
}

void h_arma_siete(carta* card){//vacio

}

void activarHabilidadArma(carta* card, int habilidad, Area_de_juego* area, int valor){
    system("cls");
    switch(habilidad){
        case(0):
            h_arma_cero(card,valor);
            break;
        case(1):
            h_arma_uno(card,valor);
            break;
        case(2):
            h_arma_dos(card, valor);
            break;
        case(3):
            h_arma_tres(card,area);
            break;
        case(4):
            h_arma_cuatro(card,area);
            break;
        case(5):
            h_arma_cinco(area);
            break;
        case(6):
            h_arma_seis(area);
            break;
        case(7):
            h_arma_siete(card);
            break;

    }

}

void h_talisman_cero(carta* card,Area_de_juego * Area){
    h_talisman_cuatro(card,Area);
}

void h_talisman_uno(carta* card,Area_de_juego * Area ){
    system("cls");
 //   printf("\nCastillo:%d %d %d\n", MapCount(Area->mazo_castillo),MapCount(Area->mano),MapCount(Area->cementerio));
    if(MapCount(Area->mazo_castillo) > 0){
        carta* carta_nueva = firstMap(Area->mazo_castillo);
        eraseMap(Area->mazo_castillo,carta_nueva->nombre);
        insertMap(Area->mano,carta_nueva->nombre,carta_nueva);

        eraseMap(Area->mano,card->nombre);
        insertMap(Area->cementerio,card->nombre,card);
     //   printf("\nCastillo:%d %d %d%s\n", MapCount(Area->mazo_castillo),MapCount(Area->mano),MapCount(Area->cementerio),carta_nueva->nombre);
    }
    system("pause");

}

void h_talisman_dos(carta* card,Area_de_juego* Area){

    Area->reserva_de_oro += 3;

    eraseMap(Area->mano,card->nombre);
    insertMap(Area->cementerio,card->nombre,card);
}

void h_talisman_tres(carta* card,Area_de_juego* area){
    int cantidad_de_aliados = MapCount(area->linea_ataque) + MapCount(area->linea_defensa) + MapCount(area->area_enemiga->linea_ataque) + MapCount(area->area_enemiga->linea_defensa);

 //   printf("%d %d %d %d\n",cantidad_de_aliados,MapCount(area->mano),MapCount(area->area_enemiga->mazo_castillo),MapCount(area->area_enemiga->cementerio));

    Map* mazo_enemigo = area->area_enemiga->mazo_castillo;
    Map* cementerio_enemigo = area->area_enemiga->cementerio;
    carta* current = firstMap(mazo_enemigo);
    int cont = 0;

    for(cont = 0; current && cont < cantidad_de_aliados; current = firstMap(mazo_enemigo),cont++){
        eraseMap(mazo_enemigo,current->nombre);
        insertMap(cementerio_enemigo,current->nombre,current);
    }

    eraseMap(area->mano,card->nombre);
    insertMap(area->cementerio,card->nombre,card);

//    printf("%d %d %d %d\n",cantidad_de_aliados,MapCount(area->mano),MapCount(area->area_enemiga->mazo_castillo),MapCount(area->area_enemiga->cementerio));
//    system("pause");

}

void h_talisman_cuatro(carta* card,Area_de_juego* Area){
    printf("\nVer Linea de Ataque Enemigo\n");
    printf("Ver Linea de Defensa Enemigo");
    int bandera = 0;
    carta* aliadoObjetivo = NULL;
    int cont = 1;
    char tecla;
    while(aliadoObjetivo == NULL){

            while(bandera == 0){
            gotoxy(1,cont+1);

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
                case(13):
                    bandera = cont;
                    break;
                case(8):
                    Area->oro_pagado -= card->coste;
                    Area->reserva_de_oro+= card->coste;
                    return;
                    break;
            }
        }

        switch(bandera){
                case(1):
                    system("cls");
                    aliadoObjetivo = verLineaAtaqueEnemigo(Area,1);
                    if(aliadoObjetivo){
                        eraseMap(Area->mano,card->nombre);
                        insertMap(Area->cementerio,card->nombre,card);
                        eliminarAliado(Area->area_enemiga->linea_ataque,aliadoObjetivo,Area->area_enemiga->cementerio);
                        return;
                    }

                    system("cls");
                    bandera = 0;
                    break;
                case(2):
                    system("cls");
                    aliadoObjetivo = verLineaDeDefensaEnemiga(Area,1);
                    if(aliadoObjetivo){
                            eraseMap(Area->mano,card->nombre);
                            insertMap(Area->cementerio,card->nombre,card);
                            eliminarAliado(Area->area_enemiga->linea_defensa,aliadoObjetivo,Area->area_enemiga->cementerio);
                            return;
                    }

                    bandera = 0;
                    system("cls");
                    break;
                default:
                    break;
        }
        system("cls");
        printf("\nVer Linea de Ataque Enemigo\n");
        printf("Ver Linea de Defensa Enemigo");
    }


}

void h_talisman_cinco(carta* card,Area_de_juego* Area_final){

    eraseMap(Area_final->mano,card->nombre);
    insertMap(Area_final->cementerio,card->nombre,card);
    int cont = 0;


    if(MapCount(Area_final->mano) >= 5){
 //       printf("%d %d %d",MapCount(Area_final->mano),MapCount(Area_final->area_enemiga->mazo_castillo),MapCount(Area_final->area_enemiga->cementerio));
 //       system("pause");
        do{
            cont++;
            system("cls");
            descartarCarta(Area_final,1);

        }while(cont < 5);
        cont = 0;

        Map* mazo_enemigo = Area_final->area_enemiga->mazo_castillo;
        Map* cementerio_enemigo = Area_final->area_enemiga->cementerio;

        carta* current = firstMap(mazo_enemigo);

        for(cont = 0; current && cont < 5; current = firstMap(mazo_enemigo),cont++){
            eraseMap(mazo_enemigo,current->nombre);
            insertMap(cementerio_enemigo,current->nombre,current);
        }
//        printf("%d %d %d",MapCount(Area_final->mano),MapCount(Area_final->area_enemiga->mazo_castillo),MapCount(Area_final->area_enemiga->cementerio));
//        system("pause");
    }
    else
    {
        system("No tienes cartas Suficientes para descartar\n");
    }

}

void h_talisman_seis(carta* card, Area_de_juego* Area){
    int cantidad =2;
    int cont = 0;
    system("cls");

    while(MapCount(Area->mazo_castillo) > 0 && cont < cantidad){
        carta* carta_nueva = firstMap(Area->mazo_castillo);
        eraseMap(Area->mazo_castillo,carta_nueva->nombre);
        insertMap(Area->mano,carta_nueva->nombre,carta_nueva);

        cont++;
    }

    eraseMap(Area->mano,card->nombre);
    insertMap(Area->cementerio,card->nombre,card);

}

void h_talisman_siete(carta* card, Area_de_juego* Area_final){
    Map* linea_ataque = Area_final->linea_ataque;
    Map* linea_defensa = Area_final->linea_defensa;

    carta* current = NULL;
    for(current = firstMap(linea_defensa); current; current = nextMap(linea_defensa)){
        current->fuerza+=2;
    }
    for(current = firstMap(linea_ataque); current; current = nextMap(linea_ataque)){
        current->fuerza+=2;
    }

    eraseMap(Area_final->mano,card->nombre);
    insertMap(Area_final->cementerio,card->nombre,card);
}

void h_talisman_ocho(carta* card,Area_de_juego* Area){

    h_talisman_uno(card,Area);

}

void h_talisman_nueve(carta* card){//vacio

}

void h_talisman_diez(carta* card){//vacio

}

void MapaCartasEnJuego(Map* mapa, int* cont){
    carta* current = NULL;
    for(current=firstMap(mapa); current; current = nextMap(mapa)){
        if(current->arma){
            (*cont)++;
        }
        (*cont)++;
    }
}

void h_talisman_once(carta* card, Area_de_juego* Area_Final){

    system("cls");

    Map* linea_de_defensa = Area_Final->linea_defensa;
    Map* linea_de_ataque = Area_Final->linea_ataque;
    Map* linea_de_defensa_enemiga = Area_Final->area_enemiga->linea_defensa;
    Map* linea_de_ataque_enemiga = Area_Final->area_enemiga->linea_defensa;
    int cartas_en_juego = 0;

    MapaCartasEnJuego(linea_de_ataque,&cartas_en_juego);
    MapaCartasEnJuego(linea_de_defensa,&cartas_en_juego);
    MapaCartasEnJuego(linea_de_ataque_enemiga,&cartas_en_juego);
    MapaCartasEnJuego(linea_de_defensa_enemiga,&cartas_en_juego);

    carta* current = NULL;
    int cont = 0;

    cartas_en_juego += list_size(Area_Final->area_enemiga->linea_de_apoyo)+ list_size(Area_Final->linea_de_apoyo);

    for(cont = 0,current = firstMap(Area_Final->cementerio); current && cont < cartas_en_juego; cont++,current = nextMap(Area_Final->cementerio)){
        eraseMap(Area_Final->cementerio,current->nombre);
        insertMap(Area_Final->mazo_castillo,current->nombre,current);
    }

    eraseMap(Area_Final->mano,card->nombre);
    insertMap(Area_Final->cementerio,card->nombre,card);

    system("pause");

}

void h_talisman_doce(carta* card){//vacio

}



void activarHabilidadTalisman(carta* card, int habilidad, Area_de_juego* area){
    system("cls");
    switch(habilidad){
        case(0):
            h_talisman_cero(card,area);
            break;
        case(1):
            h_talisman_uno(card,area);
            break;
        case(2):
            h_talisman_dos(card,area);
            break;
        case(3):
            h_talisman_tres(card,area);
            break;
        case(4):
            h_talisman_cuatro(card,area);
            break;
        case(5):
            h_talisman_cinco(card,area);
            break;
        case(6):
            h_talisman_seis(card, area);
            break;
        case(7):
            h_talisman_siete(card,area);
            break;
        case(8):
            h_talisman_ocho(card,area);
            break;
        case(9):
            h_talisman_nueve(card);
            break;
        case(10):
            h_talisman_diez(card);
            break;
        case(11):
            h_talisman_once(card,area);
            break;
        case(12):
            h_talisman_doce(card);
            break;
        default:
            break;

    }
}


