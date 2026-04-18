#include "deter.h"
#include <errno.h>

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
    memcpy(new->value, value, sizeof(new->value));
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
    int count_list = 0;
    int count_op = 0;

    while (*line != '\0' && *line != '\n')
    {
        while (isspace(*line))
        {
            line++;
        }
        if (*line == '(')
        {
            line++;
            push(&pointers, root);
            push(&pointers, now);
            root = NULL;
            now = NULL;
            // выделяем поддерево
            continue;
        }
        if (*line == ')')
        {
            line++;
            if (!pointers)
            {
                destroy_tree(&root);
                destroy_stack(&pointers);
                return NULL;
            }
            // совмещаем два поддерева
            now = pop(&pointers);
            if (!now)
            {
                pop(&pointers); // убираем бессмысленный root=NULL
                while (isspace(*line))
                {
                    line++;
                }
                if (*line == '\0')
                {
                    now = root;
                    break;
                }
                int l = len_value(line);
                char extra_value[11];
                memcpy(extra_value, line, l);
                if (index_of_operator(extra_value) == -1)
                {
                    destroy_tree(&root);
                    destroy_stack(&pointers);
                    return NULL;
                }

                Node *extra_Node = createNode(extra_value);
                if (!extra_Node)
                {
                    destroy_tree(&root);
                    destroy_stack(&pointers);
                    return NULL;
                }

                extra_Node->isRoot = true;
                extra_Node->sSheet = false;
                extra_Node->left_child = root;
                root->parent = extra_Node;
                root->isRoot = false;
                root = extra_Node;
                now = root;

                count_list += index_of_operator(now->value) == -1 ? 1 : 0;
                count_op += index_of_operator(now->value) != -1 ? 1 : 0;
                if (!strncmp("!", now->value, 1))
                {
                    count_list += 1;
                }

                line += l;
                continue;
            }
            else
            {
                // in now old tree, root is subtree
                now->right_child = root;
                if (root)
                {
                    root->parent = now;
                }
                root->isRoot = false;
                now->sSheet = false;
                root = pop(&pointers);
            }
        }

        while (isspace(*line))
        {
            line++;
        }
        int len = len_value(line);
        if (len == 0)
        {
            destroy_stack(&pointers);
            destroy_tree(&root);
            return NULL;
        }
        char value[11];

        memcpy(value, line, len);

        value[len] = '\0';
        Node *new_node = createNode(value);
        if (!new_node)
        {
            destroy_tree(&root);
            destroy_stack(&pointers);
            return NULL;
        }
        add_Node(&root, &now, new_node);
        count_list += index_of_operator(new_node->value) == -1 ? 1 : 0;
        count_op += index_of_operator(new_node->value) != -1 ? 1 : 0;
        if (!strncmp("!", new_node->value, 1))
        {
            count_list += 1;
        }
        line += len;
    }
    destroy_stack(&pointers);
    if (pointers || (count_list != count_op + 1))
    {
        destroy_tree(&root);
        return NULL;
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
        if (!strncmp("!", new->value, 1))
        {
            count_list += 1;
        }
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

Node *load_pst_expr(char *source)
{
    Node *root = NULL;
    Node *now = NULL;
    int count_list = 0;
    int count_op = 0;

    char *line = (char *)malloc(strlen(source) + 1);
    char *start = line;
    memcpy(line, source, strlen(source) + 1);
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
            if (!strncmp("!", new->value, 1))
            {
                count_list += 1;
            }
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
        if (!strncmp("!", new->value, 1))
        {
            count_list += 1;
        }
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
    free(start);
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
            if (result.len + 1 == result.capacity)
            {
                result.capacity *= 2;
                result.data = (char *)realloc(result.data, result.capacity);
            }
            memcpy(result.data + result.len, now->value, strlen(now->value));
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
            memcpy(result.data + result.len, now->value, strlen(now->value));
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
    reverse_sequence(result.data);
    return result;
}

static unsigned long long eval_uabs(long long x)
{
    if (x >= 0)
    {
        return (unsigned long long)x;
    }
    if (x == LLONG_MIN)
    {
        return 1ULL << 63;
    }
    return (unsigned long long)(-x);
}

static unsigned long long eval_ugcd(unsigned long long a, unsigned long long b)
{
    while (b != 0)
    {
        unsigned long long t = b;
        b = a % b;
        a = t;
    }
    return a;
}

static bool eval_parse_literal(const char *s, long long *out)
{
    errno = 0;
    char *end = NULL;
    long long v = strtoll(s, &end, 10);
    if (errno == ERANGE || end == s || *end != '\0')
    {
        return false;
    }
    *out = v;
    return true;
}

static bool eval_pow(long long base, long long exp, long long *out)
{
    if (exp < 0)
    {
        return false;
    }
    if (exp == 0)
    {
        *out = 1;
        return true;
    }
    long long acc = 1;
    long long b = base;
    unsigned long long e = (unsigned long long)exp;
    while (e > 1)
    {
        if (e & 1ULL)
        {
            if (__builtin_mul_overflow(acc, b, &acc))
            {
                return false;
            }
        }
        e >>= 1;
        if (e && __builtin_mul_overflow(b, b, &b))
        {
            return false;
        }
    }
    return !__builtin_mul_overflow(acc, b, &acc) && (*out = acc, true);
}

static bool eval_factorial(long long n, long long *out)
{
    if (n < 0)
    {
        return false;
    }
    if (n <= 1)
    {
        *out = 1;
        return true;
    }
    /* 21! > LLONG_MAX; без ограничения цикл ушёл бы в миллиарды итераций */
    if (n > 20)
    {
        return false;
    }
    long long r = 1;
    for (long long i = 2; i <= n; i++)
    {
        if (__builtin_mul_overflow(r, i, &r))
        {
            return false;
        }
    }
    *out = r;
    return true;
}

static bool eval_gcd(long long a, long long b, long long *out)
{
    unsigned long long ua = eval_uabs(a);
    unsigned long long ub = eval_uabs(b);
    if (ua == 0 && ub == 0)
    {
        *out = 0;
        return true;
    }
    unsigned long long g = eval_ugcd(ua, ub);
    if (g > (unsigned long long)LLONG_MAX)
    {
        return false;
    }
    *out = (long long)g;
    return true;
}

static bool eval_lcm(long long a, long long b, long long *out)
{
    unsigned long long ua = eval_uabs(a);
    unsigned long long ub = eval_uabs(b);
    if (ua == 0 || ub == 0)
    {
        *out = 0;
        return true;
    }
    unsigned long long g = eval_ugcd(ua, ub);
    unsigned long long q = ua / g;
    unsigned long long prod;
    if (__builtin_mul_overflow(q, ub, &prod) || prod > (unsigned long long)LLONG_MAX)
    {
        return false;
    }
    *out = (long long)prod;
    return true;
}

static bool eval_recursive(Node *node, VARS *vars, long long *out);

static bool eval_unary_child(Node *node, VARS *vars, long long *out)
{
    Node *arg = node->left_child ? node->left_child : node->right_child;
    return arg && eval_recursive(arg, vars, out);
}

static bool eval_recursive(Node *node, VARS *vars, long long *out)
{
    if (!node)
    {
        return false;
    }
    char op_idx = index_of_operator(node->value);
    if (op_idx == (char)-1)
    {
        if (isdigit((unsigned char)node->value[0]) ||
            (node->value[0] == '-' && isdigit((unsigned char)node->value[1])))
        {
            return eval_parse_literal(node->value, out);
        }
        for (VARS *v = vars; v; v = v->next)
        {
            if (strcmp(v->name, node->value) == 0)
            {
                *out = v->value;
                return true;
            }
        }
        return false;
    }

    long long l = 0;
    long long r = 0;
    switch (op_idx)
    {
    case 0: // +
        if (!eval_recursive(node->left_child, vars, &l) ||
            !eval_recursive(node->right_child, vars, &r))
        {
            return false;
        }
        return !__builtin_add_overflow(l, r, out);
    case 1: // -
        if (!eval_recursive(node->left_child, vars, &l) ||
            !eval_recursive(node->right_child, vars, &r))
        {
            return false;
        }
        return !__builtin_sub_overflow(l, r, out);
    case 2: // *
        if (!eval_recursive(node->left_child, vars, &l) ||
            !eval_recursive(node->right_child, vars, &r))
        {
            return false;
        }
        return !__builtin_mul_overflow(l, r, out);
    case 3: // /
        if (!eval_recursive(node->right_child, vars, &r))
        {
            return false;
        }
        if (r == 0)
        {
            *out = 0;
            return true;
        }
        if (!eval_recursive(node->left_child, vars, &l))
        {
            return false;
        }
        if (r == -1 && l == LLONG_MIN)
        {
            return false;
        }
        *out = l / r;
        return true;
    case 4: // %
        if (!eval_recursive(node->right_child, vars, &r))
        {
            return false;
        }
        if (r == 0)
        {
            *out = 0;
            return true;
        }
        if (!eval_recursive(node->left_child, vars, &l))
        {
            return false;
        }
        if (r == -1 && l == LLONG_MIN)
        {
            return false;
        }
        *out = l % r;
        return true;
    case 5: // ^
        if (!eval_recursive(node->left_child, vars, &l) ||
            !eval_recursive(node->right_child, vars, &r))
        {
            return false;
        }
        return eval_pow(l, r, out);
    case 6: // @ gcd
        if (!eval_recursive(node->left_child, vars, &l) ||
            !eval_recursive(node->right_child, vars, &r))
        {
            return false;
        }
        return eval_gcd(l, r, out);
    case 7: // # lcm
        if (!eval_recursive(node->left_child, vars, &l) ||
            !eval_recursive(node->right_child, vars, &r))
        {
            return false;
        }
        return eval_lcm(l, r, out);
    case 8: // !
        if (!eval_unary_child(node, vars, &l))
        {
            return false;
        }
        return eval_factorial(l, out);
    default:
        return false;
    }
}

bool eval(Node *node, VARS *vars, long long *result)
{
    if (!result)
    {
        return false;
    }
    return eval_recursive(node, vars, result);
}

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
        }
    }
    *root = NULL;
}
