
#include <iostream>
#include "funcionesvideojuego_v1.h"
// TODO: Iniciar la programcion incial del videojuego

int main() {
	int mapa01[] = {//Este es solo un ejemplo, falta implementar el mapa01
		2,2,2,2,2,2,2,2,
		2,2,2,2,2,2,2,2,
		2,2,2,2,2,2,2,2,
		2,2,2,2,2,2,2,2,
		2,2,2,2,2,2,2,2,
	};
	int presentacion[] = {
		1,0,0,0,1,
		1,0,0,0,1,
	};

	int jugador[]{
		-1,-1,-1,-1,4,4,-1,-1,-1,-1,
		-1,-1,-1,4,4,4,4,-1,-1,-1,
		-1,4,4,4,4,4,4,4,4,-1
	};

	//Dibujar_Mapa(mapa01, 5, 8);
	/*while (true)
	{

	Console::SetCursorPosition(coord_x_jugador, coord_y_jugador);
	std::cout << "@";
	bool se_movio = Leer_movimiento();
	if (se_movio) {
	std::cout << " ";
	Dibujar_Mapa(mapa01, 5, 8);
	}*/

	//Dibujar_jugador(jugador, 3, 10);
	dibujarinstrucciones(presentacion, 2, 5);
	mostrarinstrucciones();
	//mostrarinstrucciones();
	
	//Presentacion(presentacion, 2, 5);
	system("pause");
	return 0;
}
