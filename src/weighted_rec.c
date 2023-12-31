#include<stdio.h>
#include "autoc.h"
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


NODE* set_weight(char n[],NODE*root){
    NODE*temp=root;
    int cost=0;
    //find interested cost
    while(strcmp(n,temp->name)!=0){
        temp=temp->next;
    }
    if(temp==NULL)
    {
        printf("The item doesn't exit");
        return NULL;
    }
    cost=temp->cost;
    NODE*curr=root;
    while(curr!=NULL){
        curr->weight=abs(curr->cost-cost);
        curr=curr->next;
    }
    return temp;
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
        if(temp->weight<=500){
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
    FILE* file = fopen("../data.json", "r");
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
    //char (*arr)[100][256] = malloc(sizeof(char[100][256]));
    free(json);
    NODE* new;
    int i = 0;
    //    printf("%d , %s\n",strcmp((*test)[12],"NULL"),(*test)[12]);
    // for(int j = 9;j<17;j++)
    // {
    //     printf("%d : %s\n",j,(*test)[j]);
    // }
    NODEE *root=getnode();

    char prefix[100];

    while(strcmp((*test)[i], "NULL"))
    {
        new = create((*test)[i],atoi((*test)[i+1]));
        update(one,new);
        insert((*test)[i],root);
        i+=2;
    }
    int ch;
    while(1){
        printf("\nEnter 1 to search products \nEnter 2 to find closest match based on prices\n>");
        scanf("%d",&ch);
        switch(ch){
            case 1:
                printf("\nEnter the product name to search: \n");
                scanf("%s",&prefix);
                display_prefix(root,prefix);
                break;

            case 2:
                printf("\nFind closest match based on price: \n");
                scanf("%s",&prefix);
                NODE* interest = set_weight(prefix,one);
                update_graph(arr,one,interest);
                break;
        }
    }
}
