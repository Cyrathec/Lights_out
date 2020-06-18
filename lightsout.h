#ifndef _LIGHTSOUT_H_
#define _LIGHTSOUT_H_

void Randomize(int* b, int nb_cases);
void RandomizeMatrix(int** matrice, int weight, int nb_cases);
int SwapLine(int** matrice, int* b, int nb_cases, int line);
void NextLine(int** matrice, int* b, int nb_cases, int line);
void Unique(int** matrice, int* b, int nb_cases);
void Multiple(int** matrice, int** msave, int* b, int* bsave, int nb_cases, int LL, int nombre);

#endif