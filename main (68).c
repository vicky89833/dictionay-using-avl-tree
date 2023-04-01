#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct node {
        char string[1000];
        int index;
        int height;
        struct node *left,*right;
};


int height(struct node *N) {
  if (N == NULL)
    return 0;
  return N->height;
}
char *stringptr(struct node* temp){
        if(temp==NULL){
                return "";
                
        }
        return temp->string;
}

int max(int a, int b) {
  return (a > b) ? a : b;
}

struct node *rightRotate(struct node *y) {
  struct node *x = y->left;
  struct node *T2 = x->right;

  x->right = y;
  y->left = T2;

  y->height = max(height(y->left), height(y->right)) + 1;
  x->height = max(height(x->left), height(x->right)) + 1;

  return x;
}

struct node *leftRotate(struct node *x) {
  struct node *y = x->right;
  struct node *T2 = y->left;

  y->left = x;
  x->right = T2;

  x->height = max(height(x->left), height(x->right)) + 1;
  y->height = max(height(y->left), height(y->right)) + 1;

  return y;
}
int getBalance(struct node *N) {
  if (N == NULL)
    return 0;
  return height(N->left) - height(N->right);
}

struct node *insertNode(struct node *node, struct node *temp) {
  // Find the correct position to insertNode the node and insertNode it
  if (node == NULL)
    {return temp;}
    
  int result = strcmp(temp->string, node->string);
  if (result<0)
   { node->left = insertNode(node->left,temp);}
  else if (result>0)
    {node->right = insertNode(node->right, temp);}
  else
    {return node;}

  // Update the balance factor of each node and
  // Balance the tree
  node->height = 1 + max(height(node->left),
               height(node->right));
               
               
  int balance = getBalance(node);
  int result1=strcmp(temp->string,stringptr(node->left));
  if (balance > 1 && result1 < 0)
    {return rightRotate(node);}
    
  int result2=strcmp(temp->string,stringptr(node->right));
  if (balance < -1 && result1 > 0)
    {return leftRotate(node);}

  if (balance > 1 && result1 > 0) {
    node->left = leftRotate(node->left);
    return rightRotate(node);
  }

  if (balance < -1 && result1 < 0) {
    node->right = rightRotate(node->right);
    return leftRotate(node);
  }

  return node;
}

void printindex(struct node *root,char *string){
        if(root==NULL){
                printf("-1");
                return;
        }
        int result=strcmp(string,root->string);
          if(result==0){
                  printf("%d",root->index);
                  return;
          }
          
        else{
          
          if(result<0){
                return printindex(root->left,string);  
          }
          if(result>0){
                return printindex(root->right,string);  
          }
 
        } 
}
void inordertraverse(struct node *root){
        if(root==NULL){
                return;
        }
        inordertraverse(root->left);
        printf("%s --%d",root->string,root->index);
        inordertraverse(root->right);
}

int main() {
  struct node *root=NULL;
  int n;
  scanf("%d",&n);
  for(int i=1;i<=n;i++){
        struct node *temp=malloc(sizeof(struct node));
        scanf("%s",temp->string);
        temp->index= i ;
        temp->left=NULL;
        temp->right=NULL;
        temp->height=1;
        root=insertNode(root,temp);
  }
//   inordertraverse(root);
  char string[1000];
  scanf("%s", string);
  printindex(root,string);

  return 0;
}

