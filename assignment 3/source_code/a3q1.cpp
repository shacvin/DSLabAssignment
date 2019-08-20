
#include <stdio.h> 
#include <stdlib.h> 
#include <iostream>
using namespace std;

#define BLACK false
#define RED true 
  
struct Node 
{ 
    int data; 
    bool color; 
    Node *left, *right, *parent; 
  
    // Constructor 
    Node(int data) 
    { 
       this->data = data; 
       left = right = parent = NULL; 
       this->color = RED; 
    } 
}; 
  
// Class to represent Red-Black Tree 
class RBTree 
{ 
public: 
    Node *root; 

    void rotateLeft(Node *&, Node *&); 
    void rotateRight(Node *&, Node *&); 
    void fixViolation(Node *&, Node *&); 
    // Constructor 
    RBTree() { root = NULL; } 
    void insert(const int &n); 
    void inorder(); 
    void RBprint1();
    //void levelOrder(); 
}; 

  class BSTNode 
{ 
public:
    int key; 
     BSTNode *left, *right;
     int height; 
}; 


void inorderHelper(Node *root) ;
void insert();
int getHeightBST(BSTNode* node);
int getHeightRB(Node* node);
Node* BSTInsert(Node* root, Node *pt);
BSTNode* insertBST(BSTNode* node, int key) ;
void inorder(BSTNode *root) ;
BSTNode* createAVL(int a[], int first, int last);
void BSTprintPaths(BSTNode* node) ;
void BSTprintPathsRecur(BSTNode* node, int path[], int pathLen);
void BSTprintArray(int ints[], int len) ;
void BSTAVLTreepath(BSTNode* node);
void BTSAVLprintindent(BSTNode* node,int indentNo);
void RBprintPaths(Node* node);
void RBprintPathsRecur(Node* node, int path[], int pathLen);
void RBprintArray(int ints[], int len);
void RBTreepath(Node* node);
void RBprintindent(Node* node,int indentNo);




  
  RBTree* tree; 
  BSTNode *rootBST;
  BSTNode *rootAVL;


// A recursive function to do level order traversal 
void inorderHelper(Node *root) 
{ 
    if (root == NULL) 
        return; 
  
    inorderHelper(root->left); 
    cout<< root->data << "  "; 
    inorderHelper(root->right); 
} 
  
/* A utility function to insert a new node with given key 
   in BST */
void insert(){
	int data = 0;
	scanf("%d", &data);
	rootBST = insertBST(rootBST, data);
	tree->insert(data);

}
	int getHeightBST(BSTNode* node)
		{
			if (node ==  NULL)
			{
				return -1;
			}
			else
			{
				return max(getHeightBST(node->left),getHeightBST(node->right))+1;
			}
		}

			int getHeightRB(Node* node)
		{
			if (node ==  NULL)
			{
				return -1;
			}
			else
			{
				return max(getHeightRB(node->left),getHeightRB(node->right))+1;
			}
		}
Node* BSTInsert(Node* root, Node *pt) 
{ 
    /* If the tree is empty, return a new node */
    if (root == NULL) 
       return pt; 
  
    /* Otherwise, recur down the tree */
    if (pt->data < root->data) 
    { 
        root->left  = BSTInsert(root->left, pt); 
        root->left->parent = root; 
    } 
    else if (pt->data > root->data) 
    { 
        root->right = BSTInsert(root->right, pt); 
        root->right->parent = root; 
    } 
  
    /* return the (unchanged) node pointer */
    return root; 
} 
  
// Utility function to do level order traversal 
// void levelOrderHelper(Node *root) 
// { 
//     if (root == NULL) 
//         return; 
  
//     std::queue<Node *> q; 
//     q.push(root); 
  
//     while (!q.empty()) 
//     { 
//         Node *temp = q.front(); 
//         cout << temp->data << "  "; 
//         q.pop(); 
  
//         if (temp->left != NULL) 
//             q.push(temp->left); 
  
//         if (temp->right != NULL) 
//             q.push(temp->right); 
//     } 
// } 
  
void RBTree::rotateLeft(Node *&root, Node *&pt) 
{ 
    Node *pt_right = pt->right; 
  
    pt->right = pt_right->left; 
  
    if (pt->right != NULL) 
        pt->right->parent = pt; 
  
    pt_right->parent = pt->parent; 
  
    if (pt->parent == NULL) 
        root = pt_right; 
  
    else if (pt == pt->parent->left) 
        pt->parent->left = pt_right; 
  
    else
        pt->parent->right = pt_right; 
  
    pt_right->left = pt; 
    pt->parent = pt_right; 
} 
  
void RBTree::rotateRight(Node *&root, Node *&pt) 
{ 
    Node *pt_left = pt->left; 
  
    pt->left = pt_left->right; 
  
    if (pt->left != NULL) 
        pt->left->parent = pt; 
  
    pt_left->parent = pt->parent; 
  
    if (pt->parent == NULL) 
        root = pt_left; 
  
    else if (pt == pt->parent->left) 
        pt->parent->left = pt_left; 
  
    else
        pt->parent->right = pt_left; 
  
    pt_left->right = pt; 
    pt->parent = pt_left; 
} 
  
// This function fixes violations caused by BST insertion 
void RBTree::fixViolation(Node *&root, Node *&pt) 
{ 
    Node *parent_pt = NULL; 
    Node *grand_parent_pt = NULL; 
  
    while ((pt != root) && (pt->color != BLACK) && 
           (pt->parent->color == RED)) 
    { 
  
        parent_pt = pt->parent; 
        grand_parent_pt = pt->parent->parent; 
  
        /*  Case : A 
            Parent of pt is left child of Grand-parent of pt */
        if (parent_pt == grand_parent_pt->left) 
        { 
  
            Node *uncle_pt = grand_parent_pt->right; 
  
            /* Case : 1 
               The uncle of pt is also red 
               Only Recoloring required */
            if (uncle_pt != NULL && uncle_pt->color == RED) 
            { 
                grand_parent_pt->color = RED; 
                parent_pt->color = BLACK; 
                uncle_pt->color = BLACK; 
                pt = grand_parent_pt; 
            } 
  
            else
            { 
                /* Case : 2 
                   pt is right child of its parent 
                   Left-rotation required */
                if (pt == parent_pt->right) 
                { 
                    rotateLeft(root, parent_pt); 
                    pt = parent_pt; 
                    parent_pt = pt->parent; 
                } 
  
                /* Case : 3 
                   pt is left child of its parent 
                   Right-rotation required */
                rotateRight(root, grand_parent_pt); 
                swap(parent_pt->color, grand_parent_pt->color); 
                pt = parent_pt; 
            } 
        } 
  
        /* Case : B 
           Parent of pt is right child of Grand-parent of pt */
        else
        { 
            Node *uncle_pt = grand_parent_pt->left; 
  
            /*  Case : 1 
                The uncle of pt is also red 
                Only Recoloring required */
            if ((uncle_pt != NULL) && (uncle_pt->color == RED)) 
            { 
                grand_parent_pt->color = RED; 
                parent_pt->color = BLACK; 
                uncle_pt->color = BLACK; 
                pt = grand_parent_pt; 
            } 
            else
            { 
                /* Case : 2 
                   pt is left child of its parent 
                   Right-rotation required */
                if (pt == parent_pt->left) 
                { 
                    rotateRight(root, parent_pt); 
                    pt = parent_pt; 
                    parent_pt = pt->parent; 
                } 
  
                /* Case : 3 
                   pt is right child of its parent 
                   Left-rotation required */
                rotateLeft(root, grand_parent_pt); 
                swap(parent_pt->color, grand_parent_pt->color); 
                pt = parent_pt; 
            } 
        } 
    } 
  
    root->color = BLACK; 
} 
  
// Function to insert a new node with given data 
void RBTree::insert(const int &data) 
{ 
    Node *pt = new Node(data); 
  
    // Do a normal BST insert 
    root = BSTInsert(root, pt); 
  
    // fix Red Black Tree violations 
    fixViolation(root, pt); 
} 
  
// Function to do inorder and level order traversals 
void RBTree::inorder()     {  inorderHelper(root);} 
//void RBTree::levelOrder()  {  levelOrderHelper(root); } 

// A utility function to create a new BST node 
BSTNode *newNode(int item) 
{ 
	BSTNode *temp = new BSTNode(); 
	temp->key = item; 
	temp->left = temp->right = NULL; 
	temp->height = 1;
	return temp; 
} 
// int height(BSTNode *N)  
// {  
//     if (N == NULL)  
//         return 0;  
//     return N->height;  
// }
// int max(int a, int b)  
// {  
//     return (a > b)? a : b;  
// }  
 int size = 0; 


// A utility function to do inorder traversal of BST 


/* A utility function to insert a new node with given key in BST */
BSTNode* insertBST(BSTNode* node, int key) 
{ 
	/* If the tree is empty, return a new node */
    size++;
	if (node == NULL) return newNode(key); 

	/* Otherwise, recur down the tree */
	if (key < node->key) 
		node->left = insertBST(node->left, key); 
	    
	if (key > node->key) 
		node->right = insertBST(node->right, key);

	/* return the (unchanged) node pointer */
	return node; 
} 

int BSTarray[2000];
int x = 0; 



void createBSTarray(BSTNode *node) 
{ 
    
    if (node != NULL) 
    { 
        createBSTarray(node->left); 
        BSTarray[x++] = node->key;
        createBSTarray(node->right); 
    } 
}

void inorder(BSTNode *node) 
{ 
	
	if (node != NULL) 
	{ 
		inorder(node->left); 
		printf("%d ", node->key);
		//BSTarray[x++] = node->key;
		inorder(node->right); 
	} 
} 
//first and last are index of array
// int first = 0;
// int last = size-1;
BSTNode* createAVL(BSTNode* node,int a[], int first, int last){

      if(first>last) return NULL;
        
        node =  newNode(a[(first+last)/2]);
       node->left = createAVL(node->left,a, first, ((first+last)/2) - 1);
        node->right = createAVL(node->right,a, ((first+last)/2) + 1, last);
        return node;     
}

/*Given a binary tree, print out all of its root-to-leaf  
paths, one per line. Uses a recursive helper to do the work.*/
void BSTprintPaths(BSTNode* node)  
{  if (node == NULL)
    {
        return;
    }
    int path[1000];  
    BSTprintPathsRecur(node, path, 0);  
}  
  
/* Recursive helper function -- given a node,  
and an array containing the path from the root 
node up to but not including this node,  
print out all the root-leaf paths.*/
void BSTprintPathsRecur(BSTNode* node, int path[], int pathLen)  
{  
    if (node == NULL)  
        return;  
      
    /* append this node to the path array */
    path[pathLen] = node->key;  
    pathLen++;  
      
    /* it's a leaf, so print the path that led to here */
    if (node->left == NULL && node->right == NULL)  
    {  
        BSTprintArray(path, pathLen);  
    }  
    else
    {  
        /* otherwise try both subtrees */
        BSTprintPathsRecur(node->left, path, pathLen);  
        BSTprintPathsRecur(node->right, path, pathLen);  
    }  
}  
  
  
/* UTILITY FUNCTIONS */
/* Utility that prints out an array on a line. */
void BSTprintArray(int ints[], int len)  
{  
    int i;  
    for (i = 0; i < len; i++)  
     {  if(i==len-1){
        cout << ints[i] << " ";  
    }
    else{
    	cout << ints[i] << " -> ";
    } 
     
    }
    cout<<endl; 
}  

void BSTAVLTreepath(BSTNode* node)
{
    if(node == NULL)
    {
        return;
    }
        BSTprintPaths(node);
        BSTAVLTreepath(node -> left);
        BSTAVLTreepath(node -> right);

}

void BTSAVLprintindent(BSTNode* node,int indentNo)
        {
        	int weight = 0;
            if (node == NULL)
            {
                return;
            }
            else
            {
                for (int i = 0; i < indentNo; ++i)
                {
                    cout << "    ";
                }
                weight = getHeightBST(node->left)-getHeightBST(node->right);
                cout << node->key << " [" << weight << "]" << endl;
                BTSAVLprintindent(node->left,indentNo+1);
                BTSAVLprintindent(node->right,indentNo+1);
            }
        }
/*Given a binary tree, print out all of its root-to-leaf  
paths, one per line. Uses a recursive helper to do the work.*/
void RBprintPaths(Node* node)  
{  
    int path[1000];  
    RBprintPathsRecur(node, path, 0);  
}  
  
/* Recursive helper function -- given a node,  
and an array containing the path from the root 
node up to but not including this node,  
print out all the root-leaf paths.*/
void RBprintPathsRecur(Node* node, int path[], int pathLen)  
{  
    if (node == NULL)  
        return;  
      
    /* append this node to the path array */
    path[pathLen] = node->data;  
    pathLen++;  
      
    /* it's a leaf, so print the path that led to here */
    if (node->left == NULL && node->right == NULL)  
    {  
        RBprintArray(path, pathLen);  
    }  
    else
    {  
        /* otherwise try both subtrees */
        RBprintPathsRecur(node->left, path, pathLen);  
        RBprintPathsRecur(node->right, path, pathLen);  
    }  
}  
  
  
/* UTILITY FUNCTIONS */
/* Utility that prints out an array on a line. */
void RBprintArray(int ints[], int len)  
{  
    int i;  
    for (i = 0; i < len; i++)  
    {  
         if(i==len-1){
            cout << ints[i] << " ";  
        }
        else{
        	cout << ints[i] << " -> ";
        }
    }  
    cout<<endl;  
} 


void RBTree :: RBprint1()
{
	RBprintPaths(tree->root);
}

void RBTreepath(Node* node)
{
    if(node == NULL)
    {
        return;
    }
        //RBprint1();
    RBprintPaths(node);
        RBTreepath(node -> left);
        RBTreepath(node -> right);

}

void RBprintindent(Node* node,int indentNo)
        {
        	int weight = 0;
            if (node == NULL)
            {
                return;
            }
            else
            {
                for (int i = 0; i < indentNo; ++i)
                {
                    cout << "    ";
                }
                string s;
                if(node -> color)
                {
                    s = "BLACK";
                }
                else
                {
                    s = "RED";
                }
                weight = getHeightRB(node->left)-getHeightRB(node->right);
                cout << node->data << " [" << weight << "]" << " [" << s << "]" << endl;
                RBprintindent(node->left,indentNo+1);
                RBprintindent(node->right,indentNo+1);
            }
        }
int c = 1;
void menu(){
    int n = 0; 
    scanf("%d", &n);

switch(n){

    //int data = 0;

    case 1:
    //puts("insert a node in the BST and in the red-black tree\n");
    cout<<"Enter the data to be inserted"<<endl;
    //scanf("%d", &data);
    insert();
    // inorder(rootBST);
    // tree.inorder();
    break;

    case 2:
    createBSTarray(rootBST);
    rootAVL = createAVL(rootAVL,BSTarray, 0, x-1);
    break;

    case 3:

    inorder(rootBST);
    cout<<endl;
    inorder(rootAVL);
    cout<<endl;
    tree->inorder();
    cout<<endl;
    break;

    case 4:

    BSTAVLTreepath(rootBST);
    cout<<endl;
    BSTAVLTreepath(rootAVL);
    cout<<endl;
    RBTreepath(tree->root);
    cout<<endl;
    break;

    case 5:
    
    BTSAVLprintindent(rootBST, 0);
    cout<<endl;
    BTSAVLprintindent(rootAVL, 0);
    cout<<endl;
    RBprintindent(tree->root, 0);
    cout<<endl;
    break;

    case 6:
    c = 0;
    break;


    default:
    cout << "Enter a correct option" << endl;
    break;
}
}
void printmenu(){
	cout<<"Enter the choice as follows:"<<endl;
	cout<<"1. To insert a node in the BST and in the red-black tree\n2. To create AVL tree from the inorder traversal of the BST\n3. To print the inorder traversal of the BST/AVL/red-black tree\n4. To display all the paths in the BST/AVL tree/red-black tree \n5. To print the BST/AVL tree/red-black Tree in the terminal using level-wise indentation (print color for red-black tree) \n6. Exit"<<endl;
    menu();
}



// Driver Program to test above functions 
int main(void) 
{ 
    cout<<endl;
	// rootBST = new BSTNode();
	// rootAVL = new BSTNode();
    tree = new RBTree();
	do{
	printmenu();}
	while(c!=0);
	// int n = 0;
	// scanf("%d", &n);
	// menu();
	//struct node *rootBST = NULL; 

	// rootBST = insert(rootBST, 50); 
	// insert(rootBST, 30); 
	// insert(rootBST, 20); 
	// insert(rootBST, 40); 
	// insert(rootBST, 70); 
	// insert(rootBST, 60); 
	// insert(rootBST, 80); 

	// print inoder traversal of the BST 
	//inorder(rootBST); 

	return 0; 
} 
