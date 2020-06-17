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
 
 int SwapLine(int Line) {
	int flag, lineswap, i, auxb;
	flag = 0;
	int aux[25];
	for (lineswap = Line + 1; lineswap < N; lineswap++) {
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

void Unique(void) {
	int line, Line, column, i, auxb;
	int aux[25];
	for (Line = N - 1; Line > 0; Line--) {
		if (Matrice[Line][Line] == 0) {
			for (line = Line - 1; line >= 0; line--) {
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

void Multiple(int LL, int nombre) {
	int sln, i, q, j, line, column, Line, cumul, n, auxb;
	int x[25], aux[25];
	sln = pow(2, nombre);
	for (n = 0; n < sln; n++) {
		for(i = 0; i < nombre; i++)
			for(j = 0; j < N; j++){
				Matrice[i][j] = Msave[i][j];
			}
		for (i = 0; i < N; i++)
			b[i] = bsave[i];
		q = n;
		for (i = 0; i < nombre; i++) {
			x[N - 1 - i] = q % 2;
			q = q / 2;
		}
		for (line = 0; line < LL; line++) {
			cumul = 0;
			for (j = 0; j < nombre; j++)
				cumul += x[N - 1 - j] * Matrice[line][N - 1 - j];
			b[line] = (b[line] + cumul) % 2;
		}
		for (j = 0; j < nombre; j++) {
			for (Line = LL - 1; Line > 0; Line--) {
				if (Matrice[Line][Line] == 0)
					for (line = Line - 1; line >= 0; line--) {
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
				for (line = Line - 1; line >= 0; line--) {
					if (Matrice[line][Line] != 0) {
						for (column = Line; column >= 0; column--)
							Matrice[line][column] = (Matrice[line][column] + Matrice[Line][column]) % 2;
						b[line] = (b[line] + b[Line]) % 2;
					}
				}
			}
			for (i = 0; i < N - nombre; i++) 
				printf(" x%d=%d", i, b[i]);
			for (j = 0; j < nombre; j++)
				printf(" x%d=%d", N - nombre + j, x[N - nombre + j]);
		}
	}
}
