#include "deter.h"

createNode(char *value)
{
    ;
}

bool priority(Node *n1, Node *n2)
{
    ;
}

bool push(stack **pointers, Node *ptr)
{
    stack *new = (stack *)malloc(sizeof(stack *));
    if(!new)
    {
        return false;
    }
    new->before = *pointers;
    new->ptr = ptr;
    *pointers = new;
    return true;
}

Node *pop(stack **pointers)
{
    if(pointers == NULL || *pointers == NULL)
    {
        return NULL;
    }
    Node *ptr = (*pointers)->ptr;
    (*pointers) = (*pointers)->before;
    return ptr;
    
}

void destroy_stack(stack **pointers)
{
    while(*pointers != NULL)
    {
        stack *tmp = (*pointers)->before;
        free(*pointers);
        (*pointers) = tmp;
    }
    return;
}

unsigned char len_value(char *start)
{
    unsigned char len = 0;
    while (isspace(*start))
    {
        start++;
    }

    while (len < 11 && isalnum(*(start + len)))
    {
        len++;
    }
    return len;
}

Node *parse_expr(char *line)
{
    Node *root = NULL;
    stack *pointers = NULL;
    Node *now = NULL;
    while (*line != '\0' && *line != '\n')
    {
        while (isspace(*line))
        {
            line++;
        }
        bool pr = 0;
        if (*line == '(')
        {
            pr = 1;
            line++;
            push(&pointers, )
        }
        int len = len_value(line);
        if (len == 11 || len == 0)
        {
            // обработка ошибки
            ;
        }
        char value[11];
        strncpy(value, line, len);
        value[10] = '\0';
        Node *new_node = createNode(value);
        if (priority(now, new_node))
        {
        }
        else
        {
        }
    }
    return root;
}

void load_prf_expr(char *line);

void save_prf(Node *tree);

void save_pst(Node *tree);

void eval(Node *tree, int args);

void destroy_tree(massiveToken *tree)
{
    ;
}

int main()
{
    ;
}