#ifndef FUNCIONESVIDEOJUEGO_V1
#define FUNCIONESVIDEOJUEGO_V1

#include "conio.h"
#include <iostream>
#include <windows.h>

#define ENTER 13

#define ARRIBA 72
#define ABAJO 80
#define IZQUIERDA 75
#define DERECHA 77

using namespace std;
using namespace System;


// variables iniciales


const int niveles_del_juego = 2;

//dimenciones tronco
int dimensiones_tronco_filas = 12, dimensiones_tronco_columnas = 4;

// cordenadas iniciales del jugador
const int coord_x_jugador = 20;
const int coord_y_jugador = 25;


bool mapa_inicializado = false;
// dimensiones del jugador
int filas_jugador = 19;
int columnas_jugador = 10;


//cordenadas iniciales de la maquina
int coord_x_maquina = 20;
int corrd_y_maquina = 25;

// Nivel del juego
int nivel_juego = 1;

// dimensiones de los mapas
int filas_mapa01 = 50, columnas_mapa01 = 80;
int filas_mapa02 = 50, columnas_mapa02 = 80;

// estructuras
struct Poder {
	string nombre;
	bool avilitado;
};

struct Cordenadas {
	int X;
	int Y;
};

struct Tronco {
	int tiempo_de_aparicion;
	bool activo;
	Cordenadas cordenadas;
};


struct Jugador {
	int vidas = 3;
	int troncos_esquivados = 0;
	int troncos_destruidos = 0;
	Cordenadas cordenadas = { coord_x_jugador, coord_y_jugador };
	Cordenadas Hitbox = { coord_x_jugador + 1, coord_y_jugador + 16 };
	int Hitbox_ancho = 8; // ancho de la hitbox del jugador
	int Hitbox_alto = 3; // alto de la hitbox del jugador
	Poder poderes[2] = { {"romper tronco", false}, {"devolver tronco", false} };
};

const int MAX_TRONCOS = 3;
Tronco troncos[MAX_TRONCOS];

Jugador jugador;


void gotoxi(int x, int y) {
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

//void maximizarConsola() {
//	HWND consola = GetConsoleWindow();
//	ShowWindow(consola, SW_MAXIMIZE); // Maximiza la ventana
//}


void configurarConsola() {
	int maxAncho = Console::LargestWindowWidth;
	int maxAlto = Console::LargestWindowHeight;
	Console::WriteLine("M�ximo permitido: {0}x{1}", maxAncho, maxAlto);
	Console::SetBufferSize(800, 800);  // columnas, filas
	Console::SetWindowSize(800, 800);  // columnas, filas
}



// Dibujos


/*
Colores para la la pantalla de presentacion
los colores se dibujan en funcion del valor entero en el arreglo.
(color del sesped) 0: verde oliva brillante -> #65a01e -> lo m�s parecido en ANSI \033[48;5;70m \033[0m
(color de las ramas) 1: gris marron claro -> #83786f -> en ANSI \033[48;5;102m \033[0m
(color del musgo) 2: verde oliva oscuro -> #4a5f41 -> en ANSI \033[48;5;58m \033[0m
(color del tronco de arbol) 3: marron oscuro -> #4e342e -> en ANSI \033[48;5;52m \033[0m
(color del interior del trnco) 4: marron terracota calido -> #A9745B -> en ANSI \033[48;5;137m \033[0m
(color de las letras del titulo) 5: gris azulado muy oscuro -> \033[48;5;235m \033[0m
*/
int position_flecha = 0;



void Dibujar_Presentacion(int* matriz, int filas, int columnas, int coords_x_iniciales = 0, int coords_y_iniciales = 0) {

	int coord_escribir_X = 40;
	int coord_escribir_Y = 20;

	Console::CursorVisible = false;
	for (int i = 0; i < filas; i++) {
		for (int j = 0; j < columnas; j++) {// barremos el arreglo en forma de una matriz
			gotoxi(j + coords_x_iniciales, i + coords_y_iniciales);//Establecemos sus cordenadas segun su posicion 

			switch (matriz[(coords_y_iniciales + (i * columnas)) + (j + coords_x_iniciales)]) {
			case 0: cout << "\033[48;5;70m \033[0m"; break;
			case 1: cout << "\033[48;5;102m \033[0m"; break;
			case 2: cout << "\033[48;5;58m \033[0m"; break;
			case 3: cout << "\033[48;5;52m \033[0m"; break;
			case 4: cout << "\033[48;5;137m \033[0m"; break;
			case 5: cout << "\033[48;5;235m \033[0m"; break;
			}
		}

	}

	cout << "\033[48;5;102m\033[30m";
	gotoxi(coord_escribir_X, coord_escribir_Y);
	cout << "JUGAR";

	gotoxi(coord_escribir_X, coord_escribir_Y + 5);
	cout << "Instrucciones";

	gotoxi(coord_escribir_X, coord_escribir_Y + 10);
	cout << "Creditos";

	char t = _getch();

	if (t == ARRIBA) {
		position_flecha -= 5;
	}
	else if (t == ABAJO) {
		position_flecha += 5;
	}

	if (position_flecha > 10 || position_flecha < 0) {
		position_flecha = 0;
	}
	gotoxi(coord_escribir_X - 6, coord_escribir_Y + position_flecha);
	cout << "-->";
	cout << "\033[0m";
}

/*
Colores para mapa01
los colores se dibujan en funcion de un valor entero en el arreglo.
(color del borde) 0: marron oscuro -> #4e342e -> Lo mas parecido en ANSI \033[48;5;52m \033[0m
(colore del sesped) 1: verde brillante -> #21bf07 -> lo m�s parecido en ANSI \033[48;5;34m \033[0m
(color del camino) 2: arena claro -> #d2b48c -> lo m�s parecido en ANSI \033[48;5;180m \033[0m
*/

void Dibujar_Mapa01(int* matriz, int filas, int columnas) {// argumentos, un arreglo por referencia, numero filas, numero de colunas, obsional coords inciales
	for (int i = 0; i < filas; i++) {
		for (int j = 0; j < columnas; j++) {// barremos el arreglo en forma de una matriz
			gotoxi(j, i);//Establecemos sus cordenadas segun su pocision 

			switch (matriz[(i * columnas) + j]) {
			case 0: cout << "\033[48;5;52m \033[0m"; break;
			case 1: cout << "\033[48;5;34m \033[0m"; break;
			case 2: cout << "\033[48;5;180m \033[0m"; break;
			}
		}

	}
}
void Dibujar_mapa02(int* matriz, int filas, int columnas) {
	Console::CursorVisible = false;
	for (int i = 0; i < filas; i++) {
		for (int j = 0; j < columnas; j++) {// barremos el arreglo en forma de una matriz
			gotoxi(j, i);//Establecemos sus cordenadas segun su pocision 

			switch (matriz[i * columnas + j]) {
			case 1: cout << "\033[48;5;52m \033[0m"; break;
			case 2: cout << "\033[48;5;22m \033[0m"; break;
			case 3: cout << "\033[48;5;196m \033[0m"; break;
			case 4: cout << "\033[48;5;226m \033[0m"; break;
			case 5: cout << "\033[48;5;94m \033[0m"; break;
			case 6: cout << "\033[48;5;179m \033[0m"; break;
			}
		}
		_sleep(100);
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
			gotoxi(j + jugador.cordenadas.X, i + jugador.cordenadas.Y);//Establecemos sus cordenadas segun su pocision 

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
			gotoxi(j + coord_x_tronco, i + coord_y_tronco);
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
(segunda tonalidad de la ventana de la maquina) 10: verde azulado gris�sceo suave -> #9abeb9 -> en ANSI \033[48;5;152m \033[0m
(luces de la maquina) 11: rojo puro -> #ff0000 -> en ANSI \033[48;5;196m \033[0m
(luces de la maquina) 12: verde lima -> #40ff00 -> en ANSI \033[48;5;118m \033[0m

*/
void Dibujar_maquina(int* matriz, int filas, int columnas) {
	for (int i = 0; i < filas; i++) {
		for (int j = 0; j < columnas; j++) {
			gotoxi(j + coord_x_maquina, i + corrd_y_maquina);
			switch (matriz[i * columnas + j]) {
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
			gotoxi(j + coord_x_arbol, i + coord_y_arbol);
			switch (matriz[i * columnas + j]) {
			case -1:break;
			case 7: std::cout << "\033[48;5;94m \033[0m"; break; // Marr�n (tronco)
			case 13: cout << "\033[48;5;58m \033[0m"; break; // Verde oliva oscuro(hojas)
			}
		}
	}
}
// Colores para dibujar castor
// espacios en blanco = -1
// #000000 -> bordes en negro del castor = 6
// #c7961c -> color del pelaje del castor = 13
// #c7961c -> color de las ojeras del castor = 14
// #714646 -> color de la nariz del castor = 15
// #714646 -> color marron del castor = 0
// #ffffff -> color de dientes del castor (blanco) = 4

void DibujarCastor(int* matriz, int filas, int columnas, int coord_x_castor, int coord_y_castor) {
	Console::CursorVisible = false;
	for (int i = 0; i < filas; i++) {
		for (int j = 0; j < columnas; j++) {
			gotoxi(j + coord_x_castor, i + coord_y_castor);
			switch (matriz[i * columnas + j]) {
			case -1: break;
			case 0: cout << "\033[48;5;52m \033[0m"; break;
			case 4: cout << "\033[48;5;231m \033[0m"; break;
			case 6: cout << "\033[48;5;16m \033[0m"; break;
			case 13: cout << "\033[48;5;136m \033[0m"; break;
			case 14: cout << "\033[48;5;136m \033[0m"; break;
			case 15: cout << "\033[48;5;95m \033[0m"; break;
			}
		}
	}
}

void dibujarperdiste(int* matriz, int filas, int columnas) {
	Console::CursorVisible = false;
	for (int i = 0; i < filas; i++) {
		for (int j = 0; j < columnas; j++) {
			gotoxi(j, i);
			switch (matriz[i * columnas + j]) {
			case 0: cout << "\033[48;5;88m \033[0m"; break;   // borde rojo oscuro
			case 1: cout << "\033[48;5;196m \033[0m"; break;  // fondo rojo brillante
			}
		}
	}
}

// mostrar el mensaje game over
void mostrarperdiste() {
	gotoxi(30, 2);
	cout << "UPS! LO SENTIMOS";
	gotoxi(30, 4);
	cout << "HAS PERDIDO";
	gotoxi(30, 6);
	cout << "INTENTALO DENUEVO";
}

// dibujar ventana de ganaste
void dibujarganaste(int* matriz, int filas, int columnas) {
	Console::CursorVisible = false;
	for (int i = 0; i < filas; i++) {
		for (int j = 0; j < columnas; j++) {
			gotoxi(j, i);
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
	cout << "\033[48;5;34m\033[30m";
	gotoxi(30, 2);
	cout << "INSTRUCCIONES";
	gotoxi(2, 4);
	cout << "1. Los controles para moverse son: W A S D";
	gotoxi(2, 6);
	cout << "2. El jugador comenzara con 3 vidas.";
	gotoxi(2, 8);
	cout << "3. Los poderes disponibles son: Destruir troncos, Revertir trayectoria.";
	gotoxi(2, 10);
	cout << "4. Por cada 3 troncos destruidos hay una posibilidad que aparesca un castor";
	gotoxi(5, 11);
	cout << "y te entrege una vida extra.";
	gotoxi(2, 13);
	cout << "5. El jugador tiene que esquivar los troncos, y por cada uno que le choque";
	gotoxi(5, 14);
	cout << "perdera una vida. ";
	gotoxi(2, 16);
	cout << "6. En el primeri nivel el jugador tendra que esquivar troncos, y por cada 5 ";
	gotoxi(5, 17);
	cout << "troncos que esquive podra lanzar un poder para destruir los troncos.";
	gotoxi(2, 19);
	cout << "7. Cuando se destruye un tronco se planta un arbol automaticamente.";
	gotoxi(2, 21);
	cout << "8. Los niveles se pasan plantando 5 arboles.";
	gotoxi(2, 23);
	cout << "9. En el segundo nivel el jugador tendra otro poder que le permitira revertir";
	gotoxi(5, 24);
	cout << "la direccion de los troncos para poder destruir la maquina enemiga. ";
	gotoxi(2, 26);
	cout << "10. La maquina enemiga tiene 5 vidas por cada tronco que le choca pierde una.";
	gotoxi(2, 28);
	cout << "11. En el segundo nivel por cada 5 troncos que esquive el jugador este";
	gotoxi(6, 29);
	cout << "obtendra un poder el cual revierte la direccion de los troncos";
	cout << "\033[0m";
}

// dibujar instrucciones
void dibujarfondoinstrucciones() {
	Console::SetWindowSize(80, 50);
	Console::SetBufferSize(80, 50);
	const int FILAS = 50;
	const int COLUMNAS = 80;
	int matrizfondo[FILAS * COLUMNAS];
	for (int i = 0; i < FILAS; i++) {
		for (int j = 0; j < COLUMNAS; j++) {
			if (i == 0 || i == 49 || j == 0 || j == 79)
			{
				matrizfondo[i * COLUMNAS + j] = 0;
			} //borde
			else
			{
				matrizfondo[i * COLUMNAS + j] = 1;
			} //fondo
		}
	}
	Console::CursorVisible = false;
	for (int i = 0; i < FILAS; i++) {
		for (int j = 0; j < COLUMNAS; j++) {
			Console::SetCursorPosition(j, i);
			switch (matrizfondo[i * COLUMNAS + j]) {
			case 0: cout << "\033[48;5;52m \033[0m"; break;
			case 1: cout << "\033[48;5;34m \033[0m"; break;
			}
		}
	}
}
void creditos() {
	cout << "\033[48;5;180m \033[30m";
	gotoxi(30, 2);
	cout << "CREDITOS";
	gotoxi(2, 4);
	cout << "AUTORES/PROGRAMADORES/DISE�ADORES";
	gotoxi(2, 6);
	cout << "- Jeremi Porras";
	gotoxi(2, 8);
	cout << "- Alessio Ccasani";
	gotoxi(2, 10);
	cout << "- Emerson Nolasco";
	gotoxi(2, 13);
	cout << "UNIDOS POR EL CAMBIO";
	gotoxi(2, 16);
	cout << "La tala de �rboles destruye hogares naturales,";
	gotoxi(5, 17);
	cout << "altera el clima y pone en riesgo nuestro futuro.";
	cout << "\033[0m";
}

void dibujarfondocreditos() {
	Console::SetWindowSize(80, 50);
	Console::SetBufferSize(80, 50);
	const int FILAS = 50;
	const int COLUMNAS = 80;
	int matrizfondo[FILAS * COLUMNAS];
	for (int i = 0; i < FILAS; i++) {
		for (int j = 0; j < COLUMNAS; j++) {
			if (i == 0 || i == 49 || j == 0 || j == 79)
			{
				matrizfondo[i * COLUMNAS + j] = 0;
			} //borde
			else
			{
				matrizfondo[i * COLUMNAS + j] = 1;
			} //fondo
		}
	}
	Console::CursorVisible = false;
	for (int i = 0; i < FILAS; i++) {
		for (int j = 0; j < COLUMNAS; j++) {
			Console::SetCursorPosition(j, i);
			switch (matrizfondo[i * COLUMNAS + j]) {
			case 0: cout << "\033[48;5;34m \033[0m"; break;
			case 1: cout << "\033[48;5;180m \033[0m"; break;
			}
		}
	}
}
// Movimientos 
void Limpiar_objeto(int* mapa, int filas, int columnas, int x, int y, int filas_jugador, int columnas_jugador) {
	for (int i = 0; i < filas_jugador; i++) {
		for (int j = 0; j < columnas_jugador; j++) {
			gotoxi(x + j, y + i);
			int valor_fondo = mapa[(y + i) * columnas + (x + j)];
			if (nivel_juego == 1) {
				switch (valor_fondo) {
				case 0: cout << "\033[48;5;52m \033[0m"; break;
				case 1: cout << "\033[48;5;34m \033[0m"; break;
				case 2: cout << "\033[48;5;180m \033[0m"; break;
				}

			} else if(nivel_juego == 2) {
				switch (valor_fondo) {
				case 1: cout << "\033[48;5;52m \033[0m"; break;
				case 2: cout << "\033[48;5;22m \033[0m"; break;
				case 3: cout << "\033[48;5;196m \033[0m"; break;
				case 4: cout << "\033[48;5;226m \033[0m"; break;
				case 5: cout << "\033[48;5;94m \033[0m"; break;
				case 6: cout << "\033[48;5;179m \033[0m"; break;
				}
			}
			else {
				cout << " "; // si no es ninguno de los dos niveles, limpiamos con un espacio en blanco
			}
		}
	}
}


bool Leer_movimiento(int* mapa) {
	if (_kbhit()) {


		char t = _getch();

		//RestaurarFondoDebajoJugador(filas_jugador, columnas_jugador);
		Limpiar_objeto(mapa, filas_mapa01, columnas_mapa01, jugador.cordenadas.X, jugador.cordenadas.Y, filas_jugador, columnas_jugador);

		switch (t) {
		case ARRIBA: (jugador.cordenadas.Y > 0) ?
			jugador.cordenadas.Y-- :
			jugador.cordenadas.Y++; break;
		case ABAJO: (jugador.cordenadas.Y + filas_jugador < filas_mapa01 - 2) ? jugador.cordenadas.Y++ : jugador.cordenadas.Y--; break;
		case DERECHA: (jugador.cordenadas.X + columnas_jugador < columnas_mapa01) ? jugador.cordenadas.X++ : jugador.cordenadas.X--; break;
		case IZQUIERDA: (jugador.cordenadas.X > 0) ? jugador.cordenadas.X-- : jugador.cordenadas.X++; break;
		default: return false;
		}
		jugador.Hitbox.X = jugador.cordenadas.X + 1; // actualizamos la hitbox del jugador
		jugador.Hitbox.Y = jugador.cordenadas.Y + 16; // actualizamos la hitbox del jugador

		return true;

	}
	return false;
}


//void cambiarPoder(string poder, bool activar) {
//	int total = sizeof(arr_poderes) / sizeof(arr_poderes[0]);
//	for (int i = 0; i < total; i++) {
//		if (arr_poderes[i].nombre == poder) {
//			arr_poderes[i].avilitado = activar;
//		}
//	}
//}

bool Hay_colision(int obj01_x, int obj01_y, int obj01_ancho, int obj01_alto, int obj02_x, int obj02_y, int obj02_ancho, int obj02_alto) {
	return (
		obj01_x < obj02_x + obj02_ancho &&
		obj01_x + obj01_ancho > obj02_x &&
		obj01_y < obj02_y + obj02_alto &&
		obj01_y + obj01_alto > obj02_y
		);
}

// cambiar el valor de las vidas y mostrar la actualizacion
void vidas() {

	// Mostrar el n�mero de vidas actuales en pantalla
	gotoxi(3, 49);
	cout << "\033[0;97mVIDAS: " << jugador.vidas << "   \033[0m"; // texto blanco


	//if (jugador.vidas <= 0) {  // si llega a 0 muestra la pantalla de perdiste
	//	dibujarperdiste(matriz, filas, columnas);
	//	mostrarperdiste();
	//}

}
void troncos_esquivados() {
	gotoxi(20, 49);

	cout << "Troncos esquivados: " << jugador.troncos_esquivados << "\033[0m";
}

void inicializarTroncos() {
	srand(time(NULL));

	int tiempo_base = GetTickCount();


	for (int i = 0; i < MAX_TRONCOS; i++) {
		troncos[i].cordenadas.X = 70; // posici�n horizontal aleatoria
		troncos[i].cordenadas.Y = (i * 14) + 6; // posicion vertical diferentes 
		troncos[i].tiempo_de_aparicion = tiempo_base + (rand() % 5000);
		troncos[i].activo = true;
	}
}



void DibujarTroncos(int* mapa, int* matriz_tronco, int i) {

	int tiempo_base = GetTickCount();

	Limpiar_objeto(mapa, filas_mapa01, columnas_mapa01,
		troncos[i].cordenadas.X, troncos[i].cordenadas.Y, dimensiones_tronco_filas, dimensiones_tronco_columnas);

	if (troncos[i].cordenadas.X < 1) {
		troncos[i].cordenadas.X = columnas_mapa01 - dimensiones_tronco_columnas; // vuelve a aparecer a la derecha
		troncos[i].tiempo_de_aparicion = tiempo_base + (rand() % 5000);
		jugador.troncos_esquivados++; // incrementa el contador de troncos esquivados
		return;
	}
	troncos[i].cordenadas.X -= 1;


	DibujarTronco(matriz_tronco, dimensiones_tronco_filas, dimensiones_tronco_columnas, troncos[i].cordenadas.X, troncos[i].cordenadas.Y);
	

}

void Borrar_troncos(int* mapa, int* matriz_tronco,int i) {

	Limpiar_objeto(mapa, filas_mapa01, columnas_mapa01,
		troncos[i].cordenadas.X, troncos[i].cordenadas.Y, dimensiones_tronco_filas, dimensiones_tronco_columnas);

}

void moverTroncos() {

	for (int i = 0; i < MAX_TRONCOS; i++) {
		if (troncos[i].activo) {
			//troncos[i].cordenadas.X -= 3;
			// si el tronco sale de la pantalla, lo reiniciamos
			if (troncos[i].cordenadas.X < 1) {
				troncos[i].tiempo_de_aparicion = (1 + (rand() % 3)) * 1000;
				troncos[i].cordenadas.X = 70;
			}
		}
	}
}

void Colision_HitboxJugador_Tronco(int* mapa) {
	for (int i = 0; i < MAX_TRONCOS; i++) {
		if (troncos[i].activo && Hay_colision(jugador.Hitbox.X, jugador.Hitbox.Y, jugador.Hitbox_ancho, jugador.Hitbox_alto,
			troncos[i].cordenadas.X, troncos[i].cordenadas.Y, dimensiones_tronco_columnas, dimensiones_tronco_filas)) {
			// si hay colision con un tronco
			jugador.vidas -= 1;
			inicializarTroncos(); // reiniciamos los troncos
			jugador.cordenadas.X = coord_x_jugador; // reiniciamos la posicion del jugador
			jugador.cordenadas.Y = coord_y_jugador; // reiniciamos la posicion del jugador
			system("cls"); // limpiamos la pantalla

			if (nivel_juego == 1) {
				// si el jugador pierde una vida en el nivel 1, reiniciamos el mapa
				Dibujar_Mapa01(mapa, filas_mapa01, columnas_mapa01); // dibujamos el mapa
			}
			else if (nivel_juego == 2) {
				// si el jugador pierde una vida en el nivel 2, reiniciamos el mapa
				Dibujar_mapa02(mapa, filas_mapa02, columnas_mapa02); // dibujamos el mapa
			}
			vidas();

			return;
		}
	}
}

void Habilitar_Poderes() {
	// Habilitar el poder de romper troncos si se han esquivado 5 troncos
	if (jugador.troncos_esquivados >= 5 && !jugador.poderes[0].avilitado) {
		jugador.poderes[0].avilitado = true;
		cout << "\033[0;32mPoder romper troncos activados!\033[0m" << endl;
	}
	// Habilitar el poder de revertir la trayectoria si se han esquivado 10 troncos
	if (jugador.troncos_esquivados >= 10 && !jugador.poderes[1].avilitado) {
		jugador.poderes[1].avilitado = true;
		cout << "\033[0;32mPoder de revertir trayectoria habilitado!\033[0m" << endl; // texto verde
	}
}

void Tronco_Destruido(int* arbol, int *mapa, int *matriz_tronco) {
	for (int i = 0; i < MAX_TRONCOS; i++) {


		if (!troncos[i].activo) {
			DibujarArbol(arbol, 15, 10, troncos[i].cordenadas.X, troncos[i].cordenadas.Y);
		}

		if (troncos[i].activo && Hay_colision(jugador.Hitbox.X, jugador.Hitbox.Y, jugador.Hitbox_ancho, jugador.Hitbox_alto,
			troncos[i].cordenadas.X, troncos[i].cordenadas.Y, dimensiones_tronco_columnas, dimensiones_tronco_filas)) {
			// si hay colision con un tronco
			if (jugador.poderes[0].avilitado) { // si el poder de romper tronco esta activado
				troncos[i].activo = false; // desactivamos el tronco
				jugador.troncos_esquivados++; // incrementamos el contador de troncos esquivados
				Borrar_troncos(mapa, matriz_tronco, i); // borramos el tronco de la pantalla
				// dibujamos el arbol en la posicion del tronco destruido
				DibujarArbol(arbol, 15, 10, troncos[i].cordenadas.X, troncos[i].cordenadas.Y);
				jugador.troncos_destruidos++;
			}
		}

	}

}

#endif