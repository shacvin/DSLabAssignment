#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h> 


//! This is the main function for encrypting and saving the file in the same directory. It saves the file with name as outputfile.
int main(int argc, const char *argv[])
{
	int n = atoi (argv[1]);
	int a = atoi (argv[2]);
	int b = atoi (argv[3]);

		FILE* f = fopen(argv[4], "r");
	if(f == NULL){
		printf("File could not be opened");

	}
	fseek(f, 0, SEEK_END);
    int fsize = ftell(f);
    rewind(f);
	
	printf("The number of characters in the input file is %d \n", fsize);
	int size = 0;
    if(fsize%n == 0)
    	size = fsize;
    else{
    	size = fsize + n - fsize%n;
    }
    
	char array[size];
	for(int i = 0; i<=fsize; i++){
		fscanf(f, "%c", &array[i]);
	}
	for(int i = fsize ; i<size; i++){
		array[i] = '\0';
	}
	
	for(int i = 0; i<size; i++){
		printf("%c", array[i]);
	}
	printf("\n");
   
	fclose(f);
		char arr2 [size];
	int j = 0;
	for(int i = 0; i<size; i++){
		j = (a*i + b)%n + (i/n)*n;
		arr2[i] = array[j];
	
	}

	FILE* fo = fopen("outputfile.txt", "w");
	for(int i  = 0; i<size; i++){
		fprintf(fo, "%c", arr2[i]);
	}
fclose(f);

puts("Output file has been created with name as outputfile.txt");



	return 0;
}