#include "deter.h"

bool push(stack **pointers, Node *ptr)
{
    if (!pointers)
    {
        return false;
    }
    stack *new = (stack *)malloc(sizeof(stack *));
    if (!new)
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
    if (pointers == NULL || *pointers == NULL)
    {
        return NULL;
    }
    Node *ptr = (*pointers)->ptr;
    (*pointers) = (*pointers)->before;
    return ptr;
}

Node *peak(stack **pointers)
{
    return (*pointers)->ptr;
}

void destroy_stack(stack **pointers)
{
    if (!pointers)
    {
        return;
    }
    while (*pointers != NULL)
    {
        stack *tmp = (*pointers)->before;
        free(*pointers);
        (*pointers) = tmp;
    }
    return;
}

char index_of_operator(char *ch)
{
    for (int i = 0; i < sizeof(ALL_OPERATORS) / sizeof(ALL_OPERATORS[0]); i++)
    {
        if (!strncmp(ch, ALL_OPERATORS[i], 1))
        {
            return (char)i;
        }
    }
    return (char)-1;
}

Node *createNode(char *value)
{
    Node *new = (Node *)malloc(sizeof(Node));
    if (!new)
    {
        return NULL;
    }
    new->isRoot = false;
    new->left_child = NULL;
    new->right_child = NULL;
    strncpy(new->value, value, sizeof(new->value));
    new->parent = NULL;
    new->sSheet = true;
    return new;
}

bool priority(Node *left, Node *right)
{
    // все сравнение выводят логический результат: левый приоритетней правого?
    char n1 = index_of_operator(left->value);
    char n2 = index_of_operator(right->value);
    if (n1 == -1 && n2 != -1)
    {
        return true;
    }
    if (n2 == -1)
    {
        return false;
    }
    switch (n1)
    {
    case 0: // +
    case 1: // -
    {
        return false;
    }
    case 2: // *
    case 3: // /
    case 4: // %
    {
        if (n2 >= 2)
        {
            return false;
        }
        break;
    }
    case 5:
    {
        if (n2 >= 5)
        {
            return false;
        }
        break;
    }
    case 6:
    {
        if (n2 >= 6)
        {
            return false;
        }
        break;
    }
    case 7:
    {
        if (n2 >= 7)
        {
            return false;
        }
        break;
    }
    case 8:
    {
        if(n2 == 8)
        {
            return false;
        }
        break;
    }
    }
    return true;
}

unsigned char len_value(char *start)
{
    unsigned char len = 0;
    while (isspace(*start))
    {
        start++;
    }
    if (index_of_operator(start) != -1)
    {
        return 1;
    }
    while (len < 11 && isalnum(*(start + len)))
    {
        len++;
    }
    if (len == 11)
    {
        return 0;
    }
    return len;
}

Node *add_Node(Node **root, Node **now, Node *new)
{
    if (root == NULL || now == NULL)
    {
        return NULL;
    }
    if (*root == NULL)
    {
        *root = new;
        *now = new;
        new->isRoot = 1;
        new->sSheet = 1;
        return new;
    }

    bool prio = priority(new, *now);
    while (prio == false)
    {
        if ((*now)->isRoot == true)
        {
            // отец + лево
            (*now)->isRoot = false;
            (*now)->sSheet = false;
            (*now)->parent = new;
            new->left_child = *now;
            *root = new;
            *now = new;
            new->isRoot = true;
            return *now;
        }
        *now = (*now)->parent;
        prio = priority(new, *now);
    }
    // сын справа
    new->left_child = (*now)->right_child;
    if ((*now)->right_child != NULL)
    {
        (*now)->right_child->parent = new;
        new->sSheet = false;
    }
    (*now)->right_child = new;
    new->parent = *now;
    (*now)->sSheet = false;
    *now = new;
    return *now;
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
        bool pr = 0; // priority
        if (*line == '(')
        {
            pr = 1;
            line++;
            push(&pointers, now); // save start position
        }
        int len = len_value(line);

        if (len == 0)
        {
            // обработка ошибки
            exit(1);
        }
        char value[11];
        strncpy(value, line, len);
        value[10] = '\0';

        Node *new_node = createNode(value);
        if (!new_node)
        {
            // обработка ошибки
            exit(1);
        }
        add_Node(&root, &now, new_node);

        line += len;
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
