#ifndef PARSER
#define PARSER

typedef struct {
    char* data;
    int size;
    int top;
} Stack;

char (*parseJSON(const char* json))[100][256] ;
#endif // !PARSER

