#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX 50

typedef struct node{
  char status[MAX];
  char time[MAX];
  struct node* link;
}NODE;

NODE *create_node(char status[], char time[])
{
  NODE *package = malloc(sizeof(NODE));
  package->link = NULL;
  memcpy(package->status, status, MAX);
  memcpy(package->time, time, MAX);
  return package;
}

NODE *update_node(NODE *curr, char status[], char time[])
{
  NODE *new = create_node(status, time);
  NODE *temp = curr;
  while(temp->link!=NULL)
  {
    temp = temp->link;
  }
  temp->link = new;
}

void destroy(NODE* root)
{
  NODE*curr=root;
  while(curr!=NULL)
  {
  NODE*temp=curr;
  curr=curr->link;
  free(temp);
  }
}

void display(NODE *root)
{
  NODE *temp = root;
  while(temp!=NULL)
  {
    printf("%s %s", temp->status, temp->time);
    temp = temp->link;
    printf("\n");
  }
}

int main()
{
  NODE *example = create_node("registered","5th february 12:00pm");
  display(example);
  update_node(example,"shipped","7th february 9:00am");
  update_node(example,"out for delivery","7th february 1:00pm");
  update_node(example,"delivered","7th february 5:00pm");
  display(example);
}
