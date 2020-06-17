#include "lightsout.h"

//Variables globales
int N=25; //Nombre de cases
int L = 5; // Nombre de ligne
int b[25], bsave[25]; //Tableau de 25, copie de toutes les valeurs de la matrice
int Matrice[5][5]; //double tableau, 5 ligne, 5 colonnes
int Msave[5][5]; //idem


int main(int argc, char* argv[]) {
	randomize(); 
	RandomizeMatrix();
    Affichage_jeu();
    system("PAUSE");
	return 0;
}

//Initialisation de toutes les cases de la matrice

void randomize() {
	int i;
	for (i = 0; i < N; i++) { 
		srand(time(NULL));
		b[i] = rand() % 2;
	}
}


/*Correspondance cases matrice avec valeur random entre 0 et 1*/

void RandomizeMatrix() {
	int i, line, column;
	srand(time(NULL));
	for (i = 0; i < N; i++) {
		Matrice[i][i] = rand() % 2;
		if (i % L != 0)
			Matrice[i][i - 1] = rand() % 2;
		if((i+1)%L!=0)
			Matrice[i][i + 1] = rand() % 2;
		if(i>=L)
			Matrice[i][i - L] = rand() % 2;
		if(i<N-L)
			Matrice[i][i + L] = rand() % 2;
	}

	/* AFFICHAGE MATRICE
	printf("\n");
	for (line = 0; line < L; line++) {
		printf("\n");
		for (column = 0; column < L; column++)
			printf(" %d", Matrice[line][column]);
		printf(" %d", b[line]);
	}
	getchar();*/
}

/*fx renvoie 1 si echange de ligne ok, sinon 0 (flag), si flag=0, solution unique
Premiere �tape du pivot de gauss : mettre un 1 de la premi�re colonne en position Matrice[0][0]
*/
int SwapLine(int Line) {
	int flag, lineswap, i, auxb; //variable de fonctions
	flag = 0; 
	int aux[25]; //cr�ation d'un tableau auxiliaire
	for (lineswap = Line + 1; lineswap < N; lineswap++) { //on regarde la premiere case de la colonne, si = 0, incrementation N (donc position Matrice[0][1]), sinon on fait le swap
		if (Matrice[lineswap][Line] != 0) { 
			for (i = Line; i < N; i++)
				aux[i] = Matrice[Line][i];
			for (i = Line; i < N; i++)
				Matrice[Line][i] = Matrice[lineswap][i];
			for (i = Line; i < N; i++)
				Matrice[lineswap][i] = aux[i];
			auxb = b[Line];
			b[Line] = b[lineswap];
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
void NextLine(int Line) {
	int linefx, columnfx;
	for (linefx = Line + 1; linefx < N; linefx++) {
		if (Matrice[linefx][Line] != 0) {
			for (columnfx = Line; columnfx < N; columnfx++)
			Matrice[linefx][columnfx] = (Matrice[linefx][columnfx] + Matrice[Line][columnfx]) % 2;
			b[linefx] = (b[linefx] + b[Line]) % 2;
		}
	}
}
/*Diagonalisation de la matrice
On cherche a n'avoir des 1 que sur la diagonale (Matrice[i][i]=1)*/
void Unique(void) {
	int line, Line, column, i, auxb;
	int aux[25];
	for (Line = N - 1; Line > 0; Line--) {
		if (Matrice[Line][Line] == 0) {
			for (line = Line - 1; line >= 0; line--) {
				if (Matrice[line][Line] != 0) {
					for (i = Line; i >= 0; i--)
						aux[i] = Matrice[Line][i];
					for (i = Line; i >= 0; i--)						Matrice[Line][i] = Matrice[line][i];					for (i = Line; i >= 0; i--)						Matrice[line][i] = aux[i];					auxb = b[Line];
					b[Line] = b[line];
					b[line] = auxb;
					break;
				}
			}
			/*solution*/
			for (line = Line - 1; line >= 0; line--) {
				if (Matrice[line][Line] != 0) {
					for (column = Line; column >= 0; line--)
					Matrice[line][column] = (Matrice[line][column] + Matrice[Line][column]) % 2;
					b[line] = (b[line] + b[Line]) % 2;
				}
			}
		}
	}
}

/*en cas de flag=0, pas de solution unique mais 2^(N-Ligne) (binaire de longueur N-Ligne)*/
void Multiple(int LL, int nombre) {
	int sln, i, q, j, line, column, Line, cumul, n, auxb;
	int x[25], aux[25];
	sln = pow(2, nombre);
	for (n = 0; n < sln; n++) {
		//Sauvegarde de la matrice g�n�r�e et du tableau initial car il faut les r�g�n�rer a chaque calcul de solution
		for(i = 0; i < nombre; i++)
			for(j = 0; j < N; j++){
				Matrice[i][j] = Msave[i][j];
			}
		for (i = 0; i < N; i++)
			b[i] = bsave[i];

		q = n;
		// determination des valeurs des inconnues
		for (i = 0; i < nombre; i++) {
			x[N - 1 - i] = q % 2;
			q = q / 2;
		}

		//calcul des solutions
		for (line = 0; line < LL; line++) {			cumul = 0;			for (j = 0; j < nombre; j++)				cumul += x[N - 1 - j] * Matrice[line][N - 1 - j];			b[line] = (b[line] + cumul) % 2;		}		for (j = 0; j < nombre; j++) {
			for (Line = LL - 1; Line > 0; Line--) {
				if (Matrice[Line][Line] == 0)					for (line = Line - 1; line >= 0; line--) {
						if (Matrice[line][Line] != 0) {
							for (i = Line; i >= 0; i--)
								aux[i] = Matrice[Line][i];
							for (i = Line; i >= 0; i--)
								Matrice[Line][i] = Matrice[line][i];
							for (i = Line; i >= 0; i--)
								Matrice[line][i] = aux[i];
							auxb = b[Line];
							b[Line] = b[line];
							b[line] = auxb;
							break;
						}
					}
				//Diagonalisation
				for (line = Line - 1; line >= 0; line--) {
					if (Matrice[line][Line] != 0) {
						for (column = Line; column >= 0; column--)
						Matrice[line][column] = (Matrice[line][column] + Matrice[Line][column]) % 2;						b[line] = (b[line] + b[Line]) % 2;
					}
				}
			}

			for (i = 0; i < N - nombre; i++) 				printf(" x%d=%d", i, b[i]);			for (j = 0; j <	nombre; j++)				printf(" x%d=%d", N - nombre + j, x[N - nombre + j]);
		}
	}
}