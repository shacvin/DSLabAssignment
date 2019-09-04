
#include<bits/stdc++.h> 
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;
// #define N 4 

// int N = 0;
void printSolution(int** board, int p) 
{ 
	static int k = 1; 
	printf("%d-\n",k++); 
	for (int i = 0; i < p; i++) 
	{ 
		for (int j = 0; j < p; j++) 
			printf(" %d ", board[i][j]); 
		printf("\n"); 
	} 
	printf("\n"); 
} 


bool isSafe(int** board, int row, int col, int z) 
{ 
	int i, j; 


	for (i = 0; i < col; i++) 
		if (board[row][i]) 
			return false; 


	for (i=row, j=col; i>=0 && j>=0; i--, j--) 
		if (board[i][j]) 
			return false; 


	for (i=row, j=col; j>=0 && i<z; i++, j--) 
		if (board[i][j]) 
			return false; 

	return true; 
} 


bool solveNQUtil(int** board, int col, int y) 
{ 
	
	if (col == y) 
	{ 
		printSolution(board, y); 
		return true; 
	} 

	
	bool res = false; 
	for (int i = 0; i < y; i++) 
	{ 
	
		if ( isSafe(board, i, col, y) ) 
		{ 
	
			board[i][col] = 1; 

		
			res = solveNQUtil(board, col + 1, y) || res; 

			board[i][col] = 0; 
		} 
	} 

	
	return res; 
} 


void solveNQ(int x) 
{ 
	int** board = new int*[x];
	for(int i = 0; i<x; i++){
		board[i] = new int[x];
	} 
	for(int i= 0; i<x; i++){
		for (int j = 0; j < x; j++)
		{
			board[i][j] = 0;
		}
	}

	if (solveNQUtil(board, 0, x) == false) 
	{ 
		printf("Solution does not exist"); 
		return ; 
	} 

	return ; 
} 


int main() 
{ 
	int N = 0;
	cout<<"Enter the number N"<<"\n";
    cin>>N;
	solveNQ(N); 
	return 0; 
} 
