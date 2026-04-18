#include "func.h"

bool test_memory_leaks()
{
    Node *ptr1 = createNode("-");
    stack *pointers = NULL;
    push(&pointers, ptr1);
    push(&pointers, ptr1);
    push(&pointers, ptr1);
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

    massiveToken res1 = save_prf(root);
    if (!res1.data || strcmp(res1.data, "+ 3 / 4 2"))
    {
        printf("[LOG] i cant understand what that sheet\n");
        if (res1.data)
        {
            free(res1.data);
            destroy_tree(&root);
        }
        return false;
    }
    free(res1.data);
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
        if (r1)
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
        if (res1)
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

    Node *r7 = load_prf_expr("- + 2 / 3 @ 3 ! 3 * a 5");
    if (!r7)
    {
        printf("[LOG] no create correct tree\n");
        return false;
    }
    massiveToken res7 = save_prf(r7);
    destroy_tree(&r7);
    if (!res7.data)
    {
        printf("[LOG] no write correct prf tree\n");
        return false;
    }
    if (strcmp(res7.data, "- + 2 / 3 @ 3 ! 3 * a 5"))
    {
        printf("[LOG] no reverse function\n");
        free(res7.data);
        return false;
    }
    free(res7.data);

    Node *r8 = load_prf_expr("- * 3 + * 4 4 / - 3 2 2 1");
    if(!r8)
    {
        printf("[LOG] bug in prf\n");
        return false;
    }
    massiveToken res8 = save_prf(r8);
    if (!res8.data || strcmp(res8.data, "- * 3 + * 4 4 / - 3 2 2 1"))
    {
        printf("[LOG] have error in prf\n");
        if (res8.data)
        {
            free(res8.data);
        }
        destroy_tree(&r8);
        return false;
    }
    free(res8.data);
    destroy_tree(&r8);

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
    char t3[] = "! 2";
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
    // char t1[] = "2 + 3 / 3 @ 3! - a * 5";
    // Node *tree1 = parse_expr(t1);
    // if (!tree1)
    // {
    //     printf("[LOG] no create basic tree1\n");
    //     return false;
    // }
    // else
    // {
    //     massiveToken res1;
    //     res1 = save_prf(tree1);
    //     if (strcmp(res1.data, "- + 2 / 3 @ 3 ! 3 * a 5"))
    //     {
    //         free(res1.data);
    //         destroy_tree(&tree1);
    //         printf("[LOG] error prf form\n");
    //         return false;
    //     }
    //     free(res1.data);
    //     res1.len = 0;
    //     res1.capacity = 0;
    //     res1 = save_pst(tree1);
    //     destroy_tree(&tree1);
    //     if (strcmp(res1.data, "2 3 3 3 ! @ / + a 5 * -"))
    //     {
    //         printf("[LOG] error pst form\n");
    //         free(res1.data);
    //         return false;
    //     }
    //     free(res1.data);
    // }

    // char t2[] = "2 + (3 - 2) * 5";
    // Node *tree2 = parse_expr(t2);
    // if (!tree2)
    // {
    //     printf("[LOG] no worked barked\n");
    //     return false;
    // }
    // else
    // {
    //     massiveToken res2;
    //     res2 = save_prf(tree2);
    //     destroy_tree(&tree2);
    //     if (!res2.data)
    //     {
    //         printf("[LOG] error create tree2 prf\n");
    //         return false;
    //     }
    //     if (strcmp(res2.data, "+ 2 * - 3 2 5"))
    //     {
    //         printf("[LOG] error create basic brackets\n");
    //         free(res2.data);
    //         return false;
    //     }
    //     free(res2.data);
    // }

    // char t3[] = "(2 + 3) / 2";
    // Node *tree3 = parse_expr(t3);
    // if (!tree3)
    // {
    //     printf("[LOG] no create tree3\n");
    //     return false;
    // }
    // else
    // {
    //     massiveToken res3 = save_prf(tree3);
    //     destroy_tree(&tree3);
    //     if (!res3.data)
    //     {
    //         printf("[LOG] uncorrect tree\n");
    //         return false;
    //     }
    //     if (strcmp(res3.data, "/ + 2 3 2"))
    //     {
    //         free(res3.data);
    //         printf("[LOG] doesn't much with answer\n");
    //         return false;
    //     }
    //     free(res3.data);
    // }
    
    char t4[] = "3*(4 * 4 + (3 - 2) / 2) - 1";
    Node *tree4 = parse_expr(t4);
    if (!tree4)
    {
        printf("[LOG] no created 2 barkets, tree4\n");
        return false;
    }
    else
    {
        massiveToken res4 = save_prf(tree4);
        destroy_tree(&tree4);
        if (!res4.data)
        {
            printf("[LOG] no correct tree for prf\n");
            return false;
        }
        if (strcmp(res4.data, "- * 3 + * 4 4 / - 3 2 2 1"))
        {
            free(res4.data);
            printf("[LOG] does not mutch with reference tree4\n");
            return false;
        }
        free(res4.data);
    }

    char t5[] = "((a + b) / c+2)*43!";
    Node *tree5 = parse_expr(t5);
    if (!tree5)
    {
        printf("[LOG] no created tree5\n");
        return false;
    }
    else
    {
        massiveToken res5 = save_prf(tree5);
        destroy_tree(&tree5);
        if (!res5.data)
        {
            printf("[LOG] cant to make res5\n");
            return false;
        }
        if (strcmp(res5.data, "* + / + a b c 2 ! 43"))
        {
            free(res5.data);
            printf("[LOG] does not mutch with reference tree5\n");
            return false;
        }
        free(res5.data);
    }
    char t6[] = "((3+3) / 2)";
    Node *tree6 = parse_expr(t6);
    if (!tree6)
    {
        printf("[LOG] wasn't created tree6\n");
        return false;
    }
    else
    {
        massiveToken res6 = save_prf(tree6);
        destroy_tree(&tree6);
        if (!res6.data)
        {
            printf("[LOG] wrong create tree6\n");
            return false;
        }
        if (strcmp(res6.data, "/ + 3 3 2"))
        {
            printf("[LOG] doesn't match tree6 with reference\n");
            free(res6.data);
            return false;
        }
        free(res6.data);
    }

    char t7[] = "(2+3) - 2";
    Node *tree7 = parse_expr(t7);
    if(!tree7)
    {
        printf("[LOG] no created tree7\n");
        return false;
    }
    else
    {
        massiveToken res7 = save_prf(tree7);
        destroy_tree(&tree7);
        if(!res7.data)
        {
            printf("[LOG] wrong tree7\n");
            return false;
        }
        if(strcmp(res7.data,"- + 2 3 2"))
        {
            free(res7.data);
            printf("[LOG] doesn't match with reference tree7\n");
            return false;
        }
        free(res7.data);
    }
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
    char t1[] = "10 5 + 2 *";
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

    char t2[] = "a 2 ^ b 2 ^ +";
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

bool test_eval()
{
    long long result = 0;
    VARS var_b = {.next = NULL, .value = 3, .name = "b"};
    VARS var_a = {.next = &var_b, .value = 7, .name = "a"};

    if (eval(NULL, &var_a, &result))
    {
        printf("[LOG] eval(NULL) must be false\n");
        return false;
    }

    Node *tmp = load_prf_expr("+ 1 2");
    if (!tmp)
    {
        printf("[LOG] tmp tree not created\n");
        return false;
    }
    if (eval(tmp, &var_a, NULL))
    {
        printf("[LOG] eval with NULL result must be false\n");
        destroy_tree(&tmp);
        return false;
    }
    destroy_tree(&tmp);

    Node *n1 = load_prf_expr("42");
    if (!n1 || !eval(n1, &var_a, &result) || result != 42)
    {
        printf("[LOG] literal eval failed\n");
        if (n1)
        {
            destroy_tree(&n1);
        }
        return false;
    }
    destroy_tree(&n1);

    Node *n2 = load_prf_expr("a");
    if (!n2 || !eval(n2, &var_a, &result) || result != 7)
    {
        printf("[LOG] variable eval failed\n");
        if (n2)
        {
            destroy_tree(&n2);
        }
        return false;
    }
    destroy_tree(&n2);

    Node *n3 = load_prf_expr("unknown");
    if (!n3 || eval(n3, &var_a, &result))
    {
        printf("[LOG] unknown variable must fail\n");
        if (n3)
        {
            destroy_tree(&n3);
        }
        return false;
    }
    destroy_tree(&n3);

    Node *n4 = load_prf_expr("+ 5 6");
    if (!n4 || !eval(n4, NULL, &result) || result != 11)
    {
        printf("[LOG] add eval failed\n");
        if (n4)
        {
            destroy_tree(&n4);
        }
        return false;
    }
    destroy_tree(&n4);

    Node *n5 = load_prf_expr("- 5 6");
    if (!n5 || !eval(n5, NULL, &result) || result != -1)
    {
        printf("[LOG] sub eval failed\n");
        if (n5)
        {
            destroy_tree(&n5);
        }
        return false;
    }
    destroy_tree(&n5);

    Node *n6 = load_prf_expr("* 3 6");
    if (!n6 || !eval(n6, NULL, &result) || result != 18)
    {
        printf("[LOG] mul eval failed\n");
        if (n6)
        {
            destroy_tree(&n6);
        }
        return false;
    }
    destroy_tree(&n6);

    Node *n7 = load_prf_expr("/ 7 2");
    if (!n7 || !eval(n7, NULL, &result) || result != 3)
    {
        printf("[LOG] div eval failed\n");
        if (n7)
        {
            destroy_tree(&n7);
        }
        return false;
    }
    destroy_tree(&n7);

    Node *n8 = load_prf_expr("/ 7 0");
    if (!n8 || !eval(n8, NULL, &result) || result != 0)
    {
        printf("[LOG] div by zero branch failed\n");
        if (n8)
        {
            destroy_tree(&n8);
        }
        return false;
    }
    destroy_tree(&n8);

    Node *n9 = createNode("%%");
    Node *n9l = createNode("7");
    Node *n9r = createNode("4");
    if (!n9 || !n9l || !n9r)
    {
        if (n9)
        {
            destroy_tree(&n9);
        }
        if (n9l)
        {
            destroy_tree(&n9l);
        }
        if (n9r)
        {
            destroy_tree(&n9r);
        }
        printf("[LOG] mod nodes not created\n");
        return false;
    }
    n9->isRoot = true;
    n9->left_child = n9l;
    n9->right_child = n9r;
    n9->sSheet = false;
    n9l->parent = n9;
    n9r->parent = n9;
    if (!eval(n9, NULL, &result) || result != 3)
    {
        printf("[LOG] mod eval failed\n");
        destroy_tree(&n9);
        return false;
    }
    destroy_tree(&n9);

    Node *n10 = createNode("%%");
    Node *n10l = createNode("7");
    Node *n10r = createNode("0");
    if (!n10 || !n10l || !n10r)
    {
        if (n10)
        {
            destroy_tree(&n10);
        }
        if (n10l)
        {
            destroy_tree(&n10l);
        }
        if (n10r)
        {
            destroy_tree(&n10r);
        }
        printf("[LOG] mod zero nodes not created\n");
        return false;
    }
    n10->isRoot = true;
    n10->left_child = n10l;
    n10->right_child = n10r;
    n10->sSheet = false;
    n10l->parent = n10;
    n10r->parent = n10;
    if (!eval(n10, NULL, &result) || result != 0)
    {
        printf("[LOG] mod by zero branch failed\n");
        destroy_tree(&n10);
        return false;
    }
    destroy_tree(&n10);

    Node *n11 = load_prf_expr("^ 2 10");
    if (!n11 || !eval(n11, NULL, &result) || result != 1024)
    {
        printf("[LOG] pow eval failed\n");
        if (n11)
        {
            destroy_tree(&n11);
        }
        return false;
    }
    destroy_tree(&n11);

    Node *n12 = load_prf_expr("^ 5 0");
    if (!n12 || !eval(n12, NULL, &result) || result != 1)
    {
        printf("[LOG] pow zero exp failed\n");
        if (n12)
        {
            destroy_tree(&n12);
        }
        return false;
    }
    destroy_tree(&n12);

    Node *n13 = load_prf_expr("^ 2 63");
    if (!n13 || eval(n13, NULL, &result))
    {
        printf("[LOG] pow overflow must fail\n");
        if (n13)
        {
            destroy_tree(&n13);
        }
        return false;
    }
    destroy_tree(&n13);

    Node *n14 = load_prf_expr("@ 18 24");
    if (!n14 || !eval(n14, NULL, &result) || result != 6)
    {
        printf("[LOG] gcd eval failed\n");
        if (n14)
        {
            destroy_tree(&n14);
        }
        return false;
    }
    destroy_tree(&n14);

    Node *n15 = load_prf_expr("@ 0 0");
    if (!n15 || !eval(n15, NULL, &result) || result != 0)
    {
        printf("[LOG] gcd zero-zero failed\n");
        if (n15)
        {
            destroy_tree(&n15);
        }
        return false;
    }
    destroy_tree(&n15);

    Node *n16 = load_prf_expr("# 6 15");
    if (!n16 || !eval(n16, NULL, &result) || result != 30)
    {
        printf("[LOG] lcm eval failed\n");
        if (n16)
        {
            destroy_tree(&n16);
        }
        return false;
    }
    destroy_tree(&n16);

    Node *n17 = load_prf_expr("# 0 15");
    if (!n17 || !eval(n17, NULL, &result) || result != 0)
    {
        printf("[LOG] lcm zero branch failed\n");
        if (n17)
        {
            destroy_tree(&n17);
        }
        return false;
    }
    destroy_tree(&n17);

    Node *n18 = load_prf_expr("# 2147483647 2147483646");
    if (!n18 || eval(n18, NULL, &result))
    {
        printf("[LOG] lcm overflow must fail\n");
        if (n18)
        {
            destroy_tree(&n18);
        }
        return false;
    }
    destroy_tree(&n18);

    Node *n19 = createNode("!");
    Node *n19l = createNode("5");
    if (!n19 || !n19l)
    {
        if (n19)
        {
            destroy_tree(&n19);
        }
        if (n19l)
        {
            destroy_tree(&n19l);
        }
        printf("[LOG] factorial nodes not created\n");
        return false;
    }
    n19->isRoot = true;
    n19->left_child = n19l;
    n19->sSheet = false;
    n19l->parent = n19;
    if (!eval(n19, NULL, &result) || result != 120)
    {
        printf("[LOG] factorial eval failed\n");
        destroy_tree(&n19);
        return false;
    }
    destroy_tree(&n19);

    Node *n20 = createNode("!");
    Node *n20l = createNode("0");
    if (!n20 || !n20l)
    {
        if (n20)
        {
            destroy_tree(&n20);
        }
        if (n20l)
        {
            destroy_tree(&n20l);
        }
        printf("[LOG] factorial zero nodes not created\n");
        return false;
    }
    n20->isRoot = true;
    n20->left_child = n20l;
    n20->sSheet = false;
    n20l->parent = n20;
    if (!eval(n20, NULL, &result) || result != 1)
    {
        printf("[LOG] factorial zero failed\n");
        destroy_tree(&n20);
        return false;
    }
    destroy_tree(&n20);

    Node *n21 = createNode("!");
    Node *n21l = createNode("21");
    if (!n21 || !n21l)
    {
        if (n21)
        {
            destroy_tree(&n21);
        }
        if (n21l)
        {
            destroy_tree(&n21l);
        }
        printf("[LOG] factorial overflow nodes not created\n");
        return false;
    }
    n21->isRoot = true;
    n21->left_child = n21l;
    n21->sSheet = false;
    n21l->parent = n21;
    if (eval(n21, NULL, &result))
    {
        printf("[LOG] factorial overflow guard must fail\n");
        destroy_tree(&n21);
        return false;
    }
    destroy_tree(&n21);

    Node *right_fact = createNode("!");
    Node *arg = createNode("4");
    if (!right_fact || !arg)
    {
        if (right_fact)
        {
            destroy_tree(&right_fact);
        }
        if (arg)
        {
            destroy_tree(&arg);
        }
        printf("[LOG] no create unary right branch nodes\n");
        return false;
    }
    right_fact->isRoot = true;
    right_fact->right_child = arg;
    arg->parent = right_fact;
    right_fact->sSheet = false;
    if (!eval(right_fact, NULL, &result) || result != 24)
    {
        printf("[LOG] unary right child branch failed\n");
        destroy_tree(&right_fact);
        return false;
    }
    destroy_tree(&right_fact);

    Node *bad_literal = createNode("12x");
    if (!bad_literal || eval(bad_literal, NULL, &result))
    {
        printf("[LOG] invalid literal must fail\n");
        if (bad_literal)
        {
            destroy_tree(&bad_literal);
        }
        return false;
    }
    destroy_tree(&bad_literal);

    destroy_tree(&bad_literal);
    if (bad_literal != NULL)
    {
        printf("[LOG] destroy_tree must set NULL\n");
        return false;
    }

    return true;
}

int main()
{

    if (!test_memory_leaks())
    {
        printf("[-] memory leaks");
        exit(1);
    }
    else
    {
        printf("[+] memory leaks\n");
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
    if (!test_parse_expr())
    {
        printf("[-] parse_espr\n");
        exit(1);
    }
    else
    {
        printf("[+] parse_espr\n");
    }
    if (!test_eval())
    {
        printf("[-] test_eval\n");
        exit(1);
    }
    else
    {
        printf("[+] test_eval\n");
    }
    printf("COMPLITE\n");
    exit(0);
}
