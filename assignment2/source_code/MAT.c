#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h> 
#include <math.h>
//! This are some globally declared variables:size of the input array, bit value and output array.
int size = 0;
int bit = 0;
int** maxArray;


//! This is the recursive function which gives the output array or maximal array and also gives the values of leaf node, level and initial value(0 or 1).
void maximalArray(int** a, int i, int j, int k, int l){

	int localSize=k-i+1;

  if(maxArray[i][j] != 0){
      	return;
    }


     int count = 0;
      int value = a[i][j];

      bool b=false;
      for(int m = i; m<=k; m++){
      	for(int n = j; n<=l; n++){
           if(a[m][n] != value){
           	count++;
           	b=true;
           	break;
           }

      	}
      	if (b)
      	{
      		break;
      	}
      }
      int s = k-i+1;
      int level = (int)(log2(size)) - (int)(log2(s));

      if(count == 0){
      	bit++;
      	for(int m = i; m<=k; m++){
      	   for(int n = j; n<=l; n++){
               maxArray[m][n] = bit;
       	}
      }

      printf("(%d, %d, %d)", bit, a[i][j], level);
      puts("");

      }
    

      else{ 
      maximalArray(a, i, j, i + (localSize/2) - 1, j + (localSize/2) - 1);
      maximalArray(a, i, j + (localSize/2), i + (localSize/2) - 1, j + localSize - 1);
      maximalArray(a, i + (localSize/2), j, i + localSize - 1, j + (localSize/2) - 1);
      maximalArray(a, i + (localSize/2), j + (localSize/2), i + localSize - 1, j + localSize - 1);

     }

}
//! This is the main function which reads the input array and calls recursive function. It also allocates memory for the input and output arrays.
int  main(int argc, const char *argv[])
{
	

	FILE* f = fopen(argv[1], "r");
	fseek(f, 0, SEEK_END);

	int fsize = (int)pow(ftell(f)/2, 0.5);

	rewind(f);
	printf("%d\n", fsize);

	double x = (double)log(fsize)/(double)log(2);
	int y = (int)ceil(x);
    size = (int)pow(2, y);
    printf("%d\n", size);

     maxArray = (int**)malloc(size*sizeof(int*));
      for(int m = 0; m<size; m++){
      	maxArray[m] = (int*)malloc(size*sizeof(int));
      	memset(maxArray[m],0,size*sizeof(int));
      }

    int** array = (int**)malloc(size*sizeof(int*));

    for(int i = 0; i<size; i++){
    	array[i] = (int*)malloc(size*sizeof(int));
    }

    for(int i = 0; i<size; i++){
    	for(int j = 0; j<size; j++){
    		array[i][j] = 0;
    	}
    }

    for(int i = size-fsize; i<size; i++){
    	for(int j = size-fsize; j<size; j++){
    		fscanf(f, "%d", &array[i][j]);
    	}
    }
    
  
    for(int i = 0; i<size; i++){
    	for(int j = 0; j<size; j++){
    		printf("%d", array[i][j]);
    	}
    	puts("");
    }
	puts("QuadTree");
	maximalArray(array, 0, 0, size-1, size-1);

	puts("Maximal Array");
	for(int i = 0; i<size; i++){
		for(int j = 0; j<size; j++){
			printf("%2d ", maxArray[i][j]);
		}
		puts("");
	}
	return 0;

}