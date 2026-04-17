#include "func.h"


bool test_memory_leaks()
{
    Node *ptr1 = createNode("-");
    stack *pointers = NULL;
    push(&pointers, ptr1);
    push(&pointers, ptr1);
    push(&pointers, ptr1);
    Node *ptr2 = pop(&pointers);
    destroy_stack(&pointers);
    destroy_tree(&ptr1);
    return true;
}

bool test_reverse()
{
    // char s1[13]; strcpy(s1, "I love bread");
    char s1[] = "I love bread";
    char d1[] = "daerb evol I";
    reverse(s1, s1 + 12);
    if (strcmp(s1, d1))
    {
        printf("[LOG] s1 no complite\n");
        return false;
    }
    reverse(s1, s1 + sizeof(s1) - 1);
    if (strcmp(s1, "I love bread"))
    {
        printf("[LOG] no reverse function\n");
        return false;
    }
    char m1[] = "5 14 4 2 * - * 2 /";
    reverse(m1, m1 + sizeof(m1) - 1);
    return true;
}

bool test_reverse_sequence()
{
    char s1[] = "1+2+3+4";
    char d1[] = "4+3+2+1";
    reverse_sequence(s1);
    if (strcmp(s1, d1))
    {
        printf("[LOG] no coincidence values\n");
        return false;
    }

    char s2[] = "5 14 4 2 * - * 2 /";
    char d2[] = "/ 2 * - * 2 4 14 5";
    reverse_sequence(s2);
    if (strcmp(s2, d2))
    {
        printf("[LOG] no coincidence manual\n");
        return false;
    }

    return true;
}

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
        if (test_ptr1)
        {
            destroy_tree(&test_ptr1);
        }
        return false;
    }
    else
    {
        destroy_tree(&test_ptr1);
    }
    Node *test_ptr2 = createNode("+");
    if (!test_ptr2 || (strcmp("+", test_ptr2->value)))
    {
        if (test_ptr2)
        {
            destroy_tree(&test_ptr2);
        }
        return false;
    }
    else
    {
        destroy_tree(&test_ptr2);
    }
    Node *test_ptr3 = createNode("123");
    if (!test_ptr3 || (strcmp("123", test_ptr3->value)))
    {
        if (test_ptr3)
        {
            destroy_tree(&test_ptr3);
        }
        return false;
    }
    else
    {
        destroy_tree(&test_ptr3);
    }
    Node *test_ptr4 = createNode("fmdskalf fadsfadf");
    if (!test_ptr4 || !(strcmp("fmdskalf fadsfadf", test_ptr4->value)))
    {
        if (test_ptr4)
        {
            destroy_tree(&test_ptr4);
        }
        return false;
    }
    else
    {
        destroy_tree(&test_ptr4);
    }
    Node *test_ptr5 = createNode("adasdad");
    if (!test_ptr5 || (strcmp("adasdad", test_ptr5->value)))
    {
        if (test_ptr5)
        {
            destroy_tree(&test_ptr5);
        }
        return false;
    }
    else
    {
        destroy_tree(&test_ptr5);
    }
    Node *test_ptr6 = createNode("a");
    if (!test_ptr6 || (strcmp("a", test_ptr6->value)))
    {
        if (test_ptr6)
        {
            destroy_tree(&test_ptr6);
        }
        return false;
    }
    else
    {
        destroy_tree(&test_ptr6);
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

    destroy_stack(&ptrs);
    destroy_tree(&ptr1);
    destroy_tree(&ptr2);
    destroy_tree(&ptr3);
    destroy_tree(&ptr4);
    destroy_tree(&ptr5);
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

    destroy_tree(&n1);
    destroy_tree(&n2);
    destroy_tree(&n3);
    destroy_tree(&n4);
    destroy_tree(&n5);
    destroy_tree(&n6);
    destroy_tree(&n7);
    destroy_tree(&n8);
    destroy_tree(&n9);
    destroy_tree(&n10);
    destroy_tree(&n11);
    // destroy_tree(&n1);
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
    if ((root != n2) ||
        (root->left_child != n1) ||
        (root->right_child != n4) ||
        (root->right_child->left_child != n3) |
            (root->right_child->right_child != n5))
    {
        printf("[LOG] error result\n");
        return false;
    }

    destroy_tree(&root);
    return true;
}

bool test_load_prf_expr()
{

    char line[] = "+ 2 3";
    Node *r1 = load_prf_expr(line);
    if (!r1 || (r1->isRoot != true) ||
        strcmp(r1->value, "+") ||
        strcmp(r1->left_child->value, "2") ||
        strcmp(r1->right_child->value, "3") ||
        r1->left_child->sSheet != true || r1->right_child->sSheet != true)
    {
        if(r1)
        {
            destroy_tree(&r1);
        }
        printf("[LOG] no solutioned 2 + 3\n");
        return false;
    }
    else
    {
        destroy_tree(&r1);
    }
    Node *res1 = load_prf_expr("/ * 5 - 14 * 4 2 2");
    if (!res1 || strcmp(res1->value, "/"))
    {
        if(res1)
        {
            destroy_tree(&res1);
        }
        printf("[LOG] no complite test from manual\n");
        return false;
    }
    else
    {
        destroy_tree(&res1);
    }

    Node *r2 = load_prf_expr("(+ 3 3)");
    if (r2)
    {
        destroy_tree(&r2);
        printf("[LOG] no warning on wrong line\n");
        return false;
    }
    Node *r3 = load_prf_expr("+ + +");
    if (r3)
    {
        destroy_tree(&r3);
        printf("[LOG] no NULL on wrong line\n");
        return false;
    }
    
    Node *r4 = load_prf_expr("+ * / 4 2 3 * 5 6");
    if (!r4)
    {
        printf("[LOG] no create r4\n");
        return false;
    }
    else
    {
        destroy_tree(&r4);
    }
    
    Node *r5 = load_prf_expr("+ * / 4 2 3 5 6");
    if (r5)
    {
        destroy_tree(&r5);
        printf("[LOG] no NULL on wrong line\n");
        return false;
    }

    Node *r6 = load_prf_expr("            ");
    if (r6)
    {
        destroy_tree(&r6);
        printf("[LOG] no warning on wrong request\n");
        return false;
    }
    return true;
}

bool test_load_rst_expr()
{
    char l0[] = "3 2 +";
    Node *r0 = load_pst_expr(l0);
    if (!r0 || r0->isRoot != true ||
        strcmp(r0->value, "+") ||
        strcmp(r0->left_child->value, "3") ||
        strcmp(r0->right_child->value, "2"))
    {
        printf("[LOG] no create basic case\n");
        if (r0)
        {
            destroy_tree(&r0);
        }
        return false;
    }
    else
    {
        destroy_tree(&r0);
    }

    char l1[] = "5 14 4 2 * - * 2 /";
    Node *r1 = load_pst_expr(l1);

    if (!r1)
    {
        printf("[LOG] no solution manual\n");
        return false;
    }
    else
    {
        destroy_tree(&r1);
    }
    char t2[] = "            ";
    Node *r2 = load_prf_expr(t2);
    if (r2)
    {
        destroy_tree(&r2);
        printf("[LOG] no warning on wrong request\n");
        return false;
    }
    char t3[] = "j! 2";
    Node *r3 = load_pst_expr(t3);
    if (!r3)
    {
        printf("[LOG] error mb\n");
    }
    else
    {
        destroy_tree(&r3);
    }

    return true;
}

bool test_parse_expr()
{
    char t1[] = "2 + 3 / 3 @ 3! - a * 5";

    return true;
}

bool test_save_prf()
{
    char t1[] = "+ 2 3";
    Node *test1 = load_prf_expr(t1);
    massiveToken r1 = save_prf(test1);
    if (r1.data == NULL || strcmp(r1.data, t1))
    {
        printf("[LOG] error + 2 3\n");
        if (r1.data)
        {
            free(r1.data);
        }
        if (test1)
        {
            destroy_tree(&test1);
        }
        return false;
    }
    else
    {
        if (r1.data)
        {
            free(r1.data);
        }
        destroy_tree(&test1);
    }

    char t2[] = "/ * 5 - 14 * 4 2 2";
    Node *test2 = load_prf_expr(t2);
    massiveToken r2 = save_prf(test2);
    if (r2.data == NULL || strcmp(r2.data, t2))
    {
        printf("[LOG] no complit manual\n");
        if (r2.data)
        {
            free(r2.data);
        }
        if (test2)
        {
            destroy_tree(&test2);
        }
        return false;
    }
    else
    {
        if (r2.data)
        {
            free(r2.data);
        }
        if (test2)

        {
            destroy_tree(&test2);
        }
    }
    return true;
}

bool test_save_pst()
{
    char t1[] = "3 2 +";
    Node *test1 = load_pst_expr(t1);
    massiveToken res1 = save_pst(test1);
    if (!test1 || !res1.data || strcmp(t1, res1.data))
    {
        printf("[LOG] basic case wrong\n");
        if (test1)
        {
            destroy_tree(&test1);
        }
        if (res1.data)
        {
            free(res1.data);
        }
        return false;
    }
    else
    {
        free(res1.data);
        destroy_tree(&test1);
    }

    char t2[] = "5 14 4 2 * - * 2 /";
    Node *test2 = load_pst_expr(t2);
    massiveToken res2 = save_pst(test2);
    if (!test2 || !res2.data || strcmp(res2.data, t2))
    {
        printf("[LOG] no complit manual\n");
        if (test2)
        {
            destroy_tree(&test2);
        }
        return false;
    }
    else
    {
        destroy_tree(&test2);
        free(res2.data);
    }
    return true;
}

int main()
{

    if(!test_memory_leaks())
    {
        printf("[-] memory leaks");
        exit(1);
    }
    else
    {
        printf("[-] memory leaks");
    }
    if (!test_reverse())
    {
        printf("[-] test_reverse\n");
        exit(1);
    }
    else
    {
        printf("[+] test_reverse\n");
    }
    if (!test_reverse_sequence())
    {
        printf("[-] test_reverse_sequence\n");
        exit(1);
    }
    else
    {
        printf("[+] test_reverse_words\n");
    }
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
    if (!test_load_prf_expr())
    {
        printf("[-] load_prf_expr\n");
        exit(1);
    }
    else
    {
        printf("[+] load_prf_expr\n");
    }
    if (!test_load_rst_expr())
    {
        printf("[-] load_pst\n");
    }
    else
    {
        printf("[+] load_pst\n");
    }
    if (!test_save_prf())
    {
        printf("[-] save_prf\n");
        exit(1);
    }
    else
    {
        printf("[+] save_prf\n");
    }
    if (!test_save_pst())
    {
        printf("[-] save_pst\n");
        exit(1);
    }
    else
    {
        printf("[+] save_pst\n");
    }
}