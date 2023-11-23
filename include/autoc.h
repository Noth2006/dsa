#ifndef AUTOC
#define AUTOC

typedef struct trienode{
    struct trienode *child[255];
    int Eow;
}NODEE;
NODEE *getnode();
void insert(char *key,NODEE *root);
void display_prefix(NODEE *root,char *prefix);
#endif // !AUTOC

