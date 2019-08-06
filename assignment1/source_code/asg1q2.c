#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/*!
This is my deque. It has 4 properties.
*/
struct Deque
{
	int size;
	int capacity;
	int* array;
	int rear;

};
//! This is to provide memory to the deque and initialize some of its properties.
 struct Deque* makedeque(int capc){
 	struct Deque* deq = (struct Deque*) malloc(sizeof(struct Deque));
	deq->array = (int*)malloc(deq->capacity * sizeof(int));
	deq->capacity = capc;
	deq->size = 0;
	deq->rear = -1;
 	return deq;
}
//! This is to check if deque is full.
bool isFull(struct Deque* deque){
	return(deque->size == deque->capacity);
}
//! This is to check if deque is half.
bool isHalf(struct Deque* deque) 
{ 
    return (deque->size == (deque->capacity)/2); 
} 

//! This is to double deque's capacity using realloc function.
void capdouble(struct Deque* deque){
	deque->capacity = deque->capacity*2;
	deque->array  = (int*)realloc(deque->array, deque->capacity * sizeof(int));
}
//! This is to half deque's capacity using realloc function.
void caphalf(struct Deque* deque){
	deque->capacity = (deque->capacity)/2;
	deque->array = (int*)realloc(deque->array, deque->capacity * sizeof(int));
}
//! This is to insert an element from front and also move elements by one position using memmove function.
void insertFront(struct Deque* deque, int data) 
{ 
    if(isFull(deque)){
      capdouble(deque);
      
    } 

    memmove(&(deque->array[1]), &(deque->array[0]), deque->size * sizeof(int));
    deque->array[0] = data;
    deque->rear++;
    deque->size++;

} 
//! This is to insert an element from rear.
void insertRear(struct Deque* deque, int data){
	if(isFull(deque)){
		capdouble(deque);
	}
	deque->rear++;
	deque->array[deque->rear] = data;
	deque->size++;
}
//! This is to delete an element from front and also move elements by one position.
void deleteFront(struct Deque* deque){
    
    if(deque->rear == -1)
	{
		printf("No elements in the array");
	}
    int removeval = deque->array[0];
    memmove(&(deque->array[0]), &(deque->array[1]), deque->size * sizeof(int));
    deque->rear--;
    deque->size--;

  if(isHalf(deque)){
       caphalf(deque);
    }
}
//! This is to delete an element from rear.
void deleteRear(struct Deque* deque){


	if(deque->rear == -1)
	{
		printf("No elements in the array");
	}
	int removeval = deque->array[deque->rear];
	deque->rear--;
	deque->size--;

  if(isHalf(deque)){
       caphalf(deque);
    }

}
//! This is to print capacity of deque.
void printcap(struct Deque* deque){
//	printf("The current capacity of the deque is %d \n" , deque->capacity);
	printf("The current capacity (in bytes) of the deque is %d \n" , (deque->capacity)*4);
}
//! This is to print size of deque.
void printsize(struct Deque* deque){
	printf("The current size of the deque is %d \n", deque->size);
}

//! This is to print the deque.
void printDeque(struct Deque* deque)
{
	if(deque->rear != -1)
	{
	
		int current = 0;
		while(current <= deque->rear)
		{
			printf("%d ", deque->array[current]);
			current++;
		}
		printf("\n");
		
	}
	else
	{
		printf("Deque is empty \n");

	}
}
//! This is the main function implementing some of the functions made.
int main(void){
	printf("Firstly we make a deque of size 4 \n");
    struct Deque* deque = makedeque(4);

    printf("Now we insert an integer of value 3 in the deque from front \n");
    insertFront(deque, 3);

  printf("Now we insert an integer of value 4 in the deque from rear \n");
    insertRear(deque, 4);
   
printf("Now we insert an integer of value 3 in the deque from rear \n");
   insertRear(deque, 3);
    
  printf("Now we insert an integer of value 4 in the deque from front \n");
    insertFront(deque, 4);

printf("Now we insert an integer of value 5 in the deque from front \n");
    insertFront(deque, 5);

    printf("Now we print the deque \n");
   printDeque(deque);

   printf("Now we delete an element from rear of the deque \n");
    deleteRear(deque);

    printf("Now again we print the deque \n");
    printDeque(deque);
    insertFront(deque, 9);
    printf("Now we print the size of the deque \n");
   printsize(deque);

   printf("Now we print the capacity(bytes) of the deque \n");
   printcap(deque);



	return 0;
}