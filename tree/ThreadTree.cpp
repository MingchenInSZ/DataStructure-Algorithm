#include<stdio.h>
#include<stdlib.h>
#define MAX 100

typedef enum{Thread,Link} pointer_type; // Thread : threading pointer , Link : child pointer
typedef struct BiTNode{

        int data;
        struct BiTNode * left_child;
        struct BiTNode * right_child;
        pointer_type left_tag,right_tag;

}BiTNode, *BTree;

BiTNode * createThrNode(int d)
{
    BiTNode * p=(BiTNode *)malloc(sizeof(BiTNode));
    if(p)
    {
     p->data=d;
     p->left_child=NULL;
     p->right_child=NULL;
     p->left_tag=Thread;
     p->right_tag=Thread;
     return p;
    }else{
    printf("Memmory Allocation Failed!\n");
    return NULL;
    }
}
void createThrTree(BTree *T)
{
   int data;
   scanf("%d",&data);
   while(data!=-1)
   {
       if(*T!=NULL)
        {
        BiTNode * p=*T;
        BiTNode *pre =p;
        while(p!=NULL && p->data!=data)// find the proper position
        {
            pre=p;
           if(p->data>data)
             p=p->left_child;
           else
             p=p->right_child;
        }
        if(data<pre->data)// add to left
        {
         pre->left_child=createThrNode(data);
         pre->left_tag=Link;
        }else if(data>pre->data) // add to right
        {
        pre->right_child=createThrNode(data);
        pre->right_tag=Link;
        }else if(p->data==data)// prompt repeat warning
        {
         printf("Node repeat!%d\n",data);
        }
        }else{
        *T = createThrNode(data); // create the root  node of the tree.
        }
        scanf("%d",&data);
   }
}
/*
 * displaying the detail information of the threading tree
 */
void displayContentOfTree(BTree T)
{
 BiTNode * arr[MAX]={NULL};
 int rear=0;
 BiTNode *p=T;
 while(p!=NULL || rear!=0)
 {
     while(p!=NULL)
     {
         arr[rear++]=p;
         p=p->left_child;
     }
     if(rear!=0)
     {
         p=arr[--rear];
         printf("Node:%d [left_tag:%d right_tag:%d ]\n",p->data,p->left_tag,p->right_tag);
         p=p->right_child;
     }
 }
}
BiTNode *pre=NULL;
void inOrderThreading(BiTNode *T)
{
 if(T)
 {
     inOrderThreading(T->left_child);
     if(T->left_child==NULL)
     {
      T->left_tag=Thread;
      T->left_child=pre;
     }
     if(pre!=NULL&&pre->right_child==NULL)
     {
         pre->right_child=T;
         pre->right_tag=Thread;
     }
     pre=T;
     inOrderThreading(T->right_child);
 }
}
void inOrderTraverseThr(BTree T)// in order traverse the threading tree
{
  BTree p=T;
  p=p->left_child;
  while(p!=T)
  {
      while(p->left_tag==Link)
      p=p->left_child;
      printf("%d ",p->data);
      while(p->right_tag==Thread&&p->right_child!=T)
      {
          p=p->right_child;
          printf("%d ",p->data);
      }
      p=p->right_child;
  }
}
void inOrderThreadingAddHead(BTree *head,BTree T)// add a head to the tree and threading
{
   *head=(BTree)malloc(sizeof(BiTNode));
   if(!*head)
   {
       printf("Memmory Allocation Failed!\n");
       exit(1);
   }
   (*head)->right_child=*head;
   (*head)->right_tag=Link;
   if(!T)//if T is NULL then head point itself
   {
     (*head)->left_child=*head;
     (*head)->left_tag=Link;
   }else{ //
     (*head)->left_child=T;
     (*head)->left_tag=Thread;
     inOrderThreading(T); // get the last node
     pre->right_child=*head;
     pre->right_tag=Thread;
     (*head)->right_child=pre;
   }
}
int main()
{
    printf("Create a thread tree.\n Please input the numbers seperated by space.\n");
    BTree root= (BTree)malloc(sizeof(BTree));
    root->left_child=NULL;
    createThrTree(&(root->left_child));
    displayContentOfTree(root->left_child);
    BTree *head;
    inOrderThreadingAddHead(head,root->left_child);
    inOrderTraverseThr(*head);
    return 0;
}
