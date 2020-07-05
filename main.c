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
#include "funciones.c"
//#include <_mingw.h>


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

    HashTable* TablaHash = createHashTable(stringHash,stringEqual);
    list* lista_todas_las_cartas = list_create_empty();
    FILE * archivo = fopen("Edición\\Cartas2.csv","r");
    if(archivo == NULL){
        printf("falla");
        return 1;
    }

    char palabra[1000];
    fgets(palabra,500,archivo);
    carta* Tarjeta = NULL;

    while(fgets(palabra,1000,archivo)){

//        printf("%s\n",palabra);
        Tarjeta = crearCarta(palabra);
        list_push_back(lista_todas_las_cartas,Tarjeta);
//        printf("%s\n",Tarjeta->nombre);
        insertHashTable(TablaHash ,Tarjeta->nombre,Tarjeta);
//        printf("%s %s %s %s %s %s %s pepito%d\n",get_csv_field(palabra,1),get_csv_field(palabra,2),get_csv_field(palabra,3),get_csv_field(palabra,4),get_csv_field(palabra,5),get_csv_field(palabra,6),get_csv_field(palabra,7),atoi(get_csv_field(palabra,8)));
    }

    fclose(archivo);
//    elegirCartas(TablaHash,lista_todas_las_cartas);
//    return 0;

    //carta * current = firstHashTable(TablaHash);
    //for(; current != NULL; current = nextHashTable(TablaHash)) printf ("%s\n", current ->nombre);
//    printf("%ld",HashTableCount(TablaHash));
    Area_de_juego* area_final = NULL;
    int bandera =0;
    do{
        bandera = menu(TablaHash);

        switch(bandera){
            case(1):
                area_final = empezarJuego(TablaHash,lista_todas_las_cartas);
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
        }

    }while(area_final == NULL);

//    printf("%s", area_final->nombre_jugador);
    return 0;

}
