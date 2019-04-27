#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct singlell{
	char proid[5];			
	int beg;
	int end;					//the structure of the node
	int free;
	struct singlell* next;
	struct singlell* prev;
}node;
node *os,*getnode();
void display(),initial(),allocate(),terminate(),insert(node* ptr,int size),deleteaft(node* ptr),deletebef(node* ptr);

void initial(){
	node* inifree;
	os=getnode();
	inifree=getnode();
	strcpy(os->proid,"OS");
	os->beg=0;							//For the Operating system
	os->end=399;
	os->free=0;
	os->next=inifree;
	os->prev=NULL;
	strcpy(inifree->proid,"FREE");
	inifree->beg=400;					//For the initial free slot
	inifree->end=2599;
	inifree->free=1;
	inifree->next=NULL;
	inifree->prev=os;
	display();
		
}
	
void main(){
int opt;	
	initial();
	do{
		printf("  OPTIONS\n1.Allocate\n2.Terminate\n3.Exit\n");
		printf("\nEnter Option: ");
		scanf("%d",&opt);
		switch(opt){
			case 1:allocate();break;
			case 2:terminate();break;
			default:
					if (opt!=3)
						printf("ERROR:No such option\n\n");
		}		
	}while(opt!=3);
}

node* getnode(){
	
	node* newnode;
	newnode=(node*)malloc(sizeof(node));	//creating a node		
	newnode->next=NULL;
	newnode->prev=NULL;
	return newnode;	
	
}

void insert(node* ptr,int size){
	
				node *newnode=getnode();
				newnode->next=ptr->next;
				ptr->next=newnode;			//inserting a free node after the given node
				newnode->prev=ptr;
				strcpy(newnode->proid,"FREE");
				newnode->free=1;
				newnode->beg=ptr->beg+size;
				newnode->end=ptr->end;
	
}

void deleteaft(node* ptr){
	
			node *aftptr=ptr->next;
			ptr->end=aftptr->end;		//delete the node after a given node
			ptr->next=aftptr->next;
			if(aftptr->next!=NULL)
				aftptr->next->prev=ptr;
			free(aftptr);		
	
}

void deletebef(node* ptr){
	
			node *preptr=ptr->prev;		//delete the node before a given node
			ptr->beg=preptr->beg;
			preptr->prev->next=ptr;
			ptr->prev=preptr->prev;
			free(preptr);		
	
}

void allocate(){
	node *ptr=os;
	int size,flag=0;
	char arr[5];
	printf("Enter process ID: ");
	scanf("%s",arr);
	printf("Enter size: ");
	scanf("%d",&size);
	while(ptr!=NULL)
	{
		if((ptr->free==1) && (size<=((ptr->end-ptr->beg)+1)))//finding if a node is free and also if the inputted size is available in that node
		{	
			flag=1;
			if(size<((ptr->end-ptr->beg)+1)){
					insert(ptr,size);
						}
						
			strcpy(ptr->proid,arr);
			ptr->end=ptr->beg+size-1;
			ptr->free=0;
		
		break;			
		}
		ptr=ptr->next;
			}
	if (flag==0)		//when no free node is available for the inputted size
			printf("Memory Full\n");
	display();
}

void terminate(){
	char arr[5];
	printf("Enter process ID to terminate: ");
	scanf("%s",arr);
	node *ptr=os;
	while(strcmp(ptr->proid,arr))
			ptr=ptr->next;			//finds the process to terminate	
	ptr->free=1;
	strcpy(ptr->proid,"FREE");//makes the node free
	
	if(ptr->prev->free==1)//finds if the previous node is also free
		deletebef(ptr);	
	if(ptr->next!=NULL&&ptr->next->free==1)//finds if the next node is also free
		deleteaft(ptr);
		
	display();
}

void display(){
	node *ptr=os;
	printf("\n************MEMORY LAYOUT************\n\n");
	while(ptr!=NULL){
		printf("%s\t [%d-%d]\t SIZE=%d\n",ptr->proid,ptr->beg,ptr->end,(ptr->end-ptr->beg)+1);
		ptr=ptr->next;
}
printf("\n");
}
