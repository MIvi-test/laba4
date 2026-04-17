#include "deter.h"

bool push(stack **pointers, Node *ptr)
{
    if (!pointers)
    {
        return false;
    }
    stack *new = (stack *)malloc(sizeof(stack));
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
    stack *old = *pointers;
    *pointers = (*pointers)->before;
    free(old);
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
    for (long unsigned int i = 0; i < sizeof(ALL_OPERATORS) / sizeof(ALL_OPERATORS[0]); i++)
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
        if (n2 == 8)
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

void reverse(char *start, char *end)
{
    end--;
    while (start < end)
    {
        char temp = *start;
        *start = *end;
        *end = temp;
        start++;
        end--;
    }
}

void reverse_sequence(char *str)
{
    if (!str)
    {
        return;
    }
    int len = strlen(str);

    reverse(str, str + len);
    int lw = 0;
    while (*str)
    {
        while (isspace(*str))
        {
            str++;
        }
        lw = len_value(str);
        reverse(str, str + lw);
        str += lw;
    }
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

Node *load_prf_expr(char *line)
{
    Node *root = NULL;
    Node *now = NULL;
    int count_list = 0;
    int count_op = 0;
    while (*line != '\0')
    {
        while (isspace(*line))
        {
            line++;
        }
        if (!isalnum(*line) && index_of_operator(line) == -1)
        {
            return NULL;
        }
        int len = len_value(line);
        char value[11];
        strncpy(value, line, len);
        value[len] = '\0';
        Node *new = createNode(value);
        if (!new)
        {
            printf("[ERROR] ошибка выделения памяти\n");
            destroy_tree(&root);
            return NULL;
        }
        if (root == NULL)
        {
            count_list += index_of_operator(new->value) == -1 ? 1 : 0;
            count_op += index_of_operator(new->value) != -1 ? 1 : 0;
            root = new;
            now = new;
            new->isRoot = true;
            line += len;
            continue;
        }

        while ((now != NULL) && (now->left_child != NULL) &&
               (now->right_child != NULL))
        {
            now = now->parent;
        }
        if (now == NULL)
        {
            free(new);
            break;
        }

        if (now->left_child == NULL)
        {
            now->left_child = new;
        }
        else
        {
            now->right_child = new;
        }
        now->sSheet = false;
        new->parent = now;

        count_list += index_of_operator(new->value) == -1 ? 1 : 0;
        count_op += index_of_operator(new->value) != -1 ? 1 : 0;
        if (index_of_operator(new->value) != -1)
        {
            now = new;
        }
        line += len;
    }
    if (count_op + 1 != count_list || now == NULL)
    {
        destroy_tree(&root);
        return NULL;
    }
    return root;
}

Node *load_pst_expr(char *line)
{
    Node *root = NULL;
    Node *now = NULL;
    int count_list = 0;
    int count_op = 0;
    reverse_sequence(line);
    while (*line != '\0')
    {
        while (isspace(*line))
        {
            line++;
        }
        if (!isalnum(*line) && index_of_operator(line) == -1)
        {
            return NULL;
        }
        int len = len_value(line);
        char value[11];
        strncpy(value, line, len);
        value[len] = '\0';
        Node *new = createNode(value);
        if (!new)
        {
            printf("[ERROR] ошибка выделения памяти\n");
            destroy_tree(&root);
            return NULL;
        }
        if (root == NULL)
        {
            root = new;
            new->isRoot = true;
            now = new;
            line += len;
            count_list += index_of_operator(new->value) == -1 ? 1 : 0;
            count_op += index_of_operator(new->value) != -1 ? 1 : 0;
            continue;
        }

        if (!now)
        {
            break;
        }
        if (now->right_child == NULL)
        {
            now->right_child = new;
        }
        else if (now->left_child == NULL)
        {
            now->left_child = new;
        }
        else
        {
            now = now->parent;
            now->left_child = new;
        }
        new->parent = now;
        now->sSheet = false;
        count_list += index_of_operator(new->value) == -1 ? 1 : 0;
        count_op += index_of_operator(new->value) != -1 ? 1 : 0;
        if (index_of_operator(new->value) != -1)
        {
            now = new;
        }
        line += len;
    }

    if (count_op + 1 != count_list || now == NULL)
    {
        destroy_tree(&root);
        return NULL;
    }
    return root;
}

massiveToken save_prf(Node *root)
{
    Node *now = root;
    stack *NODES = NULL;
    massiveToken result;
    result.len = 0;
    result.capacity = 64;
    result.data = NULL;
    if (!root)
    {
        return result;
    }
    result.data = (char *)malloc(result.capacity);
    while (now != NULL || NODES != NULL)
    {
        if (now == NULL)
        {
            Node *old = pop(&NODES);
            if (!old)
            {
                continue;
            }
            now = old->right_child;
        }
        else
        {
            // printf("%s ", now->value);
            if (result.len + 1 == result.capacity)
            {
                result.capacity *= 2;
                result.data = (char *)realloc(result.data, result.capacity);
            }
            strncpy(result.data + result.len, now->value, strlen(now->value));
            result.len += strlen(now->value) + 1;
            result.data[result.len - 1] = ' ';

            if (now->sSheet == false)
            {
                push(&NODES, now);
            }
            now = now->left_child;
        }
    }
    result.len--;
    result.data[result.len] = '\0';
    destroy_stack(&NODES);
    return result;
}

massiveToken save_pst(Node *root)
{
    Node *now = root;
    stack *NODES = NULL;
    massiveToken result;
    result.len = 0;
    result.capacity = 64;
    result.data = NULL;
    if (!root)
    {
        return result;
    }
    result.data = (char *)malloc(result.capacity);
    while (now != NULL || NODES != NULL)
    {
        if (now != NULL)
        {
            if (result.len + 1 == result.capacity)
            {
                result.capacity *= 2;
                result.data = (char *)realloc(result.data, result.capacity);
            }
            strncpy(result.data + result.len, now->value, strlen(now->value));
            result.len += strlen(now->value) + 1;
            result.data[result.len - 1] = ' ';
            push(&NODES, now);
            now = now->right_child;
        }
        else
        {
            Node *old = pop(&NODES);
            now = old->left_child;
        }
    }

    result.len--;
    result.data[result.len] = '\0';
    destroy_stack(&NODES);
    return result;
}

void eval(Node *tree, int args);

void destroy_tree(Node **root)
{
    Node *now = *root;
    while (now != NULL)
    {
        if (now->left_child == NULL && now->right_child == NULL)
        {
            Node *temp = now->parent;
            if (temp != NULL)
            {
                if (temp->left_child == now)
                {
                    temp->left_child = NULL;
                }
                else
                {
                    temp->right_child = NULL;
                }
            }
            free(now);
            now = temp;
        }
        else
        {
            if (now->left_child != NULL)
            {
                now = now->left_child;
            }
            else if (now->right_child != NULL)
            {
                now = now->right_child;
            }
            else
            {
                printf("[ERROR] no list, but haven't child\n");
                free(now);
                return;
            }
        }
    }
    // *root = NULL;
}
