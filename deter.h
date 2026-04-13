#ifndef DETER_H
#define DETER_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
// #include "auxiliary.c"

enum typeValue
{
    OP = 0,
    INT
};

typedef struct Node
{
    struct Node *left_child;
    struct Node *parent;
    struct Node *right_child;
    char value[11];
    bool isRoot;

} Node;

typedef struct pointer_stack
{
    Node *ptr;
    struct pointer_stack *before; 
} stack;


typedef struct
{
    char *data;
    int len;
    int capacity;
} massiveToken;

#endif