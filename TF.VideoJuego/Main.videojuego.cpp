#include <iostream>
#include "funcionesvideojuego_v3.h"
#include "assets.h"

// TODO: Iniciar la programcion incial del videojuego

void Nivel01() {
	bool Nivel_finalizado = false;

	Dibujar_Mapa01(mapa01, filas_mapa01, columnas_mapa01);
	Dibujar_jugador(prota, 19, 10);
	inicializarTroncos();
	vidas();

	DibujarCastor(castor_data, 10, 10, 60, 20);
	unsigned long long tiempo_anterior = GetTickCount64();
	do {

		if (_kbhit()) {//detecta si se presiona alguna tecla
			Leer_movimiento(mapa01);
			Dibujar_jugador(prota, filas_jugador, columnas_jugador);
		}

		//DibujarCastor(castor_data, 10, 10, 60, 20);



		unsigned long long tiempo_actual = GetTickCount64();

		if (tiempo_actual - tiempo_anterior >= 100) {  // actualiza cada 100ms
			for (int i = 0; i < MAX_TRONCOS; i++) {
				if (!(troncos[i].activo)) continue; // Si el tronco no está activo, no lo dibujamos
				if (tiempo_actual <= troncos[i].tiempo_de_aparicion) continue;

				DibujarTroncos(mapa01, tronco_data, i);
				//moverTroncos();
			}


			tiempo_anterior = tiempo_actual;
		}



		if (jugador.troncos_esquivados >= 10) {
			jugador.poderes[0].avilitado = true;
			Tronco_Destruido(arbol_data, mapa01, tronco_data);
		}
		else {

			Colision_HitboxJugador_Tronco(mapa01);
		}

		troncos_esquivados();

		if (jugador.vidas <= 0) {
			system("cls");
			mostrarperdiste();
			break;

		}

		if (jugador.troncos_destruidos == 3) {
			DibujarCastor(castor_data, 10, 10, 60, 20);
			_sleep(2000);

			Nivel_finalizado = true;
			system("cls");
			mostrarganaste();
			nivel_juego++;

		}
	} while (!Nivel_finalizado);

	jugador.troncos_esquivados = 0; // Reiniciar el contador de troncos esquiados al finalizar el nivel
	jugador.troncos_destruidos = 0; // Reiniciar el contador de troncos destruidos al finalizar el nivel
	jugador.vidas = 3; // Reiniciar las vidas al finalizar el nivel
	jugador.poderes[0].avilitado = false; // Reiniciar el poder al finalizar el nivel
	_sleep(500);
}

void Nivel02() {
	bool Nivel_finalizado = false;
	Dibujar_mapa02(mapa02, filas_mapa02, columnas_mapa02);
	Dibujar_jugador(prota, 19, 10);
	inicializarTroncos();
	vidas();
	unsigned long long tiempo_anterior = GetTickCount64();
	do {
		if (_kbhit()) {//detecta si se presiona alguna tecla
			Leer_movimiento(mapa02);
			Dibujar_jugador(prota, filas_jugador, columnas_jugador);
		}
		unsigned long long tiempo_actual = GetTickCount64();
		if (tiempo_actual - tiempo_anterior >= 100) {  // actualiza cada 100ms
			for (int i = 0; i < MAX_TRONCOS; i++) {
				if (!(troncos[i].activo)) continue; // Si el tronco no está activo, no lo dibujamos
				if (tiempo_actual <= troncos[i].tiempo_de_aparicion) continue;
				DibujarTroncos(mapa02, tronco_data, i);
				//moverTroncos();
			}
			tiempo_anterior = tiempo_actual;
		}

		if (jugador.troncos_esquivados >= 10) {
			jugador.poderes[0].avilitado = true;
			Tronco_Destruido(arbol_data, mapa02, tronco_data);
		}
		else {
			Colision_HitboxJugador_Tronco(mapa02);
		}
		troncos_esquivados();
		if (jugador.vidas <= 0) {
			system("cls");
			mostrarperdiste();
			break;
		}
		
	} while (!Nivel_finalizado);
}


void jugar() {
	switch (nivel_juego) {
	case 1: Nivel01(); break;
	case 2: Nivel02(); break;
	default: std::cout << "Nivel no implementado." << std::endl; break;
	}
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
			if (o == ENTER) {
				opcion_elegida = true;
				num_opcion = position_flecha / 5;
			}
		}
	} while (!opcion_elegida);

	if (num_opcion == 0) {
		for (int i = nivel_juego; i <= niveles_del_juego; i++) {
		system("cls");//Limpiamos pantalla
		jugar();
		}
		
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
		dibujarfondocreditos();
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


	system("pause");
	return 0;
}