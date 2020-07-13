#include "funciones.h"

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

//    strcpy(carta_nueva->id,get_csv_field(linea,1));
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
//    int boton2;
    gotoxy(41,10);
    printf("   BIENVENIDOS A MITOS & LEYENDAS   \n\n");
    //menu inicio
//    do{
    printf("                                                   INSTRUCCIONES            \n");
    printf("                                               W,A,D y S para moverse          \n");
    printf("                                                ENTER para selecionar        \n\n");
    //printf("                                      presione cualquier boton para comenzar\n");
    //scanf("%d",&boton2);
    system("pause");
//    }while(boton2<0);

}

void imprimirCaracteristicas(carta* card, carta* arma){

    int tipo = card->tipo;

    switch(tipo){
        case(0):
            printf("Caracteristicas:\n\n");
            printf("Nombre: %s\n",card->nombre);
            printf("Fuerza: %d\n",card->fuerza);
            printf("Coste: %d\n",card->coste);
            printf("Tipo: ");
            imprimirTipoCarta(card->tipo,card);
            printf("Habilidad: No");
            break;
        case(1):
            printf("Caracteristicas:\n\n");
            printf("Nombre: %s\n",card->nombre);
            printf("Fuerza: %d\n",card->fuerza);
            printf("Coste: %d\n",card->coste);
            printf("Tipo: ");
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
            printf("Caracteristicas:\n\n");
            printf("Nombre: %s\n",card->nombre);
            printf("Fuerza: %d\n",card->fuerza);
            printf("Coste: %d\n",card->coste);
            printf("Tipo: ");
            imprimirTipoCarta(card->tipo,card);
            printf("Habilidad: ");
            imprimirHabilidadTalisman(card->habilidad_talisman);
            break;
        case(3):
            printf("Caracteristicas:\n\n");
            printf("Nombre: %s\n",card->nombre);
            printf("Fuerza: %d\n",card->fuerza);
            printf("Coste: %d\n",card->coste);
            printf("Tipo: ");
            imprimirTipoCarta(card->tipo,card);
            printf("Habilidad: ");
            imprimirHabilidadArma(card->habilidad_arma);
            break;
        case(4):
            printf("Caracteristicas:\n\n");
            printf("Nombre: %s\n",card->nombre);
            printf("Fuerza: %d\n",card->fuerza);
            printf("Coste: %d\n",card->coste);
            printf("Tipo: ");
            imprimirTipoCarta(card->tipo,card);
            printf("Habilidad: ");
            imprimirHabilidadTotem(card->habilidad_totem);
            break;


    }

//    gotoxy(1,20);

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
    //*************
    system("cls");
    int newcont = 1;
    int i = 0;
    Map* lista_cartas_escogidas= createMap(cmp_str_map);
    carta* current = list_first(lista_todas_las_cartas);
    carta* aux = NULL;

    int paginas;
    int pagina_actual = 1;


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
                //if(newcont == 1) newcont = cantCarxpag;
                if(newcont == 1) newcont = cantCarxpag;
                else newcont--;
                break;
            case('s'):

                if(newcont == cantCarxpag) newcont = 1;
                //if(newcont == cantCarxpag) newcont = 1
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
                    //list_push_front(lista_cartas_escogidas,aux);
                    cartas_escogidas++;
                }
                system("cls");
                printf("Cartas Escogidas: %d\n\n", cartas_escogidas);
                imprimirLista(lista_todas_las_cartas,pagina_actual);
                //newcont = 1;
                break;
        }

    }

    return lista_cartas_escogidas;
}

void reglas(){

    list* reglamento = list_create_empty();
    FILE* reglamentos = fopen ("Instrucciones//reglas.csv","r");
    char linea [1000];

    if(reglamento == NULL){
        printf("NO");
        system("pause");
    }

    while (fgets (linea,1000, reglamentos)){
        char* nombre;// = (char*) malloc (sizeof(char)*1000);
        nombre = get_csv_field(linea,1);
        regla *r = crear_reglas(nombre);

        list_push_back(reglamento,r);
    }

    system("cls");

    regla* aux = list_first(reglamento);

//    int boton=1;
    char tecla;
    int cont = 0;
    char copia[1000];
    strcpy(copia,aux->nombre);
    strcat(copia,".txt");

    while(aux!=NULL){

        FILE *fp = fopen(copia,"r");
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

        strcpy(copia,aux->nombre);
        strcat(copia,".txt");
        system("cls");
    }

}

regla* crear_reglas (char* nombre){

    regla *r = malloc (sizeof(regla));
    r->nombre= nombre;
    return r;

}



void creditos(){
    int i;
    int j;
    for(i = 0; i<25; i++){
        for(j=0 ; j< i; j++){
            printf("\n");
        }

        printf("%60s","------Creadores------\n");
        printf("%65s","Benjamin Ignacio Rojas Henriquez\n");
        printf("%64s","Matias Ezequiel Osorio Quinones\n");
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

//    printf("cont =%d\n",MapCount(lista1));
//    printf("cont =%d\n",MapCount(lista2));

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

//    printf("%ld %ld %ld %ld %ld %ld %ld %ld\n", MapCount(Area1->mano), list_size(Area1->destierro), Area1->reserva_de_oro, MapCount(Area1->cementerio), MapCount(Area1->linea_defensa), MapCount(Area1->mazo_castillo), list_size(Area1->linea_de_apoyo), Area1->total);
//    printf("%ld %ld %ld %ld %ld %ld %ld %ld\n", MapCount(Area2->mano), list_size(Area2->destierro), Area2->reserva_de_oro, MapCount(Area2->cementerio), MapCount(Area2->linea_defensa), MapCount(Area2->mazo_castillo), list_size(Area2->linea_de_apoyo), Area2->total);
//
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
//        strcat(palabra_completa,"\n");
//        printf("\n%s\n",palabra_completa);

        while(fgets(linea,500,archivo_de_texto)){
//            printf("%s\n",linea);
            continue;
        }

        fprintf(archivo_de_texto,palabra_completa);
    }

    fclose(archivo_de_texto);
//    system("pause");
    return Area1;

}

void ingresoAreaDeJuego(Area_de_juego* area, carta* card, int zona, char* nombre_aliado, int posicion_aliado){ // acompañante :c

    carta* carta_duena = NULL;
    //printf("%s %d %d\n",nombre_aliado,posicion_aliado, zona);
   // system("pause");
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
                printf("carta duena no existe\n");
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


    //**********
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
    if(partida_salvada_escogida == NULL){
        printf("falla\n");
        return NULL;
    }

    fgets(current,100,partida_salvada_escogida);

//    printf("%s %s\n",get_csv_field(current,2),get_csv_field(current,3));
//    system("pause");


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
            //printf("%s\n",busqueda->nombre);
            //printf("->%s %s %s | %s\n\n",get_csv_field(current,1),get_csv_field(current,2),get_csv_field(current,3),area->nombre_jugador);
            //system("pause");

            if(strcmp(area->nombre_jugador , get_csv_field(current,1))== 0){
                zona = atoi(get_csv_field(current,3));
                strcpy(nombre_aliado,get_csv_field(current,4));
                zona_del_aliado = atoi(get_csv_field(current,5));
                ingresoAreaDeJuego(area,busqueda,zona,nombre_aliado,zona_del_aliado);
//                ingresoAreaDeJuego(area,busqueda,zona);
            }
            else
            {

                zona = atoi(get_csv_field(current,3));
                if(zona == 10){
                    printf("La bandera, %s",busqueda->nombre);
                    system("pause");
                    busqueda->tipo = atoi(get_csv_field(current,4));
                    busqueda->coste = atoi(get_csv_field(current,5));
                }
                strcpy(nombre_aliado,get_csv_field(current,4));
                zona_del_aliado = atoi(get_csv_field(current,5));
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

int menu(HashTable *tabla){
    char tecla;
    int cont = 1;
    int bandera = 0;
    system("cls");
    printf("Jugar\n");
    printf("Reglas\n");
    printf("Creditos\n");
    printf("Salir del Juego\n");

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
        case (3):
            printf("Atacar Volver\n");
            break;
        case (4):
            printf("Defender Volver\n");
            break;
    }

    char tecla;
    unsigned short cont = 1;
    unsigned short bandera = 0;

    while(bandera == 0){

        if(cont == 1){
            gotoxy(cont,9);
        }
        else
        {
            if(num == 0) gotoxy(cont + 6 , 9);
            else gotoxy(cont + 7 , 9);
        }

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

void imprimirMapa(Map* mapa){
    carta* current;
    for(current = firstMap(mapa);current != NULL ; current = nextMap(mapa)) printf("%s\n",current->nombre);
}

carta* verMano(Map* mano,int etapa){//, int etapa){
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

bool eleccionMapa(char tecla, Map * mapa, int* cont){
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
                system("pause");
                system("cls");
                printf("\n");
                imprimirMapa(mapa);
                break;
            case (8):
                return false;
                break;
        }
        return true;
}

bool eleccionLista(char tecla, list * lista, int* cont){
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
                system("pause");
                system("cls");
                printf("\n");
                for(current = list_first(lista); current; current = list_next(lista)) printf("%s\n",current->nombre);
                break;
            case (8):
                return false;
                break;
        }
    return true;

}

void imprimirMenucomenzarJuego(char* nombre){
    system("cls");
    printf("%45s%s","Nombre Jugador:",nombre);
    printf("\nVer Mano\n");//1 listo
    printf("Agrupar Oros\n");//2 listo
    printf("Agrupar aliados\n");//3 listo
    printf("Ver destierro\n");//4 listo
    printf("Ver destierro enemigo\n");//5
    printf("Ver linea de ataque\n");//6 listo
    printf("Ver linea de ataque enemiga\n");//7 //listo
    printf("Ver linea de defensa\n");//8 listo
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

void analizarYLanzarCarta(carta* card, Area_de_juego* area){ // incompleto
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
            break;
        case(3)://arma
            if(area->reserva_de_oro >= card->coste && MapCount(area->linea_defensa) > 0){
                if(escogerAliado(area->linea_defensa,card)){
                    eraseMap(area->mano,card->nombre);
                    system("cls");
                    printf("Le has puesto una arma al aliado\n");
                    system("pause");
                }
                else
                {
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

void verLineaAtaqueEnemigo(Area_de_juego* Area){
    system("cls");
    if(MapCount(Area->area_enemiga->linea_ataque) == 0){
        printf("El usuario rival no tiene Cartas en la linea de ataque\n");
        system("pause");
        return;
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

        if(!eleccionMapa(tecla,lineaAtaque,&cont)) return;
    }

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

        if(!eleccionMapa(tecla,ataque,&cont)){
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
        if(!eleccionLista(tecla,destierro,&cont)) return;

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
                    case (0): // atacar
                        if(opcionesCarta(3))
                        {
                            //comenzarAtaque(Area,current);
                            return current;
                        }
                        break;
                    case (1): // defender
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

void descartarCarta(Area_de_juego* area){
    system("cls");
    printf("Tienes mas de 8 cartas, debes descartar una\\s carta\\s\n");
    system("pause");
    system("cls");
    Map* mano = area -> mano;

    carta* current = NULL;// = firstMap(mano);
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
                if(descartarOpciones()){
                    eraseMap(mano,current->nombre);
                    insertMap(area->mazo_castillo,current->nombre,current);
                    bandera = 1;
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
        //_popFront(mazo);

        tmp = firstMap(mazo);

    }

    float max = RAND_MAX;

    for( i = 0; i < 50 ; i++){

        desp=i;
        //Genero un numero aleatorio

        indice = (rand()/max * (50 - i)) + desp;
        //Intercambio valores de variables
        tmp=arreglocartas[i];
        arreglocartas[i]=arreglocartas[indice];
        arreglocartas[indice]=tmp;

    }

    for(i = 0 ; i < 50 ; i++){

        insertMap(mazo , arreglocartas[i]->nombre , arreglocartas[i]);

    }

    free(arreglocartas);

    return ;

}

void verLineaDeDefensaEnemiga(Area_de_juego *Area){

    system("cls");
    if(MapCount(Area->area_enemiga->linea_defensa) == 0){
        printf("El usuario rival no tiene Cartas en la linea de Defensa\n");
        system("pause");
        return;
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

        if(!eleccionMapa(tecla,lineaDefensa,&cont)) return;
    }

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
        if(!eleccionLista(tecla,destierro,&cont)) return;

    }

}

void verLineaDeApoyoEnemigo(Area_de_juego* Area){
    system("cls");
    printf("\n");

    if(list_size(Area->area_enemiga->linea_de_apoyo) == 0){
        printf("Tu oponente no tiene Cartas en la linea de apoyo\n");
        system("pause");
        return;
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
        if(!eleccionLista(tecla,apoyo,&cont)) return;

    }
}

void verLineaDeApoyo(Area_de_juego* Area){
    system("cls");
    printf("\n");

    if(list_size(Area->area_enemiga->linea_de_apoyo) == 0){
        printf("No tienes Cartas en la linea de apoyo\n");
        system("pause");
        return;
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

                        activarHabilidadTotem(current,current->habilidad_totem,Area);

                }
                //system("pause");
                system("cls");
                printf("\n");
                for(current = list_first(apoyo); current; current = list_next(apoyo)) printf("%s\n",current->nombre);
                break;
            case (8):
                return;
                break;

        }

    }
}

const char* ImpresionPartidaCSVsa(char* palabra, char * nombre_jugador,char* nombre_carta ,char lugar){
    palabra[0] = ',';
    palabra[1] = '\0';
    strcat(palabra,nombre_jugador);
    strcat(palabra,",");
    strcat(palabra,nombre_carta);
    strcat(palabra,",");
    int numero = strlen(palabra);
    palabra[numero] = lugar;
    palabra[numero+1] = '\0';

    strcat(palabra,",nada,0,\n");

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

void escribirEnArchivoCSV(Area_de_juego* area, FILE* archivo){
    carta* current = NULL;
    char palabra[200];

    while(stack_size(area->oros) > 0){//*******
        current = stack_pop(area->oros);
        if(area->reserva_de_oro > 0){
            area ->reserva_de_oro--;
            strcpy(palabra, ImpresionPartidaCSVsa(palabra,area->nombre_jugador,current->nombre,'3'));

            fprintf(archivo,palabra);
        }
        else
        {
            strcpy(palabra, ImpresionPartidaCSVsa(palabra,area->nombre_jugador,current->nombre,'4'));

            fprintf(archivo,palabra);
        }
    }

    current = lastMap(area->cementerio);
    while(MapCount(area->cementerio) > 0 && current!= NULL){
        ImpresionPartidaCSVsa(palabra,area->nombre_jugador,current->nombre,'0');

        fprintf(archivo,palabra);
        current = prevMap(area->cementerio);
    }

    removeAllMap(area->cementerio);

    current = lastMap(area->mano);
    while(MapCount(area->mano) > 0 && current!= NULL ){
        ImpresionPartidaCSVsa(palabra,area->nombre_jugador,current->nombre,'2');

        fprintf(archivo,palabra);
        current = prevMap(area->mano);
    }
    removeAllMap(area->mano);
//********************************************************
    current = lastMap(area->linea_ataque);
    while(MapCount(area->linea_ataque) > 0 && current!= NULL){

        if(current->arma != NULL){
            printf("%s\n",current->arma->nombre);
            system("pause");
            ImpresionPartidaCSVsa(palabra,area->nombre_jugador,current->nombre,'6');

            fprintf(archivo,palabra);

            ImpresionPartidaCSVca(palabra,area->nombre_jugador,current->arma->nombre,'9',current->nombre,'6');
            fprintf(archivo,palabra);
            current->arma = NULL;
        }
        else
        {
            ImpresionPartidaCSVsa(palabra,area->nombre_jugador,current->nombre,'6');
            fprintf(archivo,palabra);
        }

        current = prevMap(area->linea_ataque);
    }
    removeAllMap(area->linea_ataque);

    current = lastMap(area->linea_defensa);
    while(MapCount(area->linea_defensa) > 0 && current!= NULL){
        if(current->arma != NULL){
//            printf("%s\n",current->arma->nombre);
//            system("pause");
            ImpresionPartidaCSVsa(palabra,area->nombre_jugador,current->nombre,'5');

            fprintf(archivo,palabra);

            ImpresionPartidaCSVca(palabra,area->nombre_jugador,current->arma->nombre,'9',current->nombre,'5');
            fprintf(archivo,palabra);
            current->arma = NULL;
        }
        else
        {

            ImpresionPartidaCSVsa(palabra,area->nombre_jugador,current->nombre,'5');
            fprintf(archivo,palabra);
        }
        current = prevMap(area->linea_defensa);
    }
    removeAllMap(area->linea_defensa);
    //**********

    current = list_last(area->destierro);
    while(list_size(area->destierro) > 0 && current!= NULL){
        current = list_pop_back(area->destierro);
        ImpresionPartidaCSVsa(palabra,area->nombre_jugador,current->nombre,'8');

        fprintf(archivo,palabra);
    }
    area->destierro = NULL;

    current = list_last(area->linea_de_apoyo);
    while(list_size(area->linea_de_apoyo) > 0 && current!= NULL){
        current = list_pop_back(area->linea_de_apoyo);

        ImpresionPartidaCSVsa(palabra,area->nombre_jugador,current->nombre,'7');
        fprintf(archivo,palabra);
    }
    area->linea_de_apoyo = NULL;

    current = lastMap(area->mazo_castillo);
    while(MapCount(area->mazo_castillo) > 0 && current!= NULL){
        if(strcmp(current->nombre,"Bandera") == 0){

            fprintf(archivo,",%s,%s,%s,%c,%c,",area->nombre_jugador,"Bandera","10",current->tipo+48,current->coste+48);
            current = prevMap(area->mazo_castillo);
        }
        else
        {
            ImpresionPartidaCSVsa(palabra,area->nombre_jugador,current->nombre,'1');

            fprintf(archivo,palabra);
            current = prevMap(area->mazo_castillo);
        }


    }
    removeAllMap(area->mazo_castillo);
}

void guardarPartida(Area_de_juego* area){//**********

    system("cls");

    char direccion[200];
    strcpy(direccion,"Partidas\\");
    strcat(direccion,area->nombre_partida);
    strcat(direccion,".csv");

    FILE * archivo = fopen(direccion,"w");

    fprintf(archivo,",%s,%s,%s,nada,0,\n",area->nombre_partida,area->nombre_jugador,area->area_enemiga->nombre_jugador);
    escribirEnArchivoCSV(area,archivo);
    escribirEnArchivoCSV(area->area_enemiga,archivo);
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

                descartarCarta(Area_final);

            }while(MapCount(Area_final->mano) > 8);
        }
    }

}

void moverAliadoDeLugar(Map* mapa1, carta* card, Map* mapa2){
    char* nombre = card->nombre;
    char idcaracter = nombre[strlen(nombre)-1];
    nombre[strlen(nombre)-1] = 64;

    eraseMap(mapa1,card->nombre);

    insertMap(mapa2,card->nombre,card);

    nombre[strlen(nombre)-1] = idcaracter;
}



void eliminarAliado(Map* linea_de_defensa,carta* card,Map* cementerio){ // El aliado debe Pertenecer a la linea de defensa y al cementerio
    char* nombre = card->nombre;
    char idcaracter = nombre[strlen(nombre)-1];
    nombre[strlen(nombre)-1] = 64;

    eraseMap(linea_de_defensa,card->nombre);
    nombre[strlen(nombre)-1] = idcaracter;

    card->estado = false;

    if(card->arma){
        insertMap(cementerio,card->arma->nombre,card->arma);
        card->arma = NULL;
    }
    insertMap(cementerio,card->nombre,card);
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
//        printf("%d",card->arma->habilidad_arma);
//        system("pause");
        activarHabilidadArma(card->arma,card->arma->habilidad_arma,Area_final);
    }
    comenzarDefensa(Area_final->area_enemiga,card);
    //imprimirCaracteristicas(card,card->arma);
}

void comenzarDefensa(Area_de_juego* Area_final, carta* carta_enemiga){

    gotoxy(35,15);
    printf("Defensa Realizada por %s",Area_final->nombre_jugador);
    gotoxy(1,20);
    printf("(Recuerda que solo puedes utlizar Talismanes o Defenderte con algún aliado de tu linea de defensa)\n");
    gotoxy(1,26);
    system("pause");
    system("cls");

    printf("\nVer Mano\nVer Caracteristicas del Aliado Enemigo\nVer Linea de defensa\nDejarse Atacar");

    char tecla;
    int bandera = 0;
    int cont = 1;
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
                                activarHabilidadArma(defensa->arma,defensa->arma->habilidad_arma,Area_final);
                            }

                            diferencia = defensa->fuerza - carta_enemiga->fuerza;

                            if(diferencia > 0){
                                printf("Destruiste al Aliado Enemigo\n");

                                eliminarAliado(Area_final->area_enemiga->linea_defensa,carta_enemiga,Area_final->area_enemiga->cementerio);

                            }

                            if(diferencia < 0){
                                system("cls");
                                printf("%d %d\n", MapCount(Area_final->mazo_castillo),MapCount(Area_final->cementerio));
                                printf("Han destruido a tu aliado y te han enviado %d cartas al cementerio\n",diferencia * -1);

                                moverAliadoDeLugar(Area_final->area_enemiga->linea_defensa,carta_enemiga,Area_final->area_enemiga->linea_ataque);

                                eliminarAliado(Area_final->linea_defensa,defensa,Area_final->cementerio);

                                defensa = firstMap(Area_final->mazo_castillo);

                                for(int i = 0; i < diferencia *-1 && defensa != NULL; i++,defensa = firstMap(Area_final->mazo_castillo)){
                                    eraseMap(Area_final->mazo_castillo,defensa->nombre);
                                    insertMap(Area_final->cementerio,defensa->nombre,defensa);
                                }
                                printf("%d %d\n", MapCount(Area_final->mazo_castillo),MapCount(Area_final->cementerio));
                            }

                            if(diferencia*-1 == 0){
                                printf("Ambos Aliados han sido Destuidos\n");

                                eliminarAliado(Area_final->area_enemiga->linea_defensa,carta_enemiga,Area_final->area_enemiga->cementerio);
                                eliminarAliado(Area_final->linea_defensa,defensa,Area_final->cementerio);

                            }

                            printf("pep");
                            system("pause");
                            return;
                        }

                        system("cls");
                        printf("\nVer Mano\nVer Caracteristicas del Aliado Enemigo\nVer Linea de defensa\nDejarse Atacar");
                        break;
                    case (4):

                        return ;//NULL;
                        break;

                }
        }

    }
}

void comenzarJuego(Area_de_juego* Area_final){

    imprimirMenucomenzarJuego(Area_final->nombre_jugador);

    char tecla;
    unsigned short bandera = 0;
    unsigned short b_agrupacion_oro = 0;//bandera si ya se agruparon los oros toma valor 1, sino toma valor 0
    unsigned short b_agrupacion_aliado = 0;
    unsigned short cont = 1;
    carta* cartaJugada = NULL;

    carta* estado_bandera = eraseMap(Area_final->area_enemiga->mazo_castillo,"Bandera");
    //eraseMap(Area_final->area_enemiga->mazo_castillo,"Bandera");
    if(estado_bandera == NULL){
        estado_bandera = crearCarta(",band,Bandera,0,0,0,0,0,0,");
        printf("Partida Nueva");
        system("pause");
    }
    else
    {
//        printf("La mea cagá");
//        system("pause");
        b_agrupacion_oro = estado_bandera->tipo;
        b_agrupacion_aliado = estado_bandera->coste;
    }

    do{
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
            case 4:
                verDestierro(Area_final);
                bandera = 0;
                break;
            case 5://Ver destierro enemigo
                verDestierroEnemigo(Area_final);
                bandera = 0;
                break;
            case 6:
                verLineaDeAtaque(Area_final);
                bandera = 0;
                break;
            case 7:
                verLineaAtaqueEnemigo(Area_final);
                bandera = 0;
                break;
            case 8:
                cartaJugada = NULL;
                cartaJugada = verLineaDeDefensa(Area_final,0);
                if(cartaJugada){
                    comenzarAtaque(Area_final,cartaJugada);
                    b_agrupacion_aliado = 1;
                }
                bandera = 0;
                break;
            case 9://Ver linea de defensa enemiga
                verLineaDeDefensaEnemiga(Area_final);
                bandera = 0;
                break;
            case 10://Ver linea de apoyo
                verLineaDeApoyo(Area_final);
                bandera = 0;
                break;
            case 11://Ver linea de apoyo enemiga
                verLineaDeApoyoEnemigo(Area_final);
                bandera = 0;
                break;

            case 12:
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
            case 13:
                estado_bandera->tipo = b_agrupacion_oro;
                estado_bandera->coste = b_agrupacion_aliado;

                //strcpy(estado_bandera->nombre,Area_final->area_enemiga->nombre_jugador);

                insertMap(Area_final->area_enemiga->mazo_castillo,estado_bandera->nombre,estado_bandera);

                guardarPartida(Area_final);
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

        imprimirMenucomenzarJuego(Area_final->nombre_jugador);

    }while(bandera != 10);

}

/*
void jugar_arma(Area_de_juego *areadejuego , carta *armajugada){    //poner un menu donde se pregunta a que aliado anexar el arma, luego alterar dicho alido de acuerdo al efecto del arma.

    carta *aliadoobjetivo = searchMap(areadejuego->linea_defensa,carta->nombre);
    carta *aux = NULL;
    switch(armajugada->habilidad_arma){

        case -1: return;

        case 0: aliadoobjetivo->fuerza++;
                return;

        case 1: aliadoobjetivo->fuerza++;
                return;

        case 2: aliadoobjetivo->fuerza++;
                return;

        case 3: carta *nav = firstMap(areadejuego->cementerio);
                carta *aux;
                while(nav != NULL){

                    if(nav->tipo == 3){

                        aux = nav;
                        nav = nextMap(areadejuego->cementerio);
                        insertMap(areadejuego->mano , aux->nombre , aux);
                        eraseMap(areadejuego->cementerio , aux->nombre);

                    }
                    else{

                        nav = nextMap(areadejuego->cementerio);

                    }

                }

    }

}*/
