#include <iostream>
#include "funcionesvideojuego_v3.h"
#include "assets.h"

// TODO: Iniciar la programcion incial del videojuego

void Nivel01() {
	bool Nivel_finalizado = false; // determinamos si se finaliza el nivel
	bool se_mostro_poder = false; // si se muestra mostró el poder, no se volvera a dibujar

	Dibujar_Mapa01(mapa01, filas_mapa01, columnas_mapa01); // dibujamos mapa01 por primera vez
	Dibujar_jugador(prota, 19, 10);// dibujamos al jugador por primera vez
	inicializarTroncos();
	vidas();// mostramos las vidas iniciales del jugador (3 vidas)
	DibujarCastor(castor_data, 10, 10, 60, 20); // dibujamos el castor por primera vez.
	unsigned long long tiempo_anterior = GetTickCount64(); // obtenemos el tiempo al inicializar el nivel.


	do {

		if (_kbhit()) {//detecta si se presiona alguna tecla
			Leer_movimiento(mapa01); // leemos la direccion del jugador y limpiamos su posicion anterior
			Dibujar_jugador(prota, filas_jugador, columnas_jugador); // dibujamos al jugador en su nueva posición
		}




		unsigned long long tiempo_actual = GetTickCount64(); // obtenemos el tiempo 

		if (tiempo_actual - tiempo_anterior >= 100) {  // actualiza cada 100ms
			for (int i = 0; i < MAX_TRONCOS; i++) { // se barren los troncos para el nivel, se definio MAX_TRONCOS = 3
				if (!(troncos[i].activo)) continue; // Si el tronco no está activo, no lo dibujamos
				if (tiempo_actual <= troncos[i].tiempo_de_aparicion) continue; // Si no ha pasado el tiempo de aparicion del tronco continua

				DibujarTroncos(mapa01, tronco_data, i); // dibujamos el tronco

			}


			tiempo_anterior = tiempo_actual;// reiniciamos el tiempo transcurrido 
		}
		if (jugador.troncos_esquivados >= 10) {
			jugador.poderes[0].avilitado = true;
			Tronco_Destruido(arbol_data, mapa01, tronco_data);
			if (!se_mostro_poder) {

				MostrarPoder_1();
				se_mostro_poder = true;
			}
		}
		else {
			Colision_HitboxJugador_Tronco(mapa01); // si no se esquivan los 10 troncos, los troncos haran daño al jugador
		}


		troncos_esquivados(); // mostramos los troncos esquivados

		if (jugador.vidas <= 0) {
			system("cls");
			dibujargameover(gameover, 50, 80);
			jugador.perdio = true;
			break;
		}

		if (jugador.troncos_destruidos == 3) {
			DibujarCastor(castor_data, 10, 10, 60, 20);
			_sleep(2000);
			Nivel_finalizado = true;
			system("cls");
			nivel_juego++; // Avanzamos al nivel 02

		}



	} while (!Nivel_finalizado);

	jugador.troncos_esquivados = 0; // Reiniciar el contador de troncos esquiados al finalizar el nivel
	jugador.troncos_destruidos = 0; // Reiniciar el contador de troncos destruidos al finalizar el nivel
	jugador.vidas = 3; // Reiniciar las vidas al finalizar el nivel
	jugador.poderes[0].avilitado = false; // Reiniciar el poder al finalizar el nivel
	_sleep(500);
}

void Nivel02() {

	bool Nivel_finalizado = false; // determinamos si se finaliza el nivel
	bool se_mostro_poder = false; // Variable para controlar si se ha mostrado el poder
	jugador.gano = false; // Reiniciar el estado de jugador al finalizar el nivel
	jugador.perdio = false; // Reiniciar el estado de jugador al finalizar el nivel
	
	Dibujar_mapa02(mapa02, filas_mapa02, columnas_mapa02);
	Dibujar_jugador(prota, 19, 10);
	inicializarTroncos();
	Dibujar_maquina(maquina_data, 15, 15);
	vidas();

	unsigned long long tiempo_anterior = GetTickCount64();//tiempo de troncos
	unsigned long long tiempo_castor_anterior = GetTickCount64();//tiempo de castor 
	do {
		if (_kbhit()) {//detecta si se presiona alguna tecla
			Leer_movimiento(mapa02);
			Dibujar_jugador(prota, filas_jugador, columnas_jugador);
		}

		unsigned long long tiempo_actual = GetTickCount64();
		if (tiempo_actual - tiempo_anterior >= 100) {  // actualiza cada 100ms

			if (tiempo_actual - tiempo_castor_anterior >= 20000) {//20 seg	
				Aparecer_Castor(castor_data); //FUNCION DE CASTOR
				tiempo_castor_anterior = tiempo_actual;//se reinicia el tiempo de aparacion del castor
			}

			if (!(jugador.cordenadas.Y + 4 == maquina.cordenadas.Y)) {//para alinear al jugador con la maquina
				// maquina se mueve al jugador
				Limpiar_objeto(mapa02, filas_mapa02, columnas_mapa02, maquina.cordenadas.X, maquina.cordenadas.Y, 15, 15);
				MoverMaquinaHaciaJugador();
				Dibujar_maquina(maquina_data, 15, 15);

			}

			if (Rango_de_Altura(jugador.Hitbox.Y, 3, maquina.cordenadas.Y, filas_maquina)) { // si la maquina esta en el rango de la hitbox del jugador
				for (int i = 0; i < MAX_TRONCOS; i++) { // barremos los tres troncos
					if (Rango_de_Altura(maquina.cordenadas.Y + 7, filas_maquina - 7, troncos[i].cordenadas.Y, dimensiones_tronco_filas)) { // si la maquina se encuentra en el rango del camino, activara el tronco 
						troncos[i].activo = true; // Activar tronco cuando la maquina esta en rango de altura
					}
				}
			}

			for (int i = 0; i < MAX_TRONCOS; i++) {
				if (!(troncos[i].activo)) continue; // Si el tronco no está activo, no lo dibujamos

				Tronco_devuelto(mapa02, tronco_data);
				
				if (!troncos[i].varia_derecha) {
					DibujarTroncos(mapa02, tronco_data, i);
				}
				

				//moverTroncos();
				if (troncos[i].varia_derecha) {
					Limpiar_objeto(mapa02, filas_mapa01, columnas_mapa01,
					troncos[i].cordenadas.X, troncos[i].cordenadas.Y, dimensiones_tronco_filas, dimensiones_tronco_columnas);
					troncos[i].cordenadas.X += 2; // Mover tronco hacia la derecha
				
					DibujarTroncosDerecha(mapa02, tronco_data, i);

					if (Hay_colision(maquina.Hitbox.X, maquina.Hitbox.Y, maquina.Hitbox_ancho, maquina.Hitbox_alto, troncos[i].cordenadas.X,
						troncos[i].cordenadas.Y, dimensiones_tronco_filas, dimensiones_tronco_columnas)) {
						maquina.vidas--; // Restar vida a la maquina si colisiona con un tronco
						troncos[i].activo = false;// Desactivar tronco al colisionar con la maquina
						troncos[i].varia_derecha = false; // Reiniciar la posicion del tronco
						Borrar_troncos(mapa02, tronco_data, i); // Borrar tronco si colisiona con la maquina
					}

				}
			}

			tiempo_anterior = tiempo_actual;
		}



		if (jugador.troncos_esquivados >= 15) {
			jugador.poderes[1].avilitado = true;
			if (!se_mostro_poder) {
				
				MostrarPoder_1();
				se_mostro_poder = true; 
			}
		}
		else {
			Colision_HitboxJugador_Tronco(mapa02);
		}
		troncos_esquivados();

		if (maquina.vidas <= 0 ) {
			system("cls");
			dibujargameover(ganaste, 50, 80);
			jugador.gano = true; // Cambiar el estado de jugador a ganado
			_sleep(3000);
			system("cls");//Limpiamos pantalla
			dibujarfondocreditos();
			creditos();
			Nivel_finalizado = true;
			break;
		}

		if (jugador.vidas <= 0) {
			system("cls");
			dibujar_gameover(gameover, 50, 80);
			jugador.perdio = true;
			Nivel_finalizado = true;

			break;

		}

	} while (!Nivel_finalizado);

	jugador.troncos_esquivados = 0; // Reiniciar el contador de troncos esquiados al finalizar el nivel
	jugador.troncos_destruidos = 0; // Reiniciar el contador de troncos destruidos al finalizar el nivel
	
	jugador.vidas = 3; // Reiniciar las vidas al finalizar el nivel
	jugador.poderes[0].avilitado = false; // Reiniciar el poder al finalizar el nivel
	jugador.poderes[1].avilitado = false; // Reiniciar el poder al finalizar el nivel
	jugador.cordenadas.X = columnas_jugador; // Reiniciar la posicion del jugador al finalizar el nivel
	jugador.cordenadas.Y = filas_jugador; // Reiniciar la posicion del jugador al finalizar el nivel
	jugador.Hitbox.X = columnas_jugador; // Reiniciar la Hitbox del jugador al finalizar el nivel
	jugador.Hitbox.Y = filas_jugador; // Reiniciar la Hitbox del jugador al finalizar el nivel
	nivel_juego = 1; // el nivel del juego vuelve a 1, para jugar desde el inicio

	maquina.vidas = 5; // Reiniciar las vidas de la maquina al finalizar el nivel
	_sleep(500);
}


void jugar() {
	// Se jugaran los niveles consecutivamente, si se pierde en cualquier nivel, comensara desde el nivel 01
	switch (nivel_juego) {
	case 1: Nivel01(); break;
	case 2: Nivel02(); break;
	}
}

int main() {

	configurarConsola(); // configuracion de la consola


	Dibujar_Presentacion(presentacion_matris, 50, 80);//Llamar a la funcion dibujar presentacion
	bool opcion_elegida = false; // se inicializa la variable de opcion, como falsa
	int num_opcion; // se inicializa el numero de opcion

	inicio:

	do {
		if (_kbhit()) { // si detecta una tecla
			Dibujar_Presentacion(presentacion_matris, 50, 80); // dibujamos la portada del juego

			char o = _getch();// optenemo el valor que tecleo el jugador
			if (o == ENTER) { // si la tecla es enter
				opcion_elegida = true;
				num_opcion = position_flecha / 5; //tomamos la posicion de la flecha entre de 0 a 2 
			}
		}
	} while (!opcion_elegida);//si la opcion elegida es falso , sigue con el siguiente

	if (num_opcion == 0) {
		do {
			system("cls");//Limpiamos pantalla
			jugar();//se activa la opcion jugar, para ejecutar el juego
		} while (!(jugador.perdio || jugador.gano));//si esto no se cumple, el juego continua
		opcion_elegida = false;
		num_opcion = -1;
		jugador.perdio = false; // Reiniciar el estado de jugador al finalizar el juego
		jugador.gano = false; // Reiniciar el estado de jugador al finalizar el juego
		goto inicio; // Volver al inicio del juego si se pierde o se gana

	}

	if (num_opcion == 1) {//si el numero es 1, se muestran las instrucciones
		system("cls");//Limpiamos pantalla
		dibujarfondoinstrucciones();
		mostrarinstrucciones();

		do
		{
			if (_kbhit()) { //si se detecta un movimiento, volvemos a la pantalla anterior y reiniciamos los valores anteriores
				opcion_elegida = false;
				num_opcion = -1;//coloca una opcion que no existe, para poder 
				system("cls");
				goto inicio;
			}
		} while (true);

	}

	if (num_opcion == 2) {//si el numero es 2, se muestran los creditos
		system("cls");//Limpiamos pantalla
		dibujarfondocreditos();
		creditos();

		do {
			if (_kbhit()) {//si se detecta un movimiento, volvemos a la pantalla anterior y reiniciamos los valores anteriores
				opcion_elegida = false;
				num_opcion = -1;//coloca una opcion que no existe, para poder 
				system("cls");
				goto inicio;
			}

		} while (true);
	}

	return 0;
}