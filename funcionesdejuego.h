#ifndef FUNCIONESDEJUEGO_H_INCLUDED
#define FUNCIONESDEJUEGO_H_INCLUDED

void guardarPartida(Area_de_juego* area, HashTable* hash);

void comenzarJuego(Area_de_juego* Area_final, HashTable* hash);

void comenzarAtaque(Area_de_juego* Area_final, carta* card);

void comenzarDefensa(Area_de_juego* Area_final, carta* carta_enemiga);

carta* verLineaDeDefensaEnemiga(Area_de_juego *Area,int modo);

void verDestierroEnemigo(Area_de_juego *Area);

carta * verLineaAtaqueEnemigo(Area_de_juego* Area, int modo);

void agruparOros(Area_de_juego* Area);

void agruparAliados(Area_de_juego* Area);

void verLineaDeAtaque(Area_de_juego* Area);

void verDestierro(Area_de_juego* Area);

carta* verLineaDeDefensa(Area_de_juego* Area,int etapa);

carta* verLineaDeApoyoEnemigo(Area_de_juego* Area, int modo);

#endif // FUNCIONESDEJUEGO_H_INCLUDED
