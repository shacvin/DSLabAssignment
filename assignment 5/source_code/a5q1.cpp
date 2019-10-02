// Simple C++ program to add two polynomials 
#include <iostream> 
using namespace std; 

// A utility function to return maximum of two integers 
int max(int m, int n) { return (m > n)? m: n; } 

// A[] represents coefficients of first polynomial 
// B[] represents coefficients of second polynomial 
// m and n are sizes of A[] and B[] respectively 
int *add(int A[], int B[], int m, int n) 
{ 
int size = max(m, n); 
int *sum = new int[size]; 

// Initialize the porduct polynomial 
for (int i = 0; i<m; i++) 
	sum[i] = A[i]; 

// Take ever term of first polynomial 
for (int i=0; i<n; i++) 
	sum[i] += B[i]; 

return sum; 
} 



int *multiply(int A[], int B[], int m, int n) 
{ 
   int *prod = new int[m+n-1]; 
  
   // Initialize the porduct polynomial 
   for (int i = 0; i<m+n-1; i++) 
     prod[i] = 0; 
  
   // Multiply two polynomials term by term 
  
   // Take ever term of first polynomial 
   for (int i=0; i<m; i++) 
   { 
     // Multiply the current term of first polynomial 
     // with every term of second polynomial. 
     for (int j=0; j<n; j++) 
         prod[i+j] += A[i]*B[j]; 
   } 
  
   return prod; 
} 

// A utility function to print a polynomial 
void printPoly(int poly[], int n) 
{ 
	for (int i=0; i<n; i++) 
	{ 
	cout << poly[i]; 
	if (i != 0) 
		cout << "x^" << i ; 
	if (i != n-1) 
	cout << " + "; 
	} 
} 


// Driver program to test above functions 
int main() 
{ 
	
	int m = 0;

	cout<<"Enter the number of expressions in first polynomial \n";
	cin>>m; 

      int A[m];

      cout<<"Enter the values of coefficients starting from power zero coefficient \n";

      for(int i = 0; i<m; i++){
      	cin>>A[i];
      }


      	int n = 0;

	cout<<"Enter the number of expressions in second polynomial \n";
	cin>>n; 
      int B[n];

      cout<<"Enter the values of coefficients starting from power zero coefficient \n";

      for(int i = 0; i<n; i++){
      	cin>>B[i];
      }
 

	cout << "First polynomial is \n"; 
	printPoly(A, m); 

	cout << "\nSecond polynomial is \n"; 
	printPoly(B, n);

    cout<<"\n";

    int c = 0; 
    cout<<"Enter 1 to add or 2 to multiply \n";
    cin>>c;

    if(c == 1){
    		int *sum = add(A, B, m, n); 
	int size = max(m, n); 

	cout << "\nsum polynomial is \n"; 
	printPoly(sum, size); 
	cout<<"\n";
    }

    else if(c==2){
    	int *prod = multiply(A, B, m, n); 
  
    cout << "Product polynomial is \n"; 
    printPoly(prod, m+n-1); 
    cout<<"\n";
  
    }
    
    else{
    	cout<<"Enter a valid choice \n";
    }

    
	return 0; 
} 
