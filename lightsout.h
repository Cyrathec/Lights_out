#pragma once
#ifndef _LIGHTSOUT_H_
#define _LIGHTSOUT_H_

#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#define PAS 30
#define X_ORIGINE 50
#define Y_ORIGINE 50
#define TRUE 1
#define FALSE 0

int main(int argc, char* argv[]);
void randomize();
void RandomizeMatrix();
int SwapLine(int Line);
void NextLine(int Line);
void Unique(void);
void Multiple(int LL, int nombre);
#endif