#ifndef FUNCIONESVIDEOJUEGO_V1
#define FUNCIONESVIDEOJUEGO_V1
#include "conio.h"
#include <iostream>

#define ARRIBA 72
#define ABAJO 80
#define IZQUIERDA 75
#define DERECHA 77

bool mapa_inicializado = false;
int coord_x_jugador = 2;
int coord_y_jugador = 5;

using namespace System;
// TODO: Implementar las funciones

//int Nivel_de_juego() {
//
//}



// Dibujos


/*
Colores para la la pantalla de presentacion
los colores se dibujan en funcion del valor entero en el arreglo.
(color del sesped) 0: verde oliva brillante -> #65a01e -> lo más parecido en ANSI \033[48;5;70m \033[0m
(color de las ramas) 1: gris marron claro -> #83786f -> en ANSI \033[48;5;102m \033[0m
(color del musgo) 2: verde oliva oscuro -> #4a5f41 -> en ANSI \033[48;5;58m \033[0m
(color del tronco de arbol) 3: marron oscuro -> #4e342e -> en ANSI \033[48;5;52m \033[0m
(color del interior del trnco) 4: marron terracota calido -> #A9745B -> en ANSI \033[48;5;137m \033[0m
(color de las letras del titulo) 5: gris azulado muy oscuro -> \033[48;5;235m \033[0m
*/
void Presentacion(int* matriz, int filas, int columnas) {
	Console::CursorVisible = false;
	for (int i = 0; i < filas; i++) {
		for (int j = 0; j < columnas; j++) {// barremos el arreglo en forma de una matriz
			Console::SetCursorPosition(j, i);//Establecemos sus cordenadas segun su pocision 

			switch (matriz[i * columnas + j]) {
			case 0: std::cout << "\033[48;5;70m \033[0m"; break;
			case 1: std::cout << "\033[48;5;102m \033[0m"; break;
			case 2: std::cout << "\033[48;5;58m \033[0m"; break;
			case 3: std::cout << "\033[48;5;52m \033[0m"; break;
			case 4: std::cout << "\033[48;5;137m \033[0m"; break;
			case 5: std::cout << "\033[48;5;235m \033[0m"; break;
			}
		}
	}
}

/*
Colores para mapa01
los colores se dibujan en funcion de un valor entero en el arreglo.
(color del borde) 0: marron oscuro -> #4e342e -> Lo mas parecido en ANSI \033[48;5;52m \033[0m
(colore del sesped) 1: verde brillante -> #21bf07 -> lo más parecido en ANSI \033[48;5;34m \033[0m
(color del camino) 2: arena claro -> #d2b48c -> lo más parecido en ANSI \033[48;5;180m \033[0m
*/

void Dibujar_Mapa(int* matriz, int filas, int columnas) {// argumentos, un arreglo por referencia, numero filas, numero de colunas
	for (int i = 0; i < filas; i++) {
		for (int j = 0; j < columnas; j++) {// barremos el arreglo en forma de una matriz
			Console::SetCursorPosition(j, i);//Establecemos sus cordenadas segun su pocision 

			switch (matriz[i * columnas + j]) {
			case 0: std::cout << "\033[48;5;52m \033[0m"; break;
			case 1: std::cout << "\033[48;5;34m \033[0m"; break;
			case 2: std::cout << "\033[48;5;180m \033[0m"; break;
			}
		}
		if (!mapa_inicializado) {
		mapa_inicializado = true;
		_sleep(200);
		}
	}
}
/*
Colores para dibujar personaje
Los colores se dibujaran en funcion de un valor entero en arreglo.
(piel del personaje) 3: durazno suave -> #ffd787 -> en ANSI \e[48;5;222m \e[0m
(polo del personaje) 4: blanco puro -> #ffffff -> en ANSI \033[48;5;231m \033[0m
(pantalon del personaje) 5: violeta azulado brillante -> #6f51ff -> en ANSI \033[48;5;99m \033[0m
(zapatos, zombrero y ojos) 6: negro puro -> #000000 -> en ANSI \033[48;5;16m \033[0m
*/
void Dibujar_jugador(int* matriz, int filas, int columnas) {
	for (int i = 0; i < filas; i++) {
		for (int j = 0; j < columnas; j++) {// barremos el arreglo en forma de una matriz
			Console::SetCursorPosition(j + coord_x_jugador, i + coord_y_jugador);//Establecemos sus cordenadas segun su pocision 

			switch (matriz[i * columnas + j]) {
			case -1: break;
			case 3: std::cout << "\033[48;5;222m \033[0m"; break;
			case 4: std::cout << "\033[48;5;231m \033[0m"; break;
			case 5: std::cout << "\033[48;5;99m \033[0m"; break;
			case 6: std::cout << "\033[48;5;16m \033[0m"; break;

			}
		}
	}
}
/*
Colores para dibujar personaje
(efecto del tronco) 6: negro puro -> #000000 -> en ANSI \033[48;5;16m \033[0m
(color del tronco) 7: marron oscuro -> #563416 -> en ANSI  \033[48;5;94m \033[0m
*/
void DibujarTronco(int* matriz, int filas, int columnas, int coord_x_tronco, int coord_y_tronco) {
	for (int i = 0; i < filas; i++) {
		for (int j = 0; j < columnas; j++) {
			Console::SetCursorPosition(j + coord_x_tronco, i + coord_y_tronco);
			switch (matriz[i * columnas + j]) {
			case 6: std::cout << "\033[48;5;16m \033[0m"; break;
			case 7: std::cout << "\033[48;5;99m \033[0m"; break;
			}
		}
	}
}

//void Dibujar_maquina(int* matriz, int filas, int columnas) {
//	for (int i = 0; i < filas; i++) {
//		for (int j = 0; j < columnas; j++) {
//			Console::SetCursorPosition(j, i);
//		}
//	}
//}

// Movimientos 
bool Leer_movimiento() {
	if (_kbhit()) {
		char t = _getch();
		if (t == ARRIBA) {
			coord_y_jugador--;
			return true;
		}
		if (t == ABAJO) {
			coord_y_jugador++;
			return true;
		}
		if (t == DERECHA) {
			coord_x_jugador++;
			return true;
		}
		if (t == IZQUIERDA) {
			coord_x_jugador--;
			return true;
		}

	}
	return false;
}

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
//Faslta provar esta funcion
bool Hay_colision(int obj01_x, int obj01_y,int heith_barra_de_colicion , int obj02_x, int obj02_y) {
	for (int i = obj01_y; i <= obj01_y + heith_barra_de_colicion; i++) {
		if (obj01_x == obj02_x && i == obj02_y) {
			return true;
		}
	}
	return false;
}

#endif
