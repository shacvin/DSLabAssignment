#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

//! The three arrays are declared globally.
int** Red;
int** Green;
int** Blue;

//! This is the function to read the given input file and pass the data to a array.
int** readFile (char *fileName){
	FILE* f;
	f = fopen(fileName, "r");
	int** fullarray = (int**)malloc(953*sizeof(int*));
    for(int i = 0; i<953; i++){
    	fullarray[i] = (int*)malloc(1268*sizeof(int));
    }
    for(int i= 0; i<953; i++){
    for(int j = 0; j<1268; j++){
    	if(j==1267){
             fscanf(f, "%d\n", &fullarray[i][j]);
    	}
        else{
        	fscanf(f, "%d,", &fullarray[i][j]);
        }
    }

    }
    fclose(f);
    
    return fullarray;
}
//! This is the function to write data to a output file from the edited array.
void writeFile(char* newFile, int** colorArray){
	FILE* f1;
	f1 = fopen(newFile, "w");
	for(int i = 0; i<953; i++){
	    for(int j = 0; j<1268; j++){
    	if(j==1267){
             fprintf(f1, "%d\n", colorArray[i][j]);
    	}
        else{
        	fprintf(f1, "%d,", colorArray[i][j]);
        }
    }
}
    fclose(f1);
}

//! This is to remove red pixel. It consists of nested for loop to make the red pixel value zero.
void removeRed(){
for(int i = 0; i<953; i++){
	for(int j = 0; j<1268; j++){
        if((Red[i][j] > Green[i][j]) && (Red[i][j] > Blue[i][j])){
        	Red[i][j] = 0;
        }
	}
}
}
//! This is to remove green pixel. It consists of nested for loop to make the green pixel value zero. 
void removeGreen(){
for(int i = 0; i<953; i++){
	for(int j = 0; j<1268; j++){
        if((Green[i][j] > Red[i][j]) && (Green[i][j] > Blue[i][j])){
        	Green[i][j] = 0;
        }
	}
}
}

//! This is to remove blue pixel. It consists of nested for loop to make the blue pixel value zero.
void removeBlue(){
for(int i = 0; i<953; i++){
	for(int j = 0; j<1268; j++){
        if((Blue[i][j] > Green[i][j]) && (Blue[i][j] > Red[i][j])){
        	Blue[i][j] = 0;
        }
	}
}
}

//! This is to keep red only. It removes green and blue pixel value using previous functions.
void RedOnly(){
	removeBlue();
	removeGreen();
    removeBlue();
}	

//! This is to keep green only. It removes red and blue pixel value using previous functions.
void GreenOnly(){
	removeBlue();
	removeRed();
    removeBlue();
}

//! This is to keep blue only. It removes green and red pixel value using previous functions.
void BlueOnly(){
	removeRed();
	removeGreen();
    removeRed();
}

//! This is to get pixel value at specified coordinates.
void GetPixel(int x, int y){
     printf("RedPixel = %d\n", Red[x-1][y-1]);
     printf("GreenPixel = %d\n", Green[x-1][y-1]);
     printf("BluePixel = %d\n", Blue[x-1][y-1]);
}

//! This is the main function.
int main (void){
	Red = readFile("Q3_ip_Red.dat");
	Green = readFile("Q3_ip_Green.dat");
	Blue = readFile("Q3_ip_Blue.dat");

	removeGreen();
    writeFile("removeGreen_out.dat", Green);
    writeFile("removeRed_out.dat", Red);
    writeFile("removeBlue_out.dat", Blue);
	GetPixel(320, 650);
	
}
