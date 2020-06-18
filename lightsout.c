#include "lightsout.h"

#include <time.h>
#include <stdlib.h>
#include <stdio.h>

// Initialisation de toutes les cases de la matrice
void Randomize(int* b, int nb_cases) {
	for (int i = 0; i < nb_cases; i++) {
		srand(time(NULL));
		b[i] = rand() % 2;
	}
}

// Correspondance cases matrice avec valeur random entre 0 et 1
void RandomizeMatrix(int** matrice, int weight, int nb_cases) {
	srand(time(NULL));
	for (int i = 0; i < weight; i++) {
		for (int j = 0; j < weight; j++) {
			matrice[i][j] = rand() % 2;
		}
	}
	
	/*
	for (int i = 0; i < nb_cases; i++) {
		printf("i: %d\n", i);
		matrice[i][i] = rand() % 2;
		if (i % weight != 0)
			matrice[i][i - 1] = rand() % 2;
		if((i + 1) % weight != 0)
			matrice[i][i + 1] = rand() % 2;
		if( i >= weight)
			matrice[i][i - weight] = rand() % 2;
		if(i < nb_cases - weight)
			matrice[i][i + weight] = rand() % 2;
	}
	*/
}

//=====================================================================================================================//
//                                             Fonctions inutilisées                                                   //
//                            Ces fonctions seront utilisées par l'auto-resolve (un jour)                              //
//=====================================================================================================================//

/*fx renvoie 1 si echange de ligne ok, sinon 0 (flag), si flag=0, solution unique
Premiere �tape du pivot de gauss : mettre un 1 de la premi�re colonne en position Matrice[0][0]
*/
int SwapLine(int** matrice, int* b, int nb_cases, int line) {
	int flag, lineswap, i, auxb; //variable de fonctions
	flag = 0; 
	int aux[25]; //cr�ation d'un tableau auxiliaire
	for (lineswap = line + 1; lineswap < nb_cases; lineswap++) { //on regarde la premiere case de la colonne, si = 0, incrementation N (donc position Matrice[0][1]), sinon on fait le swap
		if (matrice[lineswap][line] != 0) { 
			for (i = line; i < nb_cases; i++)
				aux[i] = matrice[line][i];
			for (i = line; i < nb_cases; i++)
				matrice[line][i] = matrice[lineswap][i];
			for (i = line; i < nb_cases; i++)
				matrice[lineswap][i] = aux[i];
			auxb = b[line];
			b[line] = b[lineswap];
			b[lineswap] = auxb;
			flag = 1;
			break;
		}
	}
	return flag;
}

/*
 Modification des lignes suivantes, on cherche a savoir s'il est possible de diagonnaliser la matrice (si la fonction va jusqu'au bout), et donc de une solution
*/
void NextLine(int** matrice, int* b, int nb_cases, int line) {
	int linefx, columnfx;
	for (linefx = line + 1; linefx < nb_cases; linefx++) {
		if (matrice[linefx][line] != 0) {
			for (columnfx = line; columnfx < nb_cases; columnfx++)
			matrice[linefx][columnfx] = (matrice[linefx][columnfx] + matrice[line][columnfx]) % 2;
			b[linefx] = (b[linefx] + b[line]) % 2;
		}
	}
}

/*Diagonalisation de la matrice
On cherche a n'avoir des 1 que sur la diagonale (Matrice[i][i]=1)*/
void Unique(int** matrice, int* b, int nb_cases) {
	int line, lines, column, i, auxb;
	int aux[25];
	for (lines = nb_cases - 1; lines > 0; lines--) {
		if (matrice[lines][lines] == 0) {
			for (line = lines - 1; line >= 0; line--) {
				if (matrice[line][lines] != 0) {
					for (i = lines; i >= 0; i--)
						aux[i] = matrice[lines][i];
					for (i = lines; i >= 0; i--)
						matrice[lines][i] = matrice[line][i];
					for (i = lines; i >= 0; i--)
						matrice[line][i] = aux[i];
					auxb = b[lines];
					b[lines] = b[line];
					b[line] = auxb;
					break;
				}
			}
			/*solution*/
			for (line = lines - 1; line >= 0; line--) {
				if (matrice[line][lines] != 0) {
					for (column = lines; column >= 0; line--)
					matrice[line][column] = (matrice[line][column] + matrice[lines][column]) % 2;
					b[line] = (b[line] + b[lines]) % 2;
				}
			}
		}
	}
}

/*en cas de flag=0, pas de solution unique mais 2^(N-Ligne) (binaire de longueur N-Ligne)*/
void Multiple(int** matrice, int** msave, int* b, int* bsave, int nb_cases, int LL, int nombre) {
	int sln, i, q, j, line, column, Line, cumul, n, auxb;
	int x[25], aux[25];
	sln = nombre * nombre;
	for (n = 0; n < sln; n++) {
		//Sauvegarde de la matrice g�n�r�e et du tableau initial car il faut les r�g�n�rer a chaque calcul de solution
		for(i = 0; i < nombre; i++)
			for(j = 0; j < nb_cases; j++){
				matrice[i][j] = msave[i][j];
			}
		for (i = 0; i < nb_cases; i++)
			b[i] = bsave[i];

		q = n;
		// determination des valeurs des inconnues
		for (i = 0; i < nombre; i++) {
			x[nb_cases - 1 - i] = q % 2;
			q = q / 2;
		}

		//calcul des solutions
		for (line = 0; line < LL; line++) {
			cumul = 0;
			for (j = 0; j < nombre; j++)
				cumul += x[nb_cases - 1 - j] * matrice[line][nb_cases - 1 - j];
			b[line] = (b[line] + cumul) % 2;
		}
		for (j = 0; j < nombre; j++) {
			for (Line = LL - 1; Line > 0; Line--) {
				if (matrice[Line][Line] == 0)
					for (line = Line - 1; line >= 0; line--) {
						if (matrice[line][Line] != 0) {
							for (i = Line; i >= 0; i--)
								aux[i] = matrice[Line][i];
							for (i = Line; i >= 0; i--)
								matrice[Line][i] = matrice[line][i];
							for (i = Line; i >= 0; i--)
								matrice[line][i] = aux[i];
							auxb = b[Line];
							b[Line] = b[line];
							b[line] = auxb;
							break;
						}
					}
				//Diagonalisation
				for (line = Line - 1; line >= 0; line--) {
					if (matrice[line][Line] != 0) {
						for (column = Line; column >= 0; column--)
						matrice[line][column] = (matrice[line][column] + matrice[Line][column]) % 2;
						b[line] = (b[line] + b[Line]) % 2;
					}
				}
			}

			for (i = 0; i < nb_cases - nombre; i++) 
				printf(" x%d=%d", i, b[i]);
			for (j = 0; j <	nombre; j++)
				printf(" x%d=%d", nb_cases - nombre + j, x[nb_cases - nombre + j]);
		}
	}
}