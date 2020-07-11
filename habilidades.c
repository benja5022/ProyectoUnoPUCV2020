#include <stdio.h>
#include "habilidades.h"

void imprimirHabilidadTotem(int habilidad){
    switch(habilidad){
        case(0):
            printf("Tus Aliados ganan 2 a la fuerza.");
            break;
        case(1):
            printf("Una vez cada turno se barajan 2 cartas del cementerio al mazo castillo.");
            break;
        case(2):
            printf("Destruye un totem enemigo.");
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
            printf("Una vez por turno, Baraja 2 cartas de tu cementerio en tu castillo y robar una carta.");
            break;
        case(7):
            printf("Una vez por turno, puedes generar 2 oros para jugar Totem.");
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
            printf("Cuando entra en juego todas las armasdel cementerio pasan a la mano");
            break;
        case(4):
            printf("Una vez por turno, puedes desterrar una carta del cementerio");
            break;
        case(5):
            printf("En tu vigilia,Una vez por turno, un Jugador bota tantas cartas como aliados controles");
            break;
        case(6):
            printf("Una vez por turno, puedes desterrar un aliado de tu mano para buscar en tu castillo o cementerio y ponerlo en tu mano");
            break;
        case(7):
            printf("Cada vez que el portador haga daño de combate a un castillo oponente, pudes ganar el control de un aliado oponente");
            break;

    }
}


