#include<stdio.h>
#include<stdlib.h>
/*#define EXIT {printf("WRONG QUESTION!!!");/
  exit(1);}*/

typedef struct 
{
	int Val;
	int Arr[9];
	int Flag;
	int Index;
	int Twin;
   int Tw_Row;
   int Tw_Col;
}Grid;

void Input_Sudoku( Grid S[9][9]);
void Initialize(Grid S[9][9]);
void Fill_Possibilities(Grid S[9][9]);
void Existence(Grid S[9][9]);
void Twins_Unique(Grid S[9][9]);
int IsIn(int *Arr,int Index,int k);
void Reset_Indices(Grid S[9][9]);
