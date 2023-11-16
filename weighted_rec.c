#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "parser.h"
#define MAX 30

typedef struct node{
    char name[MAX];
    int cost;
    int weight;// let the weight the difference in costs
    struct node*next;
}NODE;

NODE*create(char name[],int cost){
    NODE* new=(NODE*)malloc(sizeof(NODE));
    if(new==NULL){
        printf("memory allocation failed");
    }
    else{
        memcpy(new->name,name,MAX);
        new->cost=cost;
        new->weight=0;
        return new;}
}

void update(NODE* head, NODE* new) {
    if (head == NULL) {
        head = new;
    } else {
        NODE* curr = head;
        while (curr->next != NULL) {
            curr = curr->next;
        }
        curr->next = new;
    }
}


void find_closest(NODE*head,NODE*interest){
    NODE*curr=head;
    int p=interest->cost;
    while(curr!=NULL){
        curr->weight=abs(curr->cost-p);
        curr=curr->next;
    }
}



void update_graph(NODE*arr[],NODE*head,NODE*interest){
    //find index of the interest node
    int count =0;
    NODE*curr=head;
    while(curr!=NULL){
        if(curr->cost==interest->cost){
            break;
        }
        curr=curr->next;
        count++;
    }
    NODE*temp=head;
    while(temp!=NULL){
        if(temp->weight<=4000){
            arr[count]=temp;
            printf("name:%s\n cost%d\n",temp->name,temp->cost);
        } 
        temp=temp->next;
    }
    if(arr[count]==NULL||arr[count]==interest){
        printf("No related products\n");
    }
}


int main(){
    //take file as input and then make the linked list , let the remaining be the same

    NODE*arr[MAX]={NULL};
    NODE*one=create("dell",50000);
    NODE*two=create("Hp",54000);
    update(one,two);
    NODE*three=create("asus",38000);
    update(one,three);
    NODE*four=create("acer",76000);
    update(one,four);
    FILE* file = fopen("data.json", "r");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }


    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    fseek(file, 0, SEEK_SET);


    char* json = (char*)malloc((fileSize + 1) * sizeof(char));


    fread(json, sizeof(char), fileSize, file);
    json[fileSize] = '\0';

    fclose(file);
    char (*test)[100][256];
    test = parseJSON(json);

    free(json);

    find_closest(one,three);
    update_graph(arr,one,three);

}
