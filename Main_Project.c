#include"Project_Header.h"

int main()
{
	Grid S[9][9];
	int i,j,row,col;

	Initialize(S);

	printf("\n\n");
	Input_Sudoku(S);

	Display(S);
	printf("\n\n\n\n");

	Fill_Possibilities(S);

	/*  for(row=0;row<9;row++,printf("\n"))
	    for(col=0;col<9;col++)
	    {
	    for(i=0;i<=S[row][col].Index;i++)
	    printf(" %d,",S[row][col].Arr[i]);
	    printf("\n");
	    }*/

	//Existence(S);
        Twins_Unique(S);

	printf("\n\n\n\n");
	return 0;
}
