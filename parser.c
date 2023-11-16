
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"
void initializeStack(Stack* stack, int size) {
    stack->data = (char*)malloc(size * sizeof(char));
    stack->size = size;
    stack->top = -1;
}

void push(Stack* stack, char element) {
    if (stack->top == stack->size - 1) {
        stack->size *= 2;
        stack->data = (char*)realloc(stack->data, stack->size * sizeof(char));
    }
    stack->data[++stack->top] = element;
}

char pop(Stack* stack) {
    if (stack->top == -1) {
        return '\0';
    }
    return stack->data[stack->top--];
}

char (*parseJSON(const char* json))[100][256] {
    Stack stack;
    initializeStack(&stack, 10);
    char prev[256];
    int inString = 0;
    char key[256];
    char parent[100][256];
    char (*arr)[100][256] = malloc(sizeof(char[100][256]));
    int keyIndex = 0;
    int eofFlag = 0;
    int itemno = 0;
    char item[2][256];
    for (int i = 0; json[i] != '\0'; i++) {
        char currentChar = json[i];

        switch (currentChar) {
            case '{':
            case '[':
                push(&stack, currentChar);
                break;
            case '}':
                if (pop(&stack) != '{') {
                    printf("Error: Mismatched braces\n");
                    return NULL;
                }
                if(!eofFlag){
                printf("%s %s\n",item[0],item[1]);
                strcpy((*arr)[itemno++],item[0]);
                strcpy((*arr)[itemno++],item[1]);
                }
                break;
            case ']':
                if (pop(&stack) != '[') {
                    printf("Error: Mismatched brackets\n");
                    return NULL;
                }
                eofFlag = 1;
                break;
            case '"':

                inString = !inString;
                break;
            case ':':

                if (!inString) {
                    key[keyIndex] = '\0';
                    strcpy(prev,key);
                    keyIndex = 0;
                    for (int i = 0; i<256; i++) {
                        key[i] = '\0';
                    }
                }
                break;
            case ',':

                if (!inString && keyIndex > 0) {
                    if(!strcmp(prev,"price")){
                        strcpy(item[1],key);
                    }else if(!strcmp(prev,"model")){
                        strcpy(item[0],key);
                    }
                    keyIndex = 0;
                    for (int i = 0; i<256; i++) {
                        key[i] = '\0';
                    }
                }
                break;
            default:

                if (inString && keyIndex < sizeof(key) - 1) {
                    key[keyIndex++] = currentChar;
                }
                break;
        }
    }

    free(stack.data);
    return arr;
}

int main() {

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

    return 0;
}
