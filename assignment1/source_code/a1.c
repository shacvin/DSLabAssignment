#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h> 

//! This is the node and it has various properties.
struct Node{
	struct Node* next;
	struct Node* prev;
	struct Node* head;
	int rollNo;
	long long int phoneNo;
	char name[50];
	char dob[15];
	char address[100];
	bool isEmpty;
};

//! This is the queue for unused roll number.
struct Unused_Roll{
	int roll_queue[13];
    int front;
    int rear;
    bool isEmpty;
    int size;
};

//! These are some globally declared variables.
struct Node* List;
struct Unused_Roll* queue;
FILE* Studentdata; 
int currentRoll;

//! This is the method to get the required node using roll number parameter.
struct Node* get(int roll_no){
	if(List->isEmpty){
		return 0;
	}

	else{
				struct Node *current=List->head->next;
		while(current != List->head)
		{
			if (current->rollNo == roll_no)
			{
				break;
			}
			current=current->next;
		}
		if(current->rollNo == roll_no)
		{
			return current;
		}
		else
		{
			return 0;
		}
	}
}

//! This is to print all of the contents of single node using roll number as a parameter.
 void print_oneNode(int roll_No){
 	struct Node* current = get(roll_No);
 	printf("Student Roll No. : %d\n", current->rollNo);
 	printf("Student Name : %s\n", current->name);
 	printf("Student DOB : %s\n", current->dob);
 	printf("Student Address : %s\n", current->address);
 	printf("Student Phone number : %lld\n", current->phoneNo);
 }
//! This is to print entire list with each node containing every properties.
 void print_List(){
 	if(List->isEmpty){
 		printf("The list is empty");
 	}

 	else{
 		struct Node* current = List->head->next;
 		while(current != List->head){
 			print_oneNode(current->rollNo);
 			current = current->next;
 		}
 	}
 }

//! This is to insert a new node and data to it using the input file given in the quetion. It uses fscanf function.
void insert(){
  struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
  if(queue->isEmpty){
  	newNode->rollNo = currentRoll;
  	currentRoll++;
  }
  else{
  	newNode->rollNo = queue->roll_queue[queue->front];
  	queue->roll_queue[queue->front] = -1;
  	queue->front = (queue->front+1)%13;
  	if(queue->front > queue->rear)
		{
			queue->isEmpty=true;
			queue->front = 0;
			queue->rear = -1;
		}
  }

  int serialNo;
  fscanf(Studentdata, "%d:%[^:]:%[^:]:%[^:]:%lld\n", &serialNo, newNode->name, newNode->dob, newNode->address, &(newNode->phoneNo));

  	if(List->isEmpty)
	{
		List->isEmpty=false;
	}

	struct Node* current=List->head->next;
	while(newNode->rollNo > current->rollNo && current->rollNo != -1)
	{
		current=current->next;
	}
	current=current->prev;
	newNode->next=current->next;
	current->next=newNode;
	newNode->prev=current;
	(newNode->next)->prev=newNode;
}


//! This is to delete a node and move the deleted node's roll number to the unused roll number queue.
void delete(int roll_no){

	struct Node* to_delete = get(roll_no);

	if(List->isEmpty){
		
		puts("No data to delete");
	}

	else if(roll_no > 113){
		
		puts("No such data found to be deleted");
	}

    else{
    	(to_delete->next)->prev = to_delete->prev;
    	(to_delete->prev)->next = to_delete->next;
    	free(to_delete);
        if(queue->rear == -1){
        	 queue->rear++;
        	queue->roll_queue[queue->rear] = roll_no;
        	queue->isEmpty = false;
        }
        else {
        	queue->rear = (queue->rear+1)%13;
        queue->roll_queue[queue->rear] = roll_no;	
        }
    	
    }
    
}

//! This is menu for modify function. It consists of several properties which can be modified like name, address, etc.
void menu_one()
{
	puts("\t1.Modify Name");
	puts("\t2.Modify Address");
	puts("\t3.Modify DOB");
	puts("\t4.Modify Phone Number");
}

//! This is the modify function. It uses switch cases to modify different properties as specified by the user. It uses scanf, memset and fgets functions.
void modify(int roll_no){
	struct Node* modify = get(roll_no);

    if(List->isEmpty){
		puts("The list is empty");
	}
 
    else if(modify == 0){
    	puts("There is no such node to modify");
    }

    else{
    	menu_one();

    	int choice_No;
    	puts("Enter your choice_No");
        scanf("%d", &choice_No);
        getchar();

        switch(choice_No){
        	case 1:
        	puts("Enter new name");
        	memset(modify->name, 0, 50);
        	fgets(modify->name, 49, stdin);
        	*(strchr(modify->name,'\n'))='\0';
        	break;

        	case 2:
        	puts("Enter new Address");
        	memset(modify->address, 0, 100);
        	fgets(modify->address, 99, stdin);
        	*(strchr(modify->address,'\n'))='\0';
        	break;

        	case 3:
        	puts("Enter new DOB");
        	memset(modify->dob, 0, 15);
        	fgets(modify->dob, 14, stdin);
        	*(strchr(modify->dob,'\n'))='\0';
        	break;

        	case 4:
        	puts("Enter new Phone number");
        	scanf("%lld", &(modify->phoneNo));
        	getchar();

        	default :
        	puts("Enter a valid choice");
        }

        putchar('\n');

    }
}

//! This is the menu for search function.
void menu_two()
{
	puts("\t1.Search by Name");
	puts("\t2.Search by Address");
	puts("\t3.Search by DOB");
	puts("\t4.Search by Phone Number");
}

//! This is the search function. It uses string comparison function from the string.h library to search for a given property in the list and prints the particular node.
void search(){
   if(List->isEmpty){
   	puts("There is no data to search");
   }

   else{
   	menu_two();
   	int choice;
   	puts("Enter the search choice");
   	scanf("%d", &choice);
   	getchar();
  //  printf("dskfhkushkh");
    struct Node* current = List->head->next;
    int count = 0;
    char search_array[100];
    long long int Phone_no;
    //printf("swtopekp");
   	switch(choice){
   		case 1:
   		//char search_Name[50];
   		puts("Enter the name to be searched");
   		fgets(search_array, 99, stdin);
   		*(strchr(search_array, '\n')) = '\0';

   		//struct Node* current = List->head->next;
   		//int count = 0;
      //printf("%s\n", search_array);
   		while(current != List->head){
        //print_oneNode(current->rollNo);
           if((strcmp(current->name, search_array)) == 0)
        //for(int i=0;i<)
        {
            print_oneNode(current->rollNo);
          	count++;
          
          	
          }
          current = current->next;
   		}
   		if(count==0){
   		puts("NO such nodes");
}
   	
   		break;

   		case 2:
   		   		//char search_Address[100];
   		puts("Enter the address to be searched");
   		fgets(search_array, 99, stdin);
   		*(strchr(search_array, '\n')) = '\0';

   		//struct Node* current = List->head->next;
   		//int count = 0;
   		while(current != List->head){
          if((strcmp(current->address, search_array)) == 0){
          	count++;
            print_oneNode(current->rollNo);
          	

          }
          current = current->next;
   		}
        if(count==0){
        	puts("Enter a valid address to search");
        }
   	
   		break;
        
        case 3:
           		//char search_DOB[15];
   		puts("Enter the date of birth to be searched(in dd monthname(first 3 letters) yy)");
   		fgets(search_array, 99, stdin);
   		*(strchr(search_array, '\n')) = '\0';

   		//struct Node* current = List->head->next;
   		//int count = 0;
   		while(current != List->head){
          if((strcmp(current->dob, search_array)) == 0){
          	count++;
          	print_oneNode(current->rollNo);
          }
          current = current->next;
   		}
   		if(count==0){
   			puts("Enter a valid date of birth to search");
   		}

   	
   		break;

   		   		case 4:
   		   		//long long int Phone_no;
   		puts("Enter the phone number to be searched");
   		scanf("%lld", &(Phone_no));
   		getchar();

   		//struct Node* current = List->head->next;
   		//int count = 0;
   		while(current != List->head){
          if((current->phoneNo) == Phone_no){
          	count++;
            print_oneNode(current->rollNo);
          	//print statement
          }
          current = current->next;
   		}
   		if(count==0){
   			puts("Enter a valid phone number to search");
   		}

   	
   		break;

        default:
        puts("Enter a valid choice");
    	}
   }
}
//! swap function - to swap two nodes.

void swap(struct Node* p1, struct Node* p2){
	(p2->next)->prev=p1;
    (p1->prev)->next=p2;
	p1->next=p2->next;
	p2->prev=p1->prev;
	p2->next=p1;
	p1->prev=p2;
}

//! This is the bubble sort function to sort the list according to the name.
 
 void sort(){
 	if(List->isEmpty){
 		puts("List is empty, nothing to be sorted!");
 	}

 	else{
 		int swapped;
 		    do
    { 
        swapped = 0; 
        struct Node* ptr1 = List->head->next; 
  
        while (ptr1->next != List->head) 
        { 
            if (strcmp(ptr1->name, (ptr1->next)->name) > 0) 
            {  
                swap(ptr1, ptr1->next); 
                swapped = 1; 
            } 
            ptr1 = ptr1->next; 
        } 
        
    } 
    while (swapped); 
 	}
 }
 

//! This is the main function.
 int main(void){
 	Studentdata = fopen("StudentData.csv", "r");
 	fscanf(Studentdata,"S.No.:Name:D.O.B.:Address:Phone No\n");

 	currentRoll = 101;

 		List=(struct Node*)malloc(sizeof(struct Node));
	List->isEmpty=true;
	List->head=(struct Node*)malloc(sizeof(struct Node));
	List->head->rollNo=-1;
	List->head->next=List->head->prev=List->head;

	queue=(struct Unused_Roll*)malloc(sizeof(struct Unused_Roll));
	memset(queue->roll_queue,0,13*sizeof(int));
	queue->isEmpty=true;
	queue->front=0;
	queue->rear=-1;

	delete(108);
	insert();
	insert();
	insert();
	insert();
	delete(102);
	delete(101);
	insert();
	insert();
	insert();
	print_List();
	sort();
	print_List();
	modify(103);
	print_List();


	return 0;
 }




