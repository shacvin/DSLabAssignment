#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h> 
//! This is the main function which decryptes the output file and creates a decrypted output file.
int main(int argc, const char *argv[]){
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
    // printf("The number of characters in the input file is %d \n", fsize);
    
    char array[fsize];

    	for(int i = 0; i<fsize; i++){
		fscanf(f, "%c", &array[i]);
	}
	fclose(f);

	char array2[fsize];
		int j = 0;
	for(int i = 0; i<fsize; i++){
		j = (a*i + b)%n + (i/n)*n;
		array2[j] = array[i];
	}

	FILE* fo = fopen("decryptedOutputfile.txt", "w");
	for(int i  = 0; i<fsize; i++){
		fprintf(fo, "%c", array2[i]);
	}

	fclose(f);

	puts("Decrypted file has been created with name as decryptedOutputfile.txt");

	return 0;
}