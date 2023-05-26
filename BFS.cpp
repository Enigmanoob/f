#include<iostream>
#include<stdlib.h>
#include<queue>
#include <omp.h>

using namespace std;
class node
{
   public:
    node *left, *right;
    int data;

};    

class Breadthfs
{
 
 public:
 
 node *insert(node *, int);
 void bfs(node *);
 
};

node *insert(node* root, int value)
{
    if (!root) {
         root=new node;
		 root->left=NULL;
		 root->right=NULL;
		 root->data= value;
		 return root;
    }

    // Insert data.
    if (value > root->data) {
        root->right = insert(root->right, value);
    }
    else if (value < root->data) {
        root->left = insert(root->left, value);
    }

    
    return root;
}

void bfs(node *head)
{

   	 queue<node*> q;
   	 q.push(head);
   	 
   	 int qSize;
   	 
   	 while (!q.empty())
   	 {
   		 qSize = q.size();
   		 #pragma omp parallel for
            	//creates parallel threads
   		 for (int i = 0; i < qSize; i++)
   		 {
   			 node* currNode;
   			 #pragma omp critical
   			 {
   			   currNode = q.front();
   			   q.pop();
   			   cout<<"\t"<<currNode->data;
   			   
   			 }// prints parent node
   			 #pragma omp critical
   			 {
   			 if(currNode->left)// push parent's left node in queue
   				 q.push(currNode->left);
   			 if(currNode->right)
   				 q.push(currNode->right);
   			 }// push parent's right node in queue   	 

   		 }
   	 }

}

int main(){

    node *root=NULL;
    int data;
    char ans;
    
    do
    {
   	 cout<<"\n enter data=>";
   	 cin>>data;
   	 
   	 root=insert(root,data);
    
   	 cout<<"do you want insert one more node?";
   	 cin>>ans;
    
    }while(ans=='y'||ans=='Y');
    
    bfs(root);
    
    return 0;
}
