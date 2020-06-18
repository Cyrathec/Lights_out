#include "lightsout.h"
#include "SDL_local.h"

#include <stdlib.h>

int main(int argc, char* argv[]) {
	int** matrice, * b;
	int weight = 5;
	int nb_cases = weight * weight;

	matrice = malloc(sizeof(int*) * weight);
	b = malloc(sizeof(int) * nb_cases);

	for (int i = 0; i < weight; i++){
		matrice[i] = malloc(sizeof(int) * weight);
	}
	
	Randomize(b, nb_cases);
	RandomizeMatrix(matrice, weight, nb_cases);

    Affichage_jeu(matrice, weight);

    system("PAUSE");

	return 0;
}