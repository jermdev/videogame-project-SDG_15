#ifndef FUNCIONESVIDEOJUEGO_V1
#define FUNCIONESVIDEOJUEGO_V1
#include <iostream>

using namespace System;
// TODO: Implementar las funciones

//int Nivel_de_juego() {
//
//}
//
//// Dibujos
//void Presentacion() {
//
//}
//
//
void Dibujar_Mapa(int* matriz, int filas, int columnas) {// argumentos, un arreglo por referencia, numero filas, numero de colunas
	for (int i = 0; i < filas; i++) {
		for (int j = 0; j < columnas; j++) {// barremos el arreglo en forma de una matriz
			Console::SetCursorPosition(j, i);//Establecemos sus cordenadas segun su pocision 
			
			switch (matriz[i*columnas + j])
			{
			case 1: std::cout << "#"; break;//este es un ejemplo, en el case ira una accinacion del color del caracter segun su numero en el arreglo
			case 2: std::cout << "*"; break;
			default:
				std::cout << " ";
				break;
			}
		}
	}
}

//void Dibujar_jugador() {
//
//}
//
//// Movimientos 
//
//void Mover_Derecha() {
//
//}
//
//void Maver_Izquierda() {
//
//}
//
//void Saltar() {
//
//}
//
//// Parametros del juego
//
//int Numero_de_Vidas() {
//
//}
//
//bool Hay_colision() {
//
//}

#endif
