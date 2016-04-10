#include <ctime>
#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <cstring>
using namespace std;
#define N 9
class Sudoku{
				public:
						void giveQuestion();
						void readIn();
						void changeNum(int,int);
						void changeRow(int,int);
						void changeCol(int,int);
						void rotate(int);
						void flip(int);
						void transform();
						void solve();

				private:
						void swap(int &,int &);
						void eliminate(int,int,int);
						void initial();
						void printout(bool);
						void set(int,int,int,bool);
						bool check();
						bool backtrack();
						bool proof();			
						bool used(int,int,int);
						bool rowused[N][11],columnused[N][11];
						bool blockused[3][3][11],possible[N][N][10];
						int board[N][N];	
};
