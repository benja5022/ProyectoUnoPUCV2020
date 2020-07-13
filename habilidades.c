#include <stdio.h>
#include "habilidades.h"
#include "funciones.h"


struct carta{

    int tipo;
    int coste;
    int habilidad_talisman;
    int habilidad_totem;
    int habilidad_arma;
    int fuerza;
    char nombre[100];
    struct carta * arma;
    bool estado; //si es bool, significa que ha sido usado

};

struct Partida{
    char nombre_partida[50];
    char nombre_Jugador1[50];
    char nombre_Jugador2[50];

};

struct Area_de_juego{
    struct Area_de_juego * area_enemiga;
    char nombre_jugador[100];
    char nombre_partida[100];
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
            printf("Destruye a un aliado oponente");
            break;
        case(1):
            printf("Saca Una carta del mazo");
            break;
        case(2):
            printf("Genera 3 oros");
            break;
        case(3):
            printf("Un jugador bota una carta por cada aliado en juego");
            break;
        case(4):
            printf("Destruye un Aliado");
            break;
        case(5):
            printf("Para jugar esta carta debes botar 5 cartas, Un jugador bota 5 cartas");
            break;
        case(6):
            printf("Roba 2 cartas de tu Mazo Castillo");
            break;
        case(7):
            printf("Los Aliados que controles ganan dos a la fuerza");
            break;
        case(8):
            printf("Roba 1 Carta de Tu mazo Castillo");
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


void h_totem_cero(carta* card){//vacio

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
    switch(habilidad){
        case(0):
            //h_totem_cero(card);
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


void h_arma_cero(carta* card){
    carta* carta_aliado = card->arma;
    carta_aliado->fuerza++;
}

void h_arma_uno(carta* card){
    carta* carta_aliado = card->arma;
    carta_aliado->fuerza+=2;
}

void h_arma_dos(carta* card){
    carta* carta_aliado = card->arma;
    carta_aliado->fuerza+=3;
}

void h_arma_tres(carta* card , Area_de_juego *Areafinal){

    carta *nav = firstMap(Areafinal->cementerio);

    while(nav != NULL){

        if(nav->tipo == 3){

            insertMap(Areafinal->mano , nav->nombre , nav);
            eraseMap(Areafinal->cementerio , nav->nombre);

        }

        nav = nextMap(Areafinal->cementerio);

    }

}
/*
void h_arma_cuatro(carta* card , Area_de_juego *Areafinal){// en el menu principal, crear un submenu preguntando si se quiere usar esta habilidad

    carta *current = NULL;
    imprimirMapa(Areafinal->area_enemiga->cementerio);

    unsigned short i;
    unsigned short cont = 1;
    char tecla;
    unsigned short bandera = 0;


    while(bandera == 0){
        gotoxy(1,cont+1);

        tecla = getch();

        switch(tecla){
            case ('w'):
                if(cont == 1) cont = MapCount(Areafinal->area_enemiga->cementerio);
                else cont--;

                break;
            case ('s'):
                if(cont == MapCount(Areafinal->area_enemiga->cementerio)) cont = 1;
                else cont++;
                break;
            case (13):
                for(i = 0, current = firstMap(Areafinal->area_enemiga->cementerio); i < cont-1 ; i++,current = nextMap(Areafinal->area_enemiga->cementerio));

                system("cls");
                imprimirCaracteristicas(current,current->arma);
                unsigned short sino = 1;
                printf("Desterrar esta carta?\n");
                printf("Si No\n");

                switch(tecla){

                    case ('a'):
                        if(sino == 1) sino = 2;
                        else sino--;
                        break;

                    case ('d'):
                        if(sino == 2) sino = 1;
                        else sino--;
                        break;

                    case (13):
                        if(sino == 1){
                            eraseMap(Areafinal->area_enemiga->cementerio , current->nombre);
                            return;
                        }

                        if(sino == 2){
                            imprimirMapa(Areafinal->area_enemiga->cementerio);
                        }

                        break;

                    case (8):
                        bandera == 1;
                        return;
                }
            }

        }

}*/
/*
void h_arma_tres(carta* card){//vacio

}
*/
void h_arma_cuatro(carta* card, Area_de_juego* area){//vacio

}

void h_arma_cinco(carta* card){//vacio

}

void h_arma_seis(carta* card){//vacio

}

void h_arma_siete(carta* card){//vacio

}

void activarHabilidadArma(carta* card, int habilidad, Area_de_juego* area){

    switch(habilidad){
        case(0):
            h_arma_cero(card);
            break;
        case(1):
            h_arma_uno(card);
            break;
        case(2):
            h_arma_dos(card);
            break;
        case(3):
            h_arma_tres(card,area);
            break;
        case(4):
            h_arma_cuatro(card,area);
            break;
        case(5):
            h_arma_cinco(card);
            break;
        case(6):
            h_arma_seis(card);
            break;
        case(7):
            h_arma_siete(card);
            break;

    }

}

void h_talisman_cero(carta* card){//vacio

}

void h_talisman_uno(carta* card){//vacio

}
void h_talisman_dos(carta* card){//vacio

}
void h_talisman_tres(carta* card){//vacio

}
void h_talisman_cuatro(carta* card){//vacio

}
void h_talisman_cinco(carta* card){//vacio

}
void h_talisman_seis(carta* card){//vacio

}
void h_talisman_siete(carta* card){//vacio

}
void h_talisman_ocho(carta* card){//vacio

}
void h_talisman_nueve(carta* card){//vacio

}
void h_talisman_diez(carta* card){//vacio

}
void h_talisman_once(carta* card){//vacio

}
void h_talisman_doce(carta* card){//vacio

}


void activarHabilidadTalisman(carta* card, int habilidad, Area_de_juego* area){
    switch(habilidad){
        case(0):
            h_talisman_cero(card);
            break;
        case(1):
            h_talisman_uno(card);
            break;
        case(2):
            h_talisman_dos(card);
            break;
        case(3):
            h_talisman_tres(card);
            break;
        case(4):
            h_talisman_cuatro(card);
            break;
        case(5):
            h_talisman_cinco(card);
            break;
        case(6):
            h_talisman_seis(card);
            break;
        case(7):
            h_talisman_siete(card);
            break;
        case(8):
            h_talisman_ocho(card);
            break;
        case(9):
            h_talisman_nueve(card);
            break;
        case(10):
            h_talisman_diez(card);
            break;
        case(11):
            h_talisman_once(card);
            break;
        case(12):
            h_talisman_doce(card);
            break;
        default:
            break;

    }
}


