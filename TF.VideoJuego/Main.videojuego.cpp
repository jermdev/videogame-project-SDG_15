
#include <iostream>
#include "funcionesvideojuego_v1.h"
// TODO: Iniciar la programcion incial del videojuego

int main() {
	int mapa01[8] = {//Este es solo un ejemplo, falta implementar el mapa01
		1,0,2,1,
		2,0,1,1,
	};
	Dibujar_Mapa(mapa01, 2, 4);
	system("pause");
	return 0;
}