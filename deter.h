#ifndef DETER_H
#define DETER_H

#include <stdio.h>
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
    struct Node *right_child;
    enum typeValue type;
    char value[11];
    char op;
    // bool sSheet;
    bool isRoot;
} Node;

typedef struct
{
    char *data;
    int len;
    int capacity;
} massiveToken;

#endif