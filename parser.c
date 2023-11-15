
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* data;
    int size;
    int top;
} Stack;

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

void parseJSON(const char* json) {
    Stack stack;
    initializeStack(&stack, 10);
    char* prev;
    int inString = 0;
    char key[256];
    int keyIndex = 0;

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
                    return;
                }
                break;
            case ']':
                if (pop(&stack) != '[') {
                    printf("Error: Mismatched brackets\n");
                    return;
                }
                break;
            case '"':

                inString = !inString;
                break;
            case ':':

                if (!inString) {
                    key[keyIndex] = '\0';
                    prev = key;
                    keyIndex = 0;
                }
                break;
            case ',':

                if (!inString && keyIndex > 0) {
                    if(strcmp(prev, "price")){
                    printf("Value: %s\n", key);
                    keyIndex = 0;
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


    if (stack.top == -1) {
        printf("JSON is valid\n");
    } else {
        printf("Error: Unmatched braces or brackets\n");
    }

    free(stack.data);
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


    parseJSON(json);


    free(json);

    return 0;
}
