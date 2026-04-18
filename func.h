#ifndef FUNC_H
#define FUNC_H
#include "deter.h"


void reverse(char *start, char *end);

void reverse_sequence(char *str);

char index_of_operator(char *ch);

Node *createNode(char *value);

bool priority(Node *n1, Node *n2);

bool push(stack **pointers, Node *ptr);

Node *pop(stack **pointers);

Node *peak(stack **pointers);

void destroy_stack(stack **pointers);

Node *add_node(Node **root, Node **now, Node *new);

unsigned char len_value(char *start);

Node *parse_expr(char *line);

Node *load_prf_expr(char *line);

Node *load_pst_expr(char *line);

massiveToken save_prf(Node *root);

massiveToken save_pst(Node *root);

bool eval(Node *node, VARS *vars, long long *result);

void destroy_tree(Node **root);


#include "func.c"

#endif