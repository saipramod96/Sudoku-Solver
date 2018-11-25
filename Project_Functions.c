///////////////////////////////////////////////////////////////////////////////////////////

#include"Project_Header.h"

///////////////////////////////////////////////////////////////////////////////////////////

void Initialize(Grid S[9][9])
{
	int i,j,k;

	for(i=0;i<9;i++)
		for(j=0;j<9;j++)
		{
			S[i][j].Val=0;
			S[i][j].Flag=0;
			S[i][j].Index=-1;
         S[i][j].Twin=0;
         S[i][j].Tw_Row=-1;
         S[i][j].Tw_Col=-1;

			for(k=0;k<9;k++)
				S[i][j].Arr[k]=0;
		}
}

///////////////////////////////////////////////////////////////////////////////////////////

void Input_Sudoku( Grid S[9][9])
{
	int i,j,val,no;

	printf("\n How many givens ?");
	scanf("%d",&no);

	for(no;no>0;no--)
	{
		printf(" ------------------");
		while(1)
		{ 
			printf("\n  Enter Row:");
			scanf("%d",&i);

			if(i>0 && i<10)
				break;

			else
				printf("\nWrong Value !\n");
		}



		while(1)
		{
			printf("\n  Enter Column:");
			scanf("%d",&j);

			if(j>0 && j<10)
				break;

			else
				printf("\nWrong Value !\n");
		}


		if(S[i-1][j-1].Flag==1)
		{ 
			no++;
			printf("\n  Value already exists at that Cell !!! \n");
			continue;
		}  


		while(1)
		{ 
			printf("\n  Enter Value:");
			scanf("%d",&val);

			if(val>0 && val<10)
				break;

			else
				printf("\nWrong Value !\n");
		}


		S[i-1][j-1].Val=val;
		S[i-1][j-1].Flag=1;

	}

}

///////////////////////////////////////////////////////////////////////////////////////////

void Display(Grid S[9][9])
{  
	int i,j;

	system("clear");

	printf("\n\t\t******************* SUDOKU SOLUTIONS *******************\n");

	printf("\n\t\t\t------------- ------------- -------------");
	for(i=0;i<9;i++)
	{  printf("\n\t\t\t");

		for(j=0;j<9;j++)
		{
			if(S[i][j].Flag!=0)
				printf("| %d ",S[i][j].Val);  

			else
				printf("|   ",S[i][j].Val);  

			if((j+1)%3==0 && j!=8)
				printf("| ");

		}


		printf("|\n\t\t\t------------- ------------- -------------");

		if((i+1)%3==0 && i!=8)
			printf("\n\n\t\t\t------------- ------------- -------------");

	}
}

///////////////////////////////////////////////////////////////////////////////////////////

void Fill_Possibilities(Grid S[9][9])
{
	int i,j,k,row,col,Flag=0,a,b,m,n;

   Reset_Indices(S);
	for(row=0;row<=8;row++)
		for(col=0;col<=8;col++)
			if(S[row][col].Val==0)
			{   for(k=1;k<=9;k++)
				{
					for(i=0;i<=8;i++)
						if(S[i][col].Val==k || (S[i][col].Twin==1 && IsIn(S[i][col].Arr,S[i][col].Index,k)))
						{  Flag=1;
							break; 
						}

					for(j=0;j<=8;j++)
						if(S[row][j].Val==k || (S[row][j].Twin==1 && IsIn(S[row][j].Arr,S[row][j].Index,k)))
						{  Flag=1;
							break;
						}

					a=3*(row/3);
					b=3*(col/3);

					for(i=a;i<a+3;i+=1)
						for(j=b;j<b+3;j+=1)
						if(S[i][j].Val==k || (S[i][j].Twin==1 && IsIn(S[i][j].Arr,S[i][j].Index,k)))
							{  Flag=1;
								break; 
							}


					if(Flag==0)
						S[row][col].Arr[++(S[row][col].Index)]=k;  

					Flag=0;
				}
			}

}

/////////////////////////////////////////////////////////////////////////////////////////
void Existence(Grid S[9][9])
{
	int Row,Col,Box,k,Count[9]={0};

	for(Row=0;Row<9;Row++)
	{
		for(Col=0;Col<9;Col++)
			if(S[Row][Col].Flag==1)
				Count[S[Row][Col].Val-1]++;

		for(k=0;k<9;k++)
		{
			if(Count[k]>1)
			{
				printf("WRONG QUESTION !!!\n");
				exit(1);
			}
		} 
		for(k=0;k<9;k++)
			Count[k]=0;
	}


	for(Col=0;Col<9;Col++)
	{
		for(Row=0;Row<9;Row++)
			if(S[Row][Col].Val!=0)
				Count[S[Row][Col].Val-1]++;

		for(k=0;k<9;k++)
		{ if(Count[k]>1)
			{
				printf("WRONG QUESTION !!!\n");
				exit(1);
			}
		}
		for(k=0;k<9;k++)
			Count[k]=0;
	}


	for(Box=0;Box<9;Box++)
	{
		for(Row=3*(Box/3);Row<3*(Box/3+1);Row++)
			for(Col=3*(Box%3);Col<3*(Box%3+1);Col++)
				if(S[Row][Col].Val!=0)
					Count[S[Row][Col].Val-1]++;


		for(k=0;k<9;k++)
		{ if(Count[k]>1)
			{
				printf("WRONG QUESTION !!!\n");
				exit(1);
			}
		} 
		for(k=0;k<9;k++)
			Count[k]=0;
	}

}   
////////////////////////////////////////////////////////////////////////////
void Twins_Unique(Grid S[9][9])
{
	int N1,N2,Flag=0,Row,Col,i,j,k,l,Store,a,b;

	for(Row=0;Row<9;Row++)
	{                           //taking one cell.
		for(Col=0;Col<9;Col++)
			if(S[Row][Col].Val==0 && S[Row][Col].Twin==0)
			{
				for(i=0;i<S[Row][Col].Index;i++)
					for(j=i+1;j<=S[Row][Col].Index;j++)
					{                //taking combos from array of possibilities.
						N1=S[Row][Col].Arr[i]; N2=S[Row][Col].Arr[j];
////////////////////row-wise checking/////////////////////////////////////						
                  Flag=0;
						for(k=0;k<9;k++)
						{
							if(k!=Col && S[Row][k].Val==0)
							{
								if((IsIn(S[Row][k].Arr,S[Row][k].Index,N1)) || (IsIn(S[Row][k].Arr,S[Row][k].Index,N2)))
								{
									Flag++;
                           if(Flag==1)
                             Store=k;
                           else if (Flag>1)
                             break;
								}
                     }
                  }
/////////////////checking for result after row-wise checking////////////////////
						if(Flag==1)          //twins found in row.
						{
							S[Row][Col].Arr[0]=N1;
							S[Row][Col].Arr[1]=N2;
							S[Row][Col].Index=1;
							S[Row][Col].Twin=1;
                     S[Row][Col].Tw_Row=Row;
                     S[Row][Col].Tw_Col=Store;
							S[Row][Store].Arr[0]=N1;
							S[Row][Store].Arr[1]=N2;
							S[Row][Store].Index=1;
							S[Row][Store].Twin=1;
                     S[Row][Store].Tw_Row=Row;
                     S[Row][Store].Tw_Col=Col;
							printf("\nr. Twins %d&%d in (%d,%d)&(%d,%d)\n",N1,N2,Row+1,Col+1,Row+1,Store+1);
                     Fill_Possibilities(S);
						}

//////////////////twins not found in row.checking column-wise///////////////////
						if(Flag>1)
                  {
							Flag=0;
							for(k=0;k<9;k++)
							{
								if(k!=Row && S[k][Col].Val==0)
								{
									if((IsIn(S[k][Col].Arr,S[k][Col].Index,N1)) || (IsIn(S[k][Col].Arr,S[k][Col].Index,N2)))
									{
										Flag++;
                           	if(Flag==1)
                             		Store=k;
										else if(Flag>1)
											break;
									}
                     	}
                  	}
////////////////////checking for result after column-wise checking///////////
							if(Flag==1)//twins found in col.
							{  
								S[Row][Col].Arr[0]=N1;
								S[Row][Col].Arr[1]=N2;
								S[Row][Col].Index=1;
								S[Row][Col].Twin=2;
                     	S[Row][Col].Tw_Row=Row;
                     	S[Row][Col].Tw_Col=Col;
								S[Store][Col].Arr[0]=N1;
								S[Store][Col].Arr[1]=N2;
								S[Store][Col].Index=1;
								S[Store][Col].Twin=2;
                     	S[Store][Col].Tw_Row=Store;
                     	S[Store][Col].Tw_Col=Col;
								printf("\nc. Twins %d&%d in (%d,%d)&(%d,%d)\n",N1,N2,Row+1,Col+1,Row+1,Store+1);
                     	Fill_Possibilities(S);
						   }
///////////////////twins not found in col.check block-wise.//////////////
                     if(Flag>1)
                     {
                        Flag=0;
                        a=3*(Row/3); b=3*(Col/3);
                        for(k=a;k<a+3;k++)
									for(l=b;l<b+3;l++)
                              {
											if(!(k==Row && l==Col) && S[k][l].Val==0)
											{
												if((IsIn(S[k][l].Arr,S[k][l].Index,N1)) || (IsIn(S[k][l].Arr,S[k][l].Index,N2)))
												{
													Flag++;
                           				if(Flag==1)
                             					Store=k;
													else if(Flag>1)
														break;
												}
                     				}
                              }
					      	if(Flag==1)          //twins found in row.
								{
									S[Row][Col].Arr[0]=N1;
									S[Row][Col].Arr[1]=N2;
									S[Row][Col].Index=1;
									S[Row][Col].Twin=1;
                     		S[Row][Col].Tw_Row=Row;
                     		S[Row][Col].Tw_Col=Store;
									S[Row][Store].Arr[0]=N1;
									S[Row][Store].Arr[1]=N2;
									S[Row][Store].Index=1;
									S[Row][Store].Twin=1;
                     		S[Row][Store].Tw_Row=Row;
                     		S[Row][Store].Tw_Col=Col;
									printf("\nb. Twins %d&%d in (%d,%d)&(%d,%d)\n",N1,N2,Row+1,Col+1,Row+1,Store+1);
                     		Fill_Possibilities(S);
								}
                     }
                  }
				  }
		   }

	}

}
///////////////////////////////////////////////////////////////////////////
int IsIn(int *Arr,int Index,int k)
{
	int i,Flag=0;

	for(i=0;i<=Index;i++)
		if(Arr[i]==k)
		{
			Flag=1;
			break;
		}
	return Flag;
} 
//////////////////////////////////////////////////////////////////////////
void Reset_Indices(Grid S[9][9])
{
	int Row,Col; 
 
   for(Row=0;Row<9;Row++)
		for(Col=0;Col<9;Col++)
			{
          if(S[Row][Col].Val==0 && S[Row][Col].Twin==0)
            S[Row][Col].Index=-1;
    		}
}
///////////////////////////////////////////////////////////////////////////
void Fill_Possibilities_Twins(Grid S[9][9])
{
	int val1,val2,Row,Col,k,i,j,a,b;

	for(Row=0;Row<9;Row++)
		for(Col=0;Col<9;Col++)
			{
/////////////////////if twin along row/////////////////////////////////////
				if(S[Row][Col].Val==0 && S[Row][Col].Twin==1)
				{
               val1=S[Row][Col].Arr[0];
               val2=S[Row][Col].Arr[1];
//check col-wise
					for(k=0;k<9;k++)
						if(k!=Row)
                  {
                     if(S[k][Col].Val==val1)
                     {
								S[Row][Col].Val=val2;
                        S[Row][Col].Index=-1;
								S[Row][Col].Twin=0;
                        S[Row][S[Row][Col].Tw_Col].Val=val1;
                        S[Row][S[Row][Col].Tw_Col].Index=-1;
                        S[Row][S[Row][Col].Tw_Col].Twin=0;
								S[Row][Col].Tw_Row=-1; //change twin row & col of twins to -1
								S[Row][Col].Tw_Col=-1;
								S[Row][S[Row][Col].Tw_Col].Tw_Row=-1;
								S[Row][S[Row][Col].Tw_Col].Tw_Row=-1;
                     }
                  }
//check box-wise
					a=3*(Row/3);
					b=3*(Col/3);
					for(i=a;i<a+3;i++)
						for(j=b;j<b+3;j++)
							{
                    		 if(S[i][j].Val==val1)
                     	{
								  	S[Row][Col].Val=val2;
                        	S[Row][Col].Index=-1;
									S[Row][Col].Twin=0;
                       	   S[Row][S[Row][Col].Tw_Col].Val=val1;
                        	S[Row][S[Row][Col].Tw_Col].Index=-1;
                        	S[Row][S[Row][Col].Tw_Col].Twin=0;
									S[Row][Col].Tw_Row=-1; //change twin row & col of twins to -1
									S[Row][Col].Tw_Col=-1;
									S[Row][S[Row][Col].Tw_Col].Tw_Row=-1;
									S[Row][S[Row][Col].Tw_Col].Tw_Row=-1;
                      	}
                     }
				}
/////////////////////if twin along column//////////////////////////////////
				if(S[Row][Col].Val==0 && S[Row][Col].Twin==2)
				{
              	val1=S[Row][Col].Arr[0];
              	val2=S[Row][Col].Arr[1];
//check row-wise
					for(k=0;k<9;k++)
						if(k!=Col)
                  {
                    	if(S[Row][k].Val==val1)
                    	{
								S[Row][Col].Val=val2;
                       	S[Row][Col].Index=-1;
								S[Row][Col].Twin=0;
                       	S[S[Row][Col].Tw_Row][Col].Val=val1;
                       	S[S[Row][Col].Tw_Row][Col].Index=-1;
                       	S[S[Row][Col].Tw_Col][Col].Twin=0;
								S[Row][Col].Tw_Row=-1; 
       						S[Row][Col].Tw_Col=-1;
								S[S[Row][Col].Tw_Row][Col].Tw_Row=-1;
								S[S[Row][Col].Tw_Row][Col].Tw_Row=-1;
                     }
                  }
//check box-wise
						a=3*(Row/3);
						b=3*(Col/3);
						for(i=a;i<a+3;i++)
							for(j=b;j<b+3;j++)
								{
                  			if(S[i][j].Val==val1)
                     		{
								  		S[Row][Col].Val=val2;
                        		S[Row][Col].Index=-1;
										S[Row][Col].Twin=0;
                       	   	S[S[Row][Col].Tw_Row][Col].Val=val1;
                        		S[S[Row][Col].Tw_Row][Col].Index=-1;
                        		S[S[Row][Col].Tw_Row][Col].Twin=0;
										S[Row][Col].Tw_Row=-1; //change twin row & col of twins to -1
										S[Row][Col].Tw_Col=-1;
										S[S[Row][Col].Tw_Row][Col].Tw_Row=-1;
										S[S[Row][Col].Tw_Row][Col].Tw_Row=-1;
                      		}
                     	}
            }
/////////////////////////////if twin in box///////////////////////////
            if(S[Row][Col].Val==0 && S[Row][Col].Twin==3)
            {
              	val1=S[Row][Col].Arr[0];
              	val2=S[Row][Col].Arr[1];
//check row-wise
					for(k=0;k<9;k++)
						if(k!=Col)
                  {
                    	if(S[Row][k].Val==val1)
                    	{
								S[Row][Col].Val=val2;
                       	S[Row][Col].Index=-1;
								S[Row][Col].Twin=0;
                       	S[S[Row][Col].Tw_Row][S[Row][Col].Tw_Col].Val=val1;
                       	S[S[Row][Col].Tw_Row][S[Row][Col].Tw_Col].Index=-1;
                       	S[S[Row][Col].Tw_Row][S[Row][Col].Tw_Col].Twin=0;
								S[Row][Col].Tw_Row=-1; //change twin row & col of twins to -1  
       						S[Row][Col].Tw_Col=-1;
								S[S[Row][Col].Tw_Row][S[Row][Col].Tw_Col].Tw_Row=-1;
								S[S[Row][Col].Tw_Row][S[Row][Col].Tw_Col].Tw_Row=-1;
                     }
                  }
//check col-wise
					for(k=0;k<9;k++)
						if(k!=Row)
                  {
                     if(S[k][Col].Val==val1)
                     {
								S[Row][Col].Val=val2;
                        S[Row][Col].Index=-1;
								S[Row][Col].Twin=0;
                       	S[S[Row][Col].Tw_Row][S[Row][Col].Tw_Col].Val=val1;
                       	S[S[Row][Col].Tw_Row][S[Row][Col].Tw_Col].Index=-1;
                       	S[S[Row][Col].Tw_Row][S[Row][Col].Tw_Col].Twin=0;
								S[Row][Col].Tw_Row=-1; //change twin row & col of twins to -1
								S[Row][Col].Tw_Col=-1;
								S[S[Row][Col].Tw_Row][S[Row][Col].Tw_Col].Tw_Row=-1;
								S[S[Row][Col].Tw_Row][S[Row][Col].Tw_Col].Tw_Row=-1;
                     }
                  }
            }
//////////////////////////////////////////////////////////////////////////////////
			}
}
