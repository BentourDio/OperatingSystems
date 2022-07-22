#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "postcode_index.h"

struct PostCodeIndex * Insert_PostCode(struct PostCodeIndex *p, int postcode)
{//au3ousa seira. otan dimiourgeitai neo node 8a mpainei sthn arxh
	struct PostCodeIndex* New_postNode;
	New_postNode =(struct PostCodeIndex*) malloc (sizeof (struct PostCodeIndex));
	New_postNode->next=NULL;
	New_postNode->previous=NULL;
	New_postNode->rank=0;

	if(p==NULL){
		p=New_postNode;
		New_postNode->postcode=postcode;
		p->counter=1;

	}
	else{
		New_postNode->next=p;
		p->previous=New_postNode;
		p=New_postNode;
		New_postNode->postcode=postcode;
		New_postNode->counter=1;
	}
	return p;
}

struct PostCodeIndex* Search_PostCode(struct PostCodeIndex* p, int postcode)
{
	if(p==NULL)
		return NULL;
	struct PostCodeIndex* temp;
	temp=p;
	while(temp!=NULL){
		if((temp->postcode)==postcode){
			return temp;
		}
		else
			temp=temp->next;
	}
	return NULL;
}

void DestoyPostIndex(struct PostCodeIndex* p)
{
	struct PostCodeIndex* temp,*aux;
	temp=p;

	while(temp!=NULL){
		aux=temp;
		temp=temp->next;
		free(aux);
	}
}

struct PostCodeIndex* PostCode_Delete_Student(struct PostCodeIndex* p,int post_code)
{
	struct PostCodeIndex* temp = Search_PostCode(p,post_code);
	temp->counter--;
	if(temp->previous!=NULL && temp->counter <= temp->previous->counter){
		int temp_postcode = temp->postcode;
	    int temp_post_counter = temp->counter;
	    //swap the data between two objects
	    temp->counter = temp->previous->counter;
	    temp->postcode = temp->previous->postcode;
	    temp->previous->postcode = temp_postcode;
        temp->previous->counter = temp_post_counter;
	}
	return p;
}

void PrintRank(struct PostCodeIndex* p, int num)
{
	struct PostCodeIndex* temp = p;
	int i;
	int c=1;
	while(temp->next!=NULL){
		temp=temp->next;
		c++;
	}
	//printf("the zip is %d\n",temp->postcode);
	//printf("counters is %d\n",c);
	//printf("\t\t\t\t\tTHE POST CODE IS %d\n",temp->postcode);
	temp->rank=1;

	for(i=0;i<num && temp!=NULL;i++){
		
//		printf("\t\t\t\t\tTHE POST CODE IS %d\n",temp->postcode);

		temp=temp->previous;
	}
	if(temp!=NULL){
		printf("	-list (%d) is/are %d most popular\n",temp->next->postcode,num);
	}
	else if(c==num){
		printf("	-list (%d) is/are %d most popular\n",p->postcode,num);
	}
	else
		printf("	-No Students are enrolled\n");
		

	/*while(temp!=NULL){
		printf("	zip:%d 		counter:%d\n",temp->postcode,temp->counter);
		temp=temp->previous;
	}*/
}