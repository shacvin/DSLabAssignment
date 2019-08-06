#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h> 

int main(int argc, const char* argv[]){
	FILE* fi = fopen(argv[1], "r");
	FILE* fo = fopen(argv[2], "r");
	char c1 = fgetc(fi);
	char c2 = fgetc(fo);
	int count = 0;
	while(c1!=EOF && c2!=EOF){
     if(c1!=c2){
     count++;
     break;
     }
     c1 = fgetc(fi);
     c2 = fgetc(fo);
	}

	if(count==0){
		puts("The files are same!");
	} 
	else{
		puts("The files are different!");
	}
	fclose(fi);
	fclose(fo);

	return 0;
}