#ifndef DETER_H
#define DETER_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <ctype.h>
#include <math.h>
// #include "auxiliary.c"

enum typeToken
{
    VALUE = 0,
    PLUS,
    MUNIS,
    MULTUPHLY,
    DIVISION,
    MODUL,
    POWER,
    NOK,
    NOD,
    FACTORIAL
};

typedef struct Node
{
    struct Node *left_child;
    struct Node *parent;
    struct Node *right_child;
    char value[11];
    bool isRoot;
    bool sSheet;
} Node;

typedef struct pointer_stack
{
    Node *ptr;
    struct pointer_stack *before; 
} stack;

typedef struct VARS
{
    struct VARS *next;
    long long value;
    char name[11];
} VARS;

typedef struct
{
    char *data;
    int len;
    int capacity;
} massiveToken;

char *ALL_OPERATORS[] = {"+","-",\
                        "*","/","%%",\
                         "^",\
                         "@",\
                         "#",\
                         "!"};
#endif