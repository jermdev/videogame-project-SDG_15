#ifndef FUNCIONESVIDEOJUEGO_V1
#define FUNCIONESVIDEOJUEGO_V1
#include "conio.h"
#include <iostream>

#define ARRIBA 72
#define ABAJO 80
#define IZQUIERDA 75
#define DERECHA 77

using namespace std;
using namespace System;

struct Poder {
	string nombre;
	bool avilitado;
};

// matrices de los mapas
int mapa01[] = {//Este es solo un ejemplo, falta implementar el mapa01
		2,2,2,2,2,2,2,2,
		2,2,2,2,2,2,2,2,
		2,2,2,2,2,2,2,2,
		2,2,2,2,2,2,2,2,
		2,2,2,2,2,2,2,2,
};

bool mapa_inicializado = false;
// dimenciones del jugador
int filas_jugador = 10;
int columnas_jugador = 15;

// cordenadas iniciales del jugador
int coord_x_jugador = 20;
int coord_y_jugador = 25;

//cordenadas iniciales de la maquina
int coord_x_maquina = 20;
int corrd_y_maquina = 25;

// Nivel del juego
int nivel_juego = 1;

//arreglo de los poderes
Poder arr_poderes[] = { {"romper tronco", false}, {"devolver tronco", false}};

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
void Dibujar_Presentacion(int* matriz, int filas, int columnas) {
	Console::CursorVisible = false;
	for (int i = 0; i < filas; i++) {
		for (int j = 0; j < columnas; j++) {// barremos el arreglo en forma de una matriz
			Console::SetCursorPosition(j, i);//Establecemos sus cordenadas segun su pocision 

			switch (matriz[i * columnas + j]) {
			case 0: cout << "\033[48;5;70m \033[0m"; break;
			case 1: cout << "\033[48;5;102m \033[0m"; break;
			case 2: cout << "\033[48;5;58m \033[0m"; break;
			case 3: cout << "\033[48;5;52m \033[0m"; break;
			case 4: cout << "\033[48;5;137m \033[0m"; break;
			case 5: cout << "\033[48;5;235m \033[0m"; break;
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

void Dibujar_Mapa(int* matriz, int filas, int columnas, int coords_x_iniciales = 0, int coords_y_iniciales = 0) {// argumentos, un arreglo por referencia, numero filas, numero de colunas, obsional coords inciales
	for (int i = 0; i < filas; i++) {
		for (int j = 0; j < columnas; j++) {// barremos el arreglo en forma de una matriz
			Console::SetCursorPosition(j + coords_x_iniciales, i + coords_y_iniciales);//Establecemos sus cordenadas segun su pocision 

			switch (matriz[(coords_y_iniciales + (i * columnas)) + (j + coords_x_iniciales)]) {
			case 0: cout << "\033[48;5;52m \033[0m"; break;
			case 1: cout << "\033[48;5;34m \033[0m"; break;
			case 2: cout << "\033[48;5;180m \033[0m"; break;
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
			case 3: cout << "\033[48;5;222m \033[0m"; break;
			case 4: cout << "\033[48;5;231m \033[0m"; break;
			case 5: cout << "\033[48;5;99m \033[0m"; break;
			case 6: cout << "\033[48;5;16m \033[0m"; break;

			}
		}
	}
}
/*
Colores para dibujar el tronco
(efecto del tronco) 6: negro puro -> #000000 -> en ANSI \033[48;5;16m \033[0m
(color del tronco) 7: marron oscuro -> #563416 -> en ANSI  \033[48;5;94m \033[0m
*/
void DibujarTronco(int* matriz, int filas, int columnas, int coord_x_tronco, int coord_y_tronco) {
	for (int i = 0; i < filas; i++) {
		for (int j = 0; j < columnas; j++) {
			Console::SetCursorPosition(j + coord_x_tronco, i + coord_y_tronco);
			switch (matriz[i * columnas + j]) {
			case 6: cout << "\033[48;5;16m \033[0m"; break;
			case 7: cout << "\033[48;5;99m \033[0m"; break;
			}
		}
	}
}

/*
Colores para dibujar la maquina
(bordes de la maquina) 6: negro puro -> #000000 -> en ANSI \033[48;5;16m \033[0m
(color del tronco) 7: marron oscuro -> #563416 -> en ANSI  \033[48;5;94m \033[0m
(cabeza de la mquina) 8: gris oscuro -> #4a4545 -> en ANSI \033[48;5;59m \033[0m
(ventana de la maquina) 9: verde menta muy claro -> #c1f1e6 -> en ANSI \033[48;5;159m \033[0m
(segunda tonalidad de la ventana de la maquina) 10: verde azulado grisásceo suave -> #9abeb9 -> en ANSI \033[48;5;152m \033[0m
(luces de la maquina) 11: rojo puro -> #ff0000 -> en ANSI \033[48;5;196m \033[0m
(luces de la maquina) 12: verde lima -> #40ff00 -> en ANSI \033[48;5;118m \033[0m

*/
void Dibujar_maquina(int* matriz, int filas, int columnas) {
	for (int i = 0; i < filas; i++) {
		for (int j = 0; j < columnas; j++) {
			Console::SetCursorPosition(j + coord_x_maquina, i + corrd_y_maquina);
			switch (matriz[i* columnas + j]) {
			case -1: break;
			case 6: cout << "\033[48;5;16m \033[0m"; break;
			case 7: cout << "\033[48;5;94m \033[0m"; break;
			case 8: cout << "\033[48;5;59m \033[0m"; break;
			case 9: cout << "\033[48;5;159m \033[0m"; break;
			case 10:cout << "\033[48;5;152m \033[0m"; break;
			case 11:cout << "\033[48;5;196m \033[0m"; break;
			case 12:cout << "\033[48;5;118m \033[0m"; break;
			}
		}
	}
}
/*
Colores para dibujar el arbol
 
(color del tronco) 7: marron oscuro -> #563416 -> en ANSI  \033[48;5;94m \033[0m
(color del musgo) 13: verde oliva oscuro -> #4a5f41 -> en ANSI \033[48;5;58m \033[0m

*/


void DibujarArbol(int* matriz, int filas, int columnas, int coord_x_arbol, int coord_y_arbol) {
	for (int i = 0; i < filas; i++) {
		for (int j = 0; j < columnas; j++) {
			Console::SetCursorPosition(j + coord_x_arbol, i + coord_y_arbol);
			switch (matriz[i * columnas + j]) {
			case -1:break;
			case 7: std::cout << "\033[48;5;94m \033[0m"; break; // Marrón (tronco)
			case 13: cout << "\033[48;5;58m \033[0m"; break; // Verde oliva oscuro(hojas)
			}
		}
	}
}


void dibujarperdiste(int* matriz, int filas, int columnas) {
	Console::CursorVisible = false;
	for (int i = 0; i < filas; i++) {
		for (int j = 0; j < columnas; j++) {
			Console::SetCursorPosition(j, i);
			switch (matriz[i * columnas + j]) {
			case 0: cout << "\033[48;5;88m \033[0m"; break;   // borde rojo oscuro
			case 1: cout << "\033[48;5;196m \033[0m"; break;  // fondo rojo brillante
			}
		}
	}
}

// mostrar el mensaje game over
void mostrarperdiste() {
	Console::SetCursorPosition(30, 2);
	cout << "UPS! LO SENTIMOS";
	Console::SetCursorPosition(30, 4);
	cout << "HAS PERDIDO";
	Console::SetCursorPosition(30, 6);
	cout << "INTENTALO DENUEVO";
}

// dibujar ventana de ganaste
void dibujarganaste(int* matriz, int filas, int columnas) {
	Console::CursorVisible = false;
	for (int i = 0; i < filas; i++) {
		for (int j = 0; j < columnas; j++) {
			Console::SetCursorPosition(j, i);
			switch (matriz[i * columnas + j]) {
			case 0: cout << "\033[48;5;22m \033[0m"; break;   // borde verde oscuro
			case 1: cout << "\033[48;5;120m \033[0m"; break;  // fondo verde claro
			}
		}
	}
}

// mostrar el mensaje cuando gana rl nivel
void mostrarganaste() {
	Console::SetCursorPosition(30, 2);
	cout << "FELICITACIONES";
	Console::SetCursorPosition(30, 4);
	cout << "HAS SUPERADO";
	Console::SetCursorPosition(30, 6);
	cout << "EL NIVEL";
}

// mostrar instrucciones 
void mostrarinstrucciones() {
	Console::SetCursorPosition(30, 2);
	cout << "INSTRUCCIONES";
	Console::SetCursorPosition(2, 4);
	cout << "1. Los controles para moverse son: W A S D";
	Console::SetCursorPosition(2, 6);
	cout << "2. El jugador comenzara con 3 vidas.";
	Console::SetCursorPosition(2, 8);
	cout << "3. Los poderes disponibles son: Destruir troncos, Revertir trayectoria.";
	Console::SetCursorPosition(2, 10);
	cout << "4. Por cada 3 troncos destruidos hay una posibilidad que aparesca un castor";
	Console::SetCursorPosition(5, 11);
	cout << "y te entrege una vida extra.";
	Console::SetCursorPosition(2, 13);
	cout << "5. El jugador tiene que esquivar los troncos, y por cada uno que le choque";
	Console::SetCursorPosition(5, 14);
	cout << "perdera una vida. ";
	Console::SetCursorPosition(2, 16);
	cout << "6. En el primeri nivel el jugador tendra que esquivar troncos, y por cada 5 ";
	Console::SetCursorPosition(5, 17);
	cout << "troncos que esquive podra lanzar un poder para destruir los troncos.";
	Console::SetCursorPosition(2, 19);
	cout << "7. Cuando se destruye un tronco se planta un arbol automaticamente.";
	Console::SetCursorPosition(2, 21);
	cout << "8. Los niveles se pasan plantando 5 arboles.";
	Console::SetCursorPosition(2, 23);
	cout << "9. En el segundo nivel el jugador tendra otro poder que le permitira revertir";
	Console::SetCursorPosition(5, 24);
	cout << "la direccion de los troncos para poder destruir la maquina enemiga. ";
	Console::SetCursorPosition(2, 26);
	cout << "10. La maquina enemiga tiene 5 vidas por cada tronco que le choca pierde una.";
	Console::SetCursorPosition(2, 28);
	cout << "11. En el segundo nivel por cada 5 troncos que esquive el jugador este";
	Console::SetCursorPosition(6, 29);
	cout << "obtendra un poder el cual revierte la direccion de los troncos";
}

// dibujar instrucciones
void dibujarinstrucciones(int* matriz, int filas, int columnas) {
	for (int i = 0; i < filas; i++) {
		for (int j = 0; j < columnas; j++) {
			Console::SetCursorPosition(j, i);
			switch (matriz[i * columnas + j]) {
			case 0: cout << "\033[48;5;52m \033[0m"; break;
			case 1: cout << "\033[48;5;17m \033[0m"; break;
			}
		}
	}
}

// Movimientos 
bool Leer_movimiento(int* mapa) {
	if (_kbhit()) {
		char t = _getch();
		if (t == ARRIBA) {

			Dibujar_Mapa(mapa, filas_jugador, columnas_jugador, coord_x_jugador, coord_y_jugador);//Esta linea se encarga de rellenar las pociciones anteriores del jugador con el mapa

			coord_y_jugador--;
			return true;
		}
		if (t == ABAJO) {
			Dibujar_Mapa(mapa, filas_jugador, columnas_jugador, coord_x_jugador, coord_y_jugador);

			coord_y_jugador++;
			return true;
		}
		if (t == DERECHA) {
			Dibujar_Mapa(mapa, filas_jugador, columnas_jugador, coord_x_jugador, coord_y_jugador);

			coord_x_jugador++;
			return true;
		}
		if (t == IZQUIERDA) {
			Dibujar_Mapa(mapa, filas_jugador, columnas_jugador, coord_x_jugador, coord_y_jugador);

			coord_x_jugador--;
			return true;
		}

	}
	return false;
}



void Avilitar_desavilitar_poderes(string poder, bool accion) {
	for (int i = 0; i < sizeof(arr_poderes); i++) {
		if (arr_poderes[i].nombre == poder) {
			arr_poderes[i].avilitado = accion;
		}
	}
}


bool Hay_colision(int obj01_x, int obj01_y,int heith_barra_de_colicion , int obj02_x, int obj02_y) {
	for (int i = obj01_y; i <= obj01_y + heith_barra_de_colicion; i++) {
		if (obj01_x == obj02_x && i == obj02_y) {
			return true;
		}
	}
	return false;
}

// cambiar el valor de las vidas y mostrar la actualizacion
void vidas(int colision, int matriz[], int filas, int columnas) {
	static int vidas = 3; // Empieza con 3 vidas

	switch (colision) {
	case 1: // Gana una vida
		vidas++;
		break;
	case 2: // Pierde una vida
		vidas--;
		break;
	}

	// Mostrar el número de vidas actuales en pantalla
	Console::SetCursorPosition(3, 2);
	cout << "\033[0;97mVIDAS: " << vidas << "   \033[0m"; // texto blanco


	if (vidas <= 0) {  // si llega a 0 muestra la pantalla de perdiste
		dibujarperdiste(matriz, filas, columnas);
		mostrarperdiste();
	}
}

#endif