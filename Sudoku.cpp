#include "Sudoku.h"
void Sudoku::swap(int &a,int &b)
{
	    int store;
		    store=a;
		    a=b;
		    b=store;
}
/*-------------------------------------------------------------------------------*/
void Sudoku::giveQuestion()
{
	    srand (time(NULL));
	    int i,j,k;
	    int question[N][N]={1,2,3,4,5,6,7,8,9,
							4,5,6,7,8,9,1,2,3,
					        7,8,9,1,2,3,4,5,6,
						    2,1,4,3,6,5,8,9,7,
						    3,6,5,8,9,7,2,1,4,
						    8,9,7,2,1,4,3,6,5,
						    5,3,1,6,4,2,9,7,8,
						    6,4,2,9,7,8,5,3,1,
						    9,7,8,5,3,1,6,4,2,};
		for(i=0;i<N;i++)    for(j=0;j<N;j++)    board[i][j]=question[i][j];
		for(k=0;k<50;k++)
		{
			i=rand()%9;
		    j=rand()%9;
		    board[i][j]=0;
		}
		changeNum(rand()%9+1,rand()%9+1);
		changeRow(rand()%3,rand()%3);
		changeCol(rand()%3,rand()%3);
	    rotate(rand()%101);
	    flip(rand()%2);
        printout(true);
}
/*-------------------------------------------------------------------------------*/
void Sudoku::readIn()
{
	    int i,j;
	    for(i=0;i<N;i++)
        for(j=0;j<N;j++)
        scanf("%d",&board[i][j]);
}
/*-------------------------------------------------------------------------------*/
void Sudoku::changeNum(int a,int b)
{
	    if (a==b)   return;
	    int i,j;
	    for(i=0;i<N;i++)
        for(j=0;j<N;j++)
        {
	        if(board[i][j]==a)  board[i][j]=b;
	        else if(board[i][j]==b) board[i][j]=a;
	    }
}
/*-------------------------------------------------------------------------------*/
void Sudoku::changeRow(int a,int b)
{
	    if (a==b)   return;
	    int i,j;
	    a*=3;
	    b*=3;
	    for(i=0;i<3;i++,a++,b++)
	    for(j=0;j<N;j++)	swap(board[a][j],board[b][j]);
}
/*-------------------------------------------------------------------------------*/
void Sudoku::changeCol(int a,int b)
{
	    if (a==b)   return;
	    int i,j;
	    a*=3;
	    b*=3;
	    for(i=0;i<3;i++,a++,b++)
        for(j=0;j<N;j++)	swap(board[j][a],board[j][b]);
}
/*-------------------------------------------------------------------------------*/
void Sudoku::rotate (int n)
{
	    int storage[N][N];
	    int i,j;
	    for(n%=4;n>0;n--)
	    {
	        for(i=0;i<4;i++)
	            for(j=0;j<5;j++)
	            {
	            swap(board[i][j],board[8-j][i]);
	            swap(board[8-j][i],board[8-i][8-j]);
	            swap(board[8-i][8-j],board[j][8-i]);
	            }
		}
}
/*-------------------------------------------------------------------------------*/
void Sudoku::flip(int n)
{
	int i,j,k;
	int storage;
    for(i=0;i<4;i++)
		for(j=0;j<N;j++)
	        if(n==0)    swap(board[i][j],board[8-i][j]);
	        else if (n==1)  swap(board[j][i],board[j][8-i]);
}
/*-------------------------------------------------------------------------------*/
void Sudoku::printout(bool t)
{
	    if(!t)  return;
		int i,j;
		for(i=0;i<N;i++)
			for(j=0;j<N;j++)
				printf("%d%c",board[i][j],(j!=8)?' ':'\n');
}
/*-------------------------------------------------------------------------------*/
void Sudoku::transform()
{
	    srand (time(NULL));
	    changeNum(rand()%9+1,rand()%9+1);
	    changeRow(rand()%3,rand()%3);
	    changeCol(rand()%3,rand()%3);
	    rotate(rand()%101);
	    flip(rand()%2);
	    printout(true);
}
/*-------------------------------------------------------------------------------*/
bool Sudoku::used(int a,int b, int c)
{
	if(N<c || c<1)	return false;
	return(rowused[a][c] || columnused[b][c] || blockused[a/3][b/3][c])? true: false;
}
/*-------------------------------------------------------------------------------*/
void Sudoku::set(int a,int b,int c,bool t)
{
	rowused[a][c]=t;
	columnused[b][c]=t;
	blockused[a/3][b/3][c]=t;
}
/*-------------------------------------------------------------------------------*/
void Sudoku::initial()
{
	int i,j;
	for(i=0;i<N;i++)
		for(j=0;j<11;j++)
		{
			rowused[i][j]=false;
			columnused[i][j]=false;
			blockused[i/3][i%3][j]=false;
		}
	for(i=0;i<N;i++)
		for(j=0;j<N;j++)
			if(board[i][j]!=0)	set(i,j,board[i][j],true);
}
/*-------------------------------------------------------------------------------*/
void Sudoku::eliminate(int a,int b,int c)
{
	int i,j;
	int csa=a/3*3;
	int csb=b/3*3;
	for(i=0;i<N;i++)
	{
		possible[a][i][c]=false;
		possible[i][b][c]=false;
	}
	for(i=csa;i<csa+3;i++)
		for(j=csb;j<csb+3;j++)	possible[i][j][c]=false;				
}
/*-------------------------------------------------------------------------------*/
bool Sudoku::check()
{
	int i,j,k,l,h,space;
	bool run;
	for(h=1;h<10;h++)
	{
		for(i=0;i<N;i++)
		{
			for(j=0,space=0,run=false;j<N;j++)
			if(possible[i][j][h])
			{
				run=true;
				space++;
				if(board[i][j]!=0)	space--;
			}
		if(space==0 && run) return false;
		for(j=0,space=0,run=false;j<N;j++)
			if(possible[j][i][h])
			{
				run=true;
				space++;
				if(board[j][i]!=0)	space--;
			}
		if(space==0 && run)	return false;
		}	
		for(i=0;i<N;i+=3)
		{
			for(j=0;j<N;j+=3)
			{
				for(k=i,space=0,run=false;k<i+3;k++)
					{
						for(l=j;l<j+3;l++)
							{
								if (possible[k][l][h])
								{
									run=true;
									space++;
									if(board[k][l]!=0)	space--;
								}
							}	
					}
				if(space==0 && run)	return false;
			}
		}
	}
	return true;
}
/*-------------------------------------------------------------------------------*/
bool Sudoku::proof()
{
	int i,j;
	for (i=0;i<N;i++)
	for(j=0;j<N;j++)
	if(board[i][j]!=0)
	{
		if(!possible[i][j][board[i][j]])
		{
			printf("0\n");
			return false;
		}
		eliminate(i,j,board[i][j]);
	}
	if(check())	return true;
	else	{printf("0\n");	return false;}
}
/*-------------------------------------------------------------------------------*/
bool Sudoku::backtrack()
{
	int i,j,now,next,storage[N][N],answer1[N][N];
	bool test[N][N],only=true;

	for(i=0;i<N;i++)
		for(j=0;j<N;j++)
		{
			if (board[i][j]!=0)	test[i][j]=true;
			else 				test[i][j]=false;	
			storage[i][j]=board[i][j];
		}
	initial();
	for(now=0,next=1;now<=80;now+=next)
	{
		i=now/9;
		j=now%9;
		if (test[i][j])	continue;	next=1;
		if (board[i][j]>0)	set(i,j,board[i][j],false);
		do{board[i][j]++;}	while(used(i,j,board[i][j]));
		if(board[i][j]<10)	set(i,j,board[i][j],true);	
		else{board[i][j]=0;	next=-1;}			
	}
	for(i=0;i<N;i++)
		for(j=0;j<N;j++)
		{
			answer1[i][j]=board[i][j];
			board[i][j]=storage[i][j];
			if(board[i][j]==0)	board[i][j]=10;
		}

	initial();
	for(now=0,next=1;now<=80;now+=next)
	{
		i=now/9;	j=now%9;
		if (test[i][j])	continue;
		next=1;
		if (board[i][j]<10)	set(i,j,board[i][j],false);
		do{board[i][j]--;}	while(used(i,j,board[i][j]));
		if(board[i][j]>0)		set(i,j,board[i][j],true);
		else{board[i][j]=10;	next=-1;}			
	}	
	for(i=0;i<N;i++)
	{
		for(j=0;j<N;j++)
			if(board[i][j]!=answer1[i][j])
			{
				only=false;
				break;
			}
		if(!only)	break;
	}
	printf("%d\n",only? 1: 2);
	return only;
}
/*-------------------------------------------------------------------------------*/
void Sudoku::solve()
{
	int i,j,k;
	for (i=0;i<N;i++)
		for(j=0;j<N;j++)
			for(k=1;k<10;k++)
			possible[i][j][k]=true;
	if(!proof())	return;
	printout(backtrack());
}

