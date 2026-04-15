#include "func.h"

bool test_index_of_operator()
{
    if (index_of_operator("*") != 2)
    {
        printf("%d ", index_of_operator("*"));
        return false;
    }
    if (index_of_operator("%%") != 4)
    {
        printf("%d ", index_of_operator("%%"));
        return false;
    }
    if (index_of_operator("_") != -1)
    {
        printf("%d ", index_of_operator("_"));
        return false;
    }
    if (index_of_operator("    f") != -1)
    {
        printf("%d ", index_of_operator("    f"));
        return false;
    }
    return true;
}

bool test_len_value()
{
    if (len_value("1234*2") != 4)
    {
        printf("1");
        return false;
    }
    if (len_value("1/") != 1)
    {
        printf("2");

        return false;
    }
    if (len_value("@123") != 1)
    {
        printf("3");

        return false;
    }
    if (len_value("*123") != 1)
    {
        printf("4");

        return false;
    }
    if (len_value("a123*4") != 4)
    {
        printf("5");

        return false;
    }
    if (len_value("aaaaaaaaaa*4") != 10)
    {
        printf("6");

        return false;
    }
    if (len_value("123123213213123*4") != 0)
    {
        printf("7");

        return false;
    }

    return true;
}

bool test_Node()
{
    Node *test_ptr1 = createNode("*");
    if (!test_ptr1 || (strcmp("*", test_ptr1->value)))
    {
        return false;
    }
    else
    {
        free(test_ptr1);
    }
    Node *test_ptr2 = createNode("+");
    if (!test_ptr2 || (strcmp("+", test_ptr2->value)))
    {
        return false;
    }
    else
    {
        free(test_ptr2);
    }
    Node *test_ptr3 = createNode("123");
    if (!test_ptr3 || (strcmp("123", test_ptr3->value)))
    {
        return false;
    }
    else
    {
        free(test_ptr3);
    }
    Node *test_ptr4 = createNode("fmdskalf fadsfadf");
    if (!test_ptr4 || !(strcmp("fmdskalf fadsfadf", test_ptr4->value)))
    {
        return false;
    }
    else
    {
        free(test_ptr4);
    }
    Node *test_ptr5 = createNode("adasdad");
    if (!test_ptr5 || (strcmp("adasdad", test_ptr5->value)))
    {
        return false;
    }
    else
    {
        free(test_ptr5);
    }
    Node *test_ptr6 = createNode("a");
    if (!test_ptr6 || (strcmp("a", test_ptr6->value)))
    {
        return false;
    }
    else
    {
        free(test_ptr6);
    }

    return true;
}

bool test_stack()
{
    stack *ptrs = NULL;
    Node *ptr1 = createNode("123");
    Node *ptr2 = createNode("+");
    Node *ptr3 = createNode("2");
    Node *ptr4 = createNode("/");
    Node *ptr5 = createNode("2");
    if (!push(&ptrs, ptr1))
    {
        destroy_stack(&ptrs);
        return false;
    }
    if (ptr1 != pop(&ptrs))
    {
        destroy_stack(&ptrs);
        return false;
    }
    if (pop(&ptrs) != NULL)
    {
        return false;
    }
    if (push(&ptrs, ptr2) && push(&ptrs, ptr3))
    {
        if (ptr3 != pop(&ptrs) || ptr2 != pop(&ptrs))
        {
            destroy_stack(&ptrs);
            return false;
        }
    }
    if (push(&ptrs, ptr4) && ptr4 != peak(&ptrs))
    {
        destroy_stack(&ptrs);
        return false;
    }
    if (push(&ptrs, ptr5) && ptr5 != peak(&ptrs))
    {
        return false;
    }
    return true;
}

bool test_priory()
{
    Node *n1 = createNode("+");
    Node *n2 = createNode("1");
    Node *n3 = createNode("abc");
    Node *n4 = createNode("-");
    Node *n5 = createNode("*");
    Node *n6 = createNode("/");
    Node *n7 = createNode("@");
    Node *n8 = createNode("#");
    Node *n9 = createNode("!");
    Node *n10 = createNode("^");
    Node *n11 = createNode("%%");
    if (priority(n1, n2) != false)
    {
        printf("[LOG] + and 1\n");
        return false;
    }
    if (priority(n2, n1) != true)
    {
        printf("[LOG] 1 and +\n");
        return false;
    }
    if (priority(n3, n2) != false)
    {
        printf("[LOG] abc and 1\n");
        return false;
    }
    if (priority(n3, n4) != true)
    {
        printf("[LOG] abc and -\n");
        return false;
    }
    if (priority(n4, n5) != false)
    {
        printf("[LOG] - and *\n");
        return false;
    }
    if (priority(n5, n6) != false)
    {
        printf("[LOG] * and /\n");
        return false;
    }
    if (priority(n5, n1) != true)
    {
        printf("[LOG] * and 1\n");

        return false;
    }
    if (priority(n7, n6) != true)
    {
        printf("[LOG] @ and /\n");
        return false;
    }
    return true;
}

bool test_add_node()
{

    static Node *root = NULL;
    static Node *now = NULL;
    Node *n1 = createNode("3");
    if (!n1)
    {
        return false;
    }
    Node *n2 = createNode("+");
    if (!n2)
    {
        free(n1);
        return false;
    }
    Node *n3 = createNode("4");
    if (!n3)
    {
        free(n1);
        free(n2);
        return false;
    }
    Node *n4 = createNode("/");
    if (!n4)
    {
        free(n1);
        free(n2);
        free(n3);
        return false;
    }
    Node *n5 = createNode("2");
    if (!n5)
    {
        free(n1);
        free(n2);
        free(n3);
        free(n4);
        return false;
    }
    if (strcmp(add_Node(&root, &now, n1)->value, "3") || !root || !now)
    {
        printf("[LOG] no added 3\n");
        return false;
    }
    if (root->isRoot != 1 || root->parent != NULL)
    {
        printf("[LOG] error status root\n");
        return false;
    }
    if (strcmp(add_Node(&root, &now, n2)->value, "+"))
    {
        printf("[LOG] no added +\n");
        return false;
    }
    if (now != n2 || root != n2)
    {
        printf("[LOG] no move now or root\n");
    }
    if (n2->left_child != n1 || n1->parent != n2)
    {
        printf("[LOG] error create relations with before elements\n");
        return false;
    }
    if (strcmp(add_Node(&root, &now, n3)->value, "4"))
    {
        printf("[LOG] no added 4\n");
        return false;
    }
    if (now->parent != n2 || n2->right_child != n3)
    {
        printf("[LOG] no add relations with +");
        return false;
    }
    if (now == root)
    {
        printf("[LOG] problem with moving NOW\n");
        return false;
    }
    if (strcmp(add_Node(&root, &now, n4)->value, "/") || root->right_child != n4)
    {
        printf("[LOG] no added /\n");
        return false;
    }
    if (root != n2)
    {
        printf("[LOG] where n2?\n");
        return false;
    }
    if (now->left_child != n3)
    {
        printf("[LOG] no create relations with n3\n");
        return false;
    }
    if (strcmp(add_Node(&root, &now, n5)->value, "2"))
    {
        printf("[LOG] no added 2");
        return false;
    }
    if (root != n2 || \
        root->left_child != n1 ||\
         root->right_child != n4 ||\
          root->right_child->left_child != n3 |\
           root->right_child->right_child != n5)
    {
        printf("[LOG] error result\n");
        return false;
    }
    return true;
}

int main()
{
    if (!test_Node())
    {
        printf("[-] create_Node\n");
        exit(1);
    }
    else
    {
        printf("[+] create_Node\n");
    }
    if (!test_stack())
    {
        printf("[-] test_stack\n");
        exit(1);
    }
    else
    {
        printf("[+] test_stack\n");
    }
    if (!test_index_of_operator())
    {
        printf("[-] index_of_operator\n");
    }
    else
    {
        printf("[+] index_of_operator\n");
    }
    if (!test_len_value())
    {
        printf("[-] len_value\n");
        exit(1);
    }
    else
    {
        printf("[+] len_value\n");
    }
    if (!test_priory())
    {
        printf("[-] test_priory\n");
    }
    else
    {
        printf("[+] test_priority\n");
    }
    if (!test_add_node())
    {
        printf("[-] add_node\n");
        exit(1);
    }
    else
    {
        printf("[+] add_node\n");
    }
}