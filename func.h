#ifndef FUNC_H
#define FUNC_H
#include "deter.h"

char index_of_operator(char *ch);

Node *createNode(char *value);

bool priority(Node *n1, Node *n2);

bool push(stack **pointers, Node *ptr);

Node *pop(stack **pointers);

Node *peak(stack **pointers);

void destroy_stack(stack **pointers);

unsigned char len_value(char *start);

Node *parse_expr(char *line);

void load_prf_expr(char *line);

void save_prf(Node *tree);

void save_pst(Node *tree);

void eval(Node *tree, int args);

void destroy_tree(massiveToken *tree);

Node *add_node(Node **root, Node **now, Node *new);

#include "func.c"

#endif