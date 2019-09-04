#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <bits/stdc++.h>

using namespace std;

int main(){
	int n = 0;
	cin>>n;

    int a[n];
    for(int i = 0; i<n; i++){
    	cin>>a[i];
    }

    int xora[n];
    xora[0] = a[0];
    for(int i = 1; i<n; i++){
    	xora[i] = xora[i-1]^a[i];
    }

    int triplet[n][n];
    for(int i = 0; i<n; i++){
    	for(int j = 0; j<n; j++){
    		triplet[i][j] = 0;
    	}
    }
int count = 0;
    for(int i = 0; i<n-1; i++){
    	for(int k = i+1; k<n; k++){
            if(xora[k] == 0){
              count = k-i+count;
              triplet[i][k] = 1;
            }

            xora[k] = xora[k]^xora[i];
    	}
    }
    cout<<"The number of triplets are "<<count<<"\n";
     n = count;
    int tripletarray[n][n][n];
    for(int i = 0; i<n; i++){
        for(int j = 0; j<n; j++){
            for(int k = 0; k<n; k++){
                tripletarray[i][j][k] = 0;
            }
        }
    }


    for(int i = 0; i<n; i++){
    	for(int k = 0; k<n; k++){
    		if(triplet[i][k] == 1){
    			for(int j = i+2; j<k+2; j++){
    				//cout<<"The triplets are as "<<i+1<<" "<<j<<" "<<k+1<<"\n";
                    tripletarray[i+1][j][k+1] = 1;
    			}
    		}
    	}
    }

    for(int i = 0; i<n; i++){
        for(int j = 0; j<n; j++){
            for(int k = 0; k<n; k++){
                if(tripletarray[i][j][k] == 1){
                   cout<<"The triplets are as "<<i<<" "<<j<<" "<<k<<"\n";
                }
            }
        }
    }
        return 0;
}