#include<stdio.h>
#include "autoc.h"
#include<stdlib.h>
#include<string.h>
int length;
char str[100];

NODEE *getnode()
{
    NODEE *temp=malloc(sizeof(NODEE));
    for(int i=0;i<255;i++)
    {
        temp->child[i]=NULL;
    }
    temp->Eow=0;
    return(temp);
}
void insert(char *key,NODEE *root)
{
    NODEE *cur=root;
    int index;
    for(int i=0;key[i]!='\0';i++)
    {
        index=key[i];
        if(cur->child[index]==NULL)
            cur->child[index]=getnode();
        cur=cur->child[index];
    }
    cur->Eow=1;
}
void display(NODEE *root)
{
    NODEE *cur=root;
    for(int i=0;i<255;i++)
    {
        if(cur->child[i]!=NULL)
        {
            str[length++]=i;
            if(cur->child[i]->Eow==1)
            {
                printf("\n");
                for(int j=0;j<length;j++)
                {
                    printf("%c",str[j]);
                }
            }
            display(cur->child[i]); }
    }
    length--;
}

void display_prefix(NODEE *root,char *prefix)
{
    NODEE *cur=root;
    int index;
    for(int i=0;prefix[i]!='\0';i++)
    {
        index=prefix[i];
        if(cur->child[index]!=NULL)
        {
            str[length++]=index;
            cur=cur->child[index];
        }
    }
    if(cur->Eow==1)
    {
        for(int j=0;j<length;j++)
        {
            printf("%c",str[j]);
        }
    }
    display(cur);
}
