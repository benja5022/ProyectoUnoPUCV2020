#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <conio.h>
#include <windows.h>
//#include <_mingw.h>


typedef struct carta carta;

/*
struct Area_de_juego{
    struct Area_de_juego * area_enemiga;
    char nombre_jugador[100];
    Mapa * cementerio;
    Mapa * mazo_castillo;
    Mapa * linea_defensa;
    Mapa * linea_ataque;
    Mapa * mano;
    unsigned int reserva_de_oro;
    unsigned int oro_pagado;
    pila * oros;
    lista * linea_de_apoyo;
    lista * destierro;
};
*/
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
void crearCarta(char * linea){
    carta * carta_nueva = (carta *) malloc (sizeof(carta));
    carta_nueva ->coste = atoi(get_csv_field(linea,7));
    carta_nueva ->fuerza = atoi(get_csv_field(linea,8));
    carta_nueva ->habilidad_arma = atoi(get_csv_field(linea,6)) ;
    carta_nueva ->habilidad_talisman = atoi(get_csv_field(linea,4));
    carta_nueva ->habilidad_totem = atoi(get_csv_field(linea,5));
    carta_nueva ->tipo = atoi(get_csv_field(linea,3));

//    printf("%d %d %d %d\n",carta_nueva ->coste, carta_nueva ->fuerza, carta_nueva ->tipo, carta_nueva ->habilidad_arma);
}
void comenzarPartida(){

}

void buscarPartida(){

}

void empezarJuego(){

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
            buscarPartida();
            break;
        case (2):
            comenzarPartida();
    }
    printf("Empezar juego opcion %d\n", bandera);
}

void reglas(){


}

void creditos(){
    int i;
    int j;
    for(i = 0; i<50; i++){
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

void menu(){
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

    printf("opcion = %d\n",bandera);

    switch(bandera){
        case(1):
            empezarJuego();
            break;

        case(2):
            reglas();
            break;

        case(3):
            creditos();
            break;
    }

}

int main()
{
    menu();
    return 0;
    FILE * archivo = fopen("ArchivoPrueba.csv","r");
    char palabra[1000];
    fgets(palabra,500,archivo);
    while(fgets(palabra,500,archivo)){

        crearCarta(palabra);
//        printf("%s %s %s %s %s %s %s pepito%d\n",get_csv_field(palabra,1),get_csv_field(palabra,2),get_csv_field(palabra,3),get_csv_field(palabra,4),get_csv_field(palabra,5),get_csv_field(palabra,6),get_csv_field(palabra,7),atoi(get_csv_field(palabra,8)));

    }
    fclose(archivo);

}
