#include <iostream>
#include "funcionesvideojuego_v1.h"
#include "assets.h"

// TODO: Iniciar la programcion incial del videojuego

void Nivel01() {
	Dibujar_Mapa01(mapa01, filas_mapa01, columnas_mapa01);
	Dibujar_jugador(prota, 19, 10);
	inicializarTroncos();

	DibujarCastor(castor_data, 10, 10, 60, 20);
	unsigned long long tiempo_anterior = GetTickCount64();
	do {

		if (_kbhit()) {//detecta si se presiona alguna tecla
			Leer_movimiento(mapa01);
			Dibujar_jugador(prota, filas_jugador, columnas_jugador);
		}

		DibujarCastor(castor_data, 10, 10, 60, 20);



		unsigned long long tiempo_actual = GetTickCount64();

		if (tiempo_actual - tiempo_anterior >= 100) {  // actualiza cada 100ms
			for (int i = 0; i < MAX_TRONCOS; i++) {
				if ( tiempo_actual <= troncos[i].tiempo_de_aparicion) continue;

				DibujarTroncos(mapa01, tronco_data, i);
				//moverTroncos();
			}
			
			
			tiempo_anterior = tiempo_actual;
		}


	} while (true);

}

int main() {

	configurarConsola();


	Dibujar_Presentacion(presentacion_matris, 50, 80);//Llamar a la funcion dibujar presentacion
	bool opcion_elegida = false;
	int num_opcion;
inicio:
	do
	{
		if (_kbhit()) {
			Dibujar_Presentacion(presentacion_matris, 50, 80);

			char o = _getch();
			if (o == 13) {
				opcion_elegida = true;
				num_opcion = position_flecha / 5;
			}
		}
	} while (!opcion_elegida);

	if (num_opcion == 0) {
		system("cls");//Limpiamos pantalla

		Nivel01();

	}

	if (num_opcion == 1) {
		system("cls");//Limpiamos pantalla
		dibujarfondoinstrucciones();
		mostrarinstrucciones();

		do
		{
			if (_kbhit()) {
				opcion_elegida = false;
				num_opcion = -1;
				system("cls");
				goto inicio;
			}
		} while (true);

	}

	if (num_opcion == 2) {
		system("cls");//Limpiamos pantalla
		creditos();

		do {
			if (_kbhit()) {
				opcion_elegida = false;
				num_opcion = -1;
				system("cls");
				goto inicio;
			}

		} while (true);
	}

	/*while (true)
	{

	Console::SetCursorPosition(coord_x_jugador, coord_y_jugador);
	std::cout << "@";
	bool se_movio = Leer_movimiento();
	if (se_movio) {
	std::cout << " ";
	Dibujar_Mapa01(mapa01, 5, 8);
	}*/

	system("pause");
	return 0;
}
