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
#include "habilidades.c"
#include "funciones.c"



long long stringHash(const void * key) {
    long long hash = 5381;

    const char * ptr;

    for (ptr = key; *ptr != '\0'; ptr++) {
        hash = ((hash << 5) + hash) + tolower(*ptr); /* hash * 33 + c */
    }

    return hash;
}

int stringEqual(const void * key1, const void * key2) {
    const char * A = key1;
    const char * B = key2;

    return strcmp(A, B) == 0;
}

int main()
{
  //  imprimirHabilidadTalisman(5);
  //  system("pause");
 //   system("color 20");

    HashTable* TablaHash = createHashTable(stringHash,stringEqual);
    list* lista_todas_las_cartas = list_create_empty();
    FILE * archivo = fopen("Edición\\Cartas.csv","r");
    if(archivo == NULL){
        printf("falla");
        return 1;
    }

    char palabra[500];
    fgets(palabra,500,archivo);
    carta* Tarjeta = NULL;

    while(fgets(palabra,500,archivo)){
        //printf("%s\n",palabra);
        Tarjeta = crearCarta(palabra);
        list_push_back(lista_todas_las_cartas,Tarjeta);
        insertHashTable(TablaHash , Tarjeta->nombre ,Tarjeta);
    }

    fclose(archivo);

    //printf("fuera");

    Area_de_juego* area_final = NULL;
    int bandera =0;
    do{
        bandera = menu(TablaHash);

        switch(bandera){
            case(1):
                area_final = jugar(TablaHash,lista_todas_las_cartas);
                bandera = 0;
                break;

            case(2):
                reglas();
                bandera = 0;
                break;

            case(3):
                creditos();
                bandera = 0;
                break;
            case(4):
                return 0;
                break;
        }

        if(area_final != NULL){
            comenzarJuego(area_final);
            area_final = NULL;
        }
    }while(area_final == NULL);


    return 0;
}
