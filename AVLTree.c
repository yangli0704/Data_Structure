#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <math.h>


typedef struct AVLTreeNode {
	int key; //key of this item
	int  value;  //value (int) of this item 
	int height; //height of the subtree rooted at this node
	struct AVLTreeNode *left; //pointer to left child
	struct AVLTreeNode *right; //pointer to right child
} AVLTreeNode;

typedef struct AVLTree{
	int  size;      // count of items in avl tree
	AVLTreeNode *root; // root
} AVLTree;


AVLTreeNode *newAVLTreeNode(int k, int v )
{
	AVLTreeNode *newNode;
	newNode = malloc(sizeof(AVLTreeNode));
	assert(newNode != NULL);
	newNode->key = k;
	newNode->value = v;
	newNode->height = 0; // height of this new node is set to 0
	newNode->left = NULL; // this node has no child
	newNode->right = NULL;
	newNode->parent = NULL; // no parent
	return newNode;
}

// create a new empty avl tree
AVLTree *newAVLTree()
{
	AVLTree *T;
	T = malloc(sizeof (AVLTree));
	assert (T != NULL);
	T->size = 0;
	T->root = NULL;
	return T;
}

typedef struct AVLTreeNodeInsert {
	int duplicateFlag; // check if a node is duplicateds
	struct AVLTreeNode *node; //pointer to parent
} AVLTreeNodeInsert;

AVLTreeNodeInsert *newAVLTreeNodeInsert(int k,int v)
{
	AVLTreeNodeInsert *newNode;
	newNode = malloc(sizeof(AVLTreeNodeInsert));
	assert(newNode != NULL);
	newNode->node = newAVLTreeNode(k,v);
	newNode->duplicateFlag = 0;
	return newNode;
}

AVLTreeNodeInsert *createAVLTreeNodeInsert(AVLTreeNode* node,int duplicateFlag)
{
	AVLTreeNodeInsert *newNode;
	newNode = malloc(sizeof(AVLTreeNodeInsert));
	assert(newNode != NULL);
	newNode->node = node;
	newNode->duplicateFlag = duplicateFlag;
	return newNode;
}


int max(int a, int b){
	return((a > b)?a:b);
} // function to calculate max value

int setHeight(AVLTreeNode* root) {
	int lh,rh;
	if (root->left==NULL) {
		lh = 0;
	} else {
		lh = root->left->height;
	};

	if (root->right==NULL) {
		rh = 0;
	} else {
		rh = root->right->height;
	};

	return 1+max(lh,rh);
}

int GetBalanceFactor(AVLTreeNode* root) {
	int lh,rh;
    if(root == NULL)
        return 0;

    if (root->left==NULL) {
		lh = 0;
	} else {
		lh = root->left->height;
	};

	if (root->right==NULL) {
		rh = 0;
	} else {
		rh = root->right->height;
	};

	return lh - rh;
} // function to get balance factor



//1.right rotation

AVLTreeNode* RightRotate(AVLTreeNode* root) {
    AVLTreeNode* left = root->left;
    
    root->left = left->right; 
    left->right = root; 

	root->height = setHeight(root);
    left->height = setHeight(left);
    //root->height = setHeight(root);
    
    return left;
}

//2.left rotation
AVLTreeNode* LeftRotate(AVLTreeNode* root) {
    AVLTreeNode* right = root->right;
    
    root->right = right->left; 
    right->left = root; 

    right->height = setHeight(right);
    root->height = setHeight(root);
    
    return right;
}

AVLTreeNode* TreeBalance(AVLTreeNode* root) {
	int bf = GetBalanceFactor(root);
	if(bf > 1 && GetBalanceFactor(root->left) >=0){  // LL
		return RightRotate(root);}
    else if(bf > 1 && GetBalanceFactor(root->left) < 0) { //LR
        root->left = LeftRotate(root->left);
        return RightRotate(root);
    }
	else if(bf < -1 && GetBalanceFactor(root->right) <= 0){ // RR
        return LeftRotate(root);}
    else if(bf < -1 && GetBalanceFactor(root->right) > 0) { // RL
        root->right = RightRotate(root->right);
        return LeftRotate(root);
    } else { // No need to rotate
        return root;
    }
}

// function to insert node recursively
AVLTreeNodeInsert *InsertNodeRecursive(AVLTreeNode* root,int k,int v)
{
	int duplicateFlag;
	if (root == NULL) {
			AVLTreeNodeInsert* newNodeInsert = newAVLTreeNodeInsert(k,v);
			newNodeInsert->node->height = setHeight(newNodeInsert->node);
			newNodeInsert->duplicateFlag = 1;
			return(newNodeInsert);
		}
	else {
		if (k<root->key||(k==root->key&&v<root->value)){
			AVLTreeNodeInsert* nodeInsert = InsertNodeRecursive(root->left,k,v);
			root->left = nodeInsert->node;
			duplicateFlag = nodeInsert->duplicateFlag;
		}
		else if(k>root->key||(k==root->key&&v>root->value)){
			AVLTreeNodeInsert* nodeInsert = InsertNodeRecursive(root->right,k,v);
			root->right = nodeInsert->node;
			duplicateFlag = nodeInsert->duplicateFlag;
		}
		else {
			duplicateFlag = 0;
		};
		//Update the height for each node
		root = TreeBalance(root);
		root->height = setHeight(root);

		return createAVLTreeNodeInsert(root,duplicateFlag);
	}
}


void PrintAVLTreeRecusive(AVLTreeNode* root) {
	if (root==NULL){
		return;
	};
	PrintAVLTreeRecusive(root->left);
	printf("(key: %i, value: %i)\n",root->key,root->value);
	PrintAVLTreeRecusive(root->right);

}


AVLTreeNode * MinValueNode(AVLTreeNode* node)
{
    AVLTreeNode* current = node;  
    /* traversing down to find the most left node */
    while (current->left != NULL)
        current = current->left;
  
    return current;
}

AVLTreeNode *DeleteNodeRecursive(AVLTreeNode* root,int k,int v,AVLTree *T) {
	if(root==NULL){
		return NULL;
	}
	else {
		if (k<root->key||(k==root->key&&v<root->value)){
			root->left = DeleteNodeRecursive(root->left,k,v,T);
		}
		else if(k>root->key||(k==root->key&&v>root->value)){
			root->right = DeleteNodeRecursive(root->right,k,v,T);
		}
		else {
			if(root->left!=NULL&&root->right!=NULL){
				AVLTreeNode* node = MinValueNode(root->right);
				root->key = node->key;
				root->value = node->value;
				root->right = DeleteNodeRecursive(root->right,node->key,node->value,T);
			}
			else if (root->left !=NULL&&root->right==NULL){
				root = root->left;
				T->size--;
			}
			else if(root->right !=NULL&&root->left==NULL) {
				root = root->right;
				T->size--;
			}
			else {
				free(root);
				root = NULL;
				T->size--;
				//AVLTreeNode* root;
			}
		};
		root = TreeBalance(root);
		if(root !=NULL) {
			root->height = setHeight(root);
		};
		return root;
	}
}


int InsertNode(AVLTree *T, int k, int v)
{
	//put your code here
	AVLTreeNodeInsert* node;
	//int flag;
	if (T->root == NULL) {
		T->root = newAVLTreeNode(k,v);
		T->size++;
		return 0;
	}
	else{
		node = InsertNodeRecursive(T->root,k,v);
		T->root =node->node;
		if(node->duplicateFlag==1){
			T->size++;
		};
		return node->duplicateFlag;
	}
}

AVLTree *CreateAVLTree(const char *filename)
{
	int k,v;
	AVLTree* tree;
	char temp;
	tree = newAVLTree();
	FILE* file = fopen(filename, "r");
	if(file == NULL) {
		printf("Error! Can't Opening File");
		xit(1) ;                                   // checking error
	}
	while (fscanf (file, " (%d , %d) ", &k, &v) == 2)  // check for number
	{
		InsertNode(tree, k, v); //insert into AVL Tree
	}
	fclose(file);
	}

	return tree;
}

int DeleteNode(AVLTree *T, int k, int v)
{
 	// put your code here
	AVLTreeNode* root;
	int size = T->size;
	if (T->root == NULL) {
		return 0;
	}
	else{
		root = DeleteNodeRecursive(T->root,k,v,T);
		T->root =root;
		if(size == T->size) {
			return 0;
		}
		else {
			return 1;
		}
	}
}

AVLTreeNode *Search(AVLTree *T, int k, int v)
{
	// put your code here
	AVLTreeNode* node=T->root;
	while(node != NULL){
		if (k<node->key||(k==node->key&&v<node->value)){
			node = node->left;
		}
		else if(k>node->key||(k==node->key&&v>node->value)){
			node = node->right;
		}
		else{
			return node;
		}
	};
	return node;
}


void InoderTraversal(AVLTree *T)
{
 // put your code here
 if(T->root==NULL){
	 printf("Empty Tree\n");
 }
 else{
	 PrintAVLTreeRecusive(T->root);
 }
}


int main() //sample code for
{ int i,j;
 AVLTree *tree1, *tree2, *tree3;
 AVLTreeNode *node1;
 
 tree1=CreateAVLTree("file1.txt");
 InoderTraversal(tree1);

 tree2=newAVLTree();
 j=InsertNode(tree2, 10, 10);
 for (i=0; i<15; i++)
  {
   j=InsertNode(tree2, i, i);
   if (j==0) printf("(%d, %d) already exists\n", i, i);
  }
  InoderTraversal(tree2);
  node1=Search(tree2,20,20);
  if (node1!=NULL)
    printf("key= %d value= %d\n",node1->key,node1->value);
  else 
    printf("Key 20 does not exist\n");
  
  for (i=17; i>0; i--)
  {
    j=DeleteNode(tree2, i, i);
	if (j==0) 
	  printf("Key %d does not exist\n",i);  
    PrintAVLTree(tree2);
  };
 
 tree3=newAVLTree();
 j=InsertNode(tree3, 6, 25);
 j=InsertNode(tree3, 6, 10);
 j=InsertNode(tree3, 6, 12);
 j=InsertNode(tree3, 6, 20);
 j=InsertNode(tree3, 9, 25);
 j=InsertNode(tree3, 10, 25);
 PrintAVLTree(tree3);
}