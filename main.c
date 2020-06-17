#include "lightsout.h" 
 
int N=25; 
int L = 5; 
int b[25]; 
int Matrice[5][5]; 
 
 
int main(int argc, char* argv[]) { 
	Randomizer(); 
	RandomizeMatrix(); 
	return 0; 
} 
 
void Randomizer() { 
	int i; 
	for (i = 0; i < N; i++) 
		{ 
		srand(time(NULL)); 
		b[i] = rand() % 2; 
		]} 
} 
 
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
	/** JUSTE POUR VERIFIER LA GENERATION RANDOM 
	printf("\n"); 
	for (line = 0; line < L; line++) { 
		printf("\n"); 
		for (column = 0; column < L; column++) 
			printf(" %d", Matrice[line][column]); 
		printf(" %d", b[line]); 
	} 
	getchar(); 
} 
*/ 
 
