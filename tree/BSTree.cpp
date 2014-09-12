#include<stdio.h>
#include<stdlib.h>
#define MAX 100
typedef struct BiTNode{

  int data;
  int visit;
  struct BiTNode *left;
  struct BiTNode *right;
}BiTNode,*BTree;

BiTNode * createNode(int d)
{
  BiTNode *p= (BiTNode *)malloc(sizeof(BiTNode));
  if(p)
  {
      p->data=d; //fill the data feild
      p->visit=0; // fill the visit feild
      p->left=NULL;
      p->right=NULL;
      printf("create a node %d\n",d);
      return p;
  }else{
  printf("Allocation Memorry Failed!");
  return NULL;
  }
}
void createSortedTree(BTree *T)
{
  int a;
  scanf("%d",&a);
  while(a!=-1)
  {
     if(*T==NULL)
     {
       *T=createNode(a);
     }else{

        BiTNode *p=*T;
        BiTNode *pre=p;
        while(p!=NULL && p->data!=a) // find the proper position for the new node.
        {
            pre=p;
            if(p->data>a)
              p=p->left;
            else
              p=p->right;
        }
        if(pre->data>a)
          pre->left=createNode(a);  // add a left leaf node
        else if(pre->data<a)
          pre->right=createNode(a);// add a right leaf node
        else{
         printf("Node repeat.%d\n",a);// the node is already in the tree
        }
     }
     scanf("%d",&a);
  }
}

void inOrderTraverse(BTree T)
{
    BiTNode * arr[MAX]={NULL};
    BiTNode *p=T;
    int end=0;
    while(p!=NULL || end!=0)
    {
         while(p!=NULL)
         {
             arr[end++]=p;
             p=p->left;
         }
         if(end!=0)
         {
            p=arr[--end];
            printf("%d ",p->data);
            p=p->right;

         }

    }
}
/*
 * 1) traverse the left branch of T until NULL
 * 2) get the top node in the stack, and check the visit feild,
 *    if visit=0,push it into stack again,and the current node switch to p=p->right repeat 1)
 *    else that is visit=1   visit the node and set p=NULL(get another node in the stack)
 * 3) repeat until the stack is empty
 */
void postOrderTraverse(BTree T)
{
BiTNode * arr[MAX]={NULL};
int rear=0;
BiTNode *p=T;
while(p!=NULL || rear!=0)
{
    while(p!=NULL)
    {
        arr[rear++]=p;
        p=p->left;
    }
    if(rear!=0)
    {
        p=arr[--rear];
        if(p->visit==0) // if the node is the first time at the top,
        {                   //we should push it to the stack again
        p->visit=1;
        arr[rear++]=p;
        p=p->right;
        }else{
        printf("%d ",p->data);
        p=NULL;
        }
    }
}

}
void levelTraverse(BTree T)
{
  BiTNode * arr[MAX]={NULL};// use the arr as the queue to cach the nodes
  int front=0,rear=0;
  if(T!=NULL)
     arr[rear++]=T;//initate the queue
  while(front!=rear)
  {
     BiTNode *p=arr[front++];//get the top element
     printf("%d ",p->data);
     if(p->left!=NULL)
       arr[rear++]=p->left;  //push to the queue
     if(p->right!=NULL)
       arr[rear++]=p->right;  //push to the queue
  }
}
/*
 * In the post order, only the left and right are NULL  or  the left and the right has visited
 * can the procedure visits the node, else first the right then push the left
 */
void postOrderTraverse2(BTree T)
{
    BiTNode * arr[MAX]={NULL}; // store the nodes as stack
    BiTNode *p,*pre=NULL;  // p is the current node and pre is the previous accessed node
    int rear=0;
    arr[rear++]=T;  // push the root into the stack
    while(rear!=0)
    {
      p=arr[rear-1];
      if((p->left==NULL && p->right==NULL)||(pre!=NULL &&(pre==p->left||pre==p->right))) // if left and right is NULL
      {                                                                                     //or the left and the right has accessed,
          printf("%d ",p->data);                                                            //then visit the node
          pre=p;
          rear--; // pop the stack

      }else{  // first push the right then the left, to make sure the left is visited before the right
        if(p->right!=NULL)
          arr[rear++]=p->right;
        if(p->left!=NULL)
          arr[rear++]=p->left;

      }
    }
}
/*
 *Change the binary search tree to a double link without create one node.
 */
BiTNode * tree2link(BTree T)
{
    BiTNode * arr[MAX] ={NULL};
    int rear=0,first=1;
    BiTNode *p=T,*head=NULL,*tail=NULL,*tmp=NULL;
    while(p!=NULL || rear!=0)
    {
        while(p!=NULL)
        {
            arr[rear++]=p;
            p=p->left;
        }
        if(rear!=0)
        {
         p=arr[--rear];
         if(!first) // if the node is not the head , then add it to the tail
         {
         tmp = p;
         p=p->right;
         tail->left=tmp;
         tmp->right=tail;
         tail=tmp;
         tail->left=NULL;
         }else{     //if the node is the first visited in inordertraverse, make it a head
          first=0;
          head=p;
          tail=head;
          tail->left=NULL;
          tail->right=NULL;
          p=p->right;
         }

        }
    }
    return head;
}
void linkTraverse(BiTNode *head)
{
  BiTNode *p=head;
  while(p!=NULL)
  {
      printf("%d ",p->data);
      p=p->left;
  }
}
int main()
{
   printf("Please input the values of nodes seperated by space with -1 denotes termination\n");
   BTree root=(BTree)malloc(sizeof(BiTNode));
   root->left=NULL;
   createSortedTree(&(root->left));
   printf("create done! print\n");
   printf("in order sequence:\n");
   inOrderTraverse(root->left);
   printf("\npost order sequence(1):\n");
   postOrderTraverse(root->left);
   printf("\npost order sequence(2):\n");
   postOrderTraverse2(root->left);
   printf("\n The level sequenece is:\n");
   levelTraverse(root->left);
   printf("\nlink view:\n");
   linkTraverse(tree2link(root->left));
}
