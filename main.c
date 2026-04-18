#include "deter.h"
#include "func.h"
#include <ctype.h>
#include <unistd.h>

Node *current_tree = NULL;

static int interactive;

static void hint(const char *msg)
{
    if (interactive)
    {
        fprintf(stderr, "%s\n", msg);
    }
}

static void print_welcome(void)
{
    if (!interactive)
    {
        return;
    }
    fprintf(stderr,
            "\n"
            "  Вычислитель выражений (дерево разбора)\n"
            "  ─────────────────────────────────────\n"
            "  Вводите команду в строке. Примеры ниже — команда «help».\n"
            "  Выход: quit  или  exit  или  Ctrl+D\n\n");
}

static void print_help(void)
{
    fprintf(stderr,
            "\n"
            "  Команды (аргумент — всё после первого пробела до конца строки):\n\n"
            "  parse <выражение>     инфикс:  parse 2 + 3 * x\n"
            "  load_prf <строка>     префикс с пробелами:  load_prf + 2 3\n"
            "  load_pst <строка>     постфикс:  load_pst 2 3 +\n"
            "  save_prf              напечатать дерево в префиксе (stdout)\n"
            "  save_pst              напечатать в постфиксе (stdout)\n"
            "  eval [a=1,b=2,...]    вычислить; для каждой буквы в выражении нужно a=число\n"
            "                        чисто числовое — можно:  eval\n\n"
            "  Подсказки:\n"
            "  • Сначала загрузите выражение (parse / load_*), потом save_* или eval.\n"
            "  • success / incorrect / not_loaded / eval_error — в stdout; число — только при успешном eval.\n\n");
}

static void print_prompt(void)
{
    if (interactive)
    {
        fputs("> ", stdout);
        fflush(stdout);
    }
}

static int line_is_blank(const char *s)
{
    if (!s)
    {
        return 1;
    }
    for (; *s; s++)
    {
        if (!isspace((unsigned char)*s))
        {
            return 0;
        }
    }
    return 1;
}

int main(void)
{
    char line[1024];
    interactive = isatty(STDIN_FILENO);
    print_welcome();

    while (1)
    {
        print_prompt();
        if (!fgets(line, sizeof(line), stdin))
        {
            if (interactive)
            {
                fputs("\n", stderr);
            }
            break;
        }
        if (line_is_blank(line))
        {
            hint("  (пустая строка) Введите команду или: help");
            continue;
        }

        char *cmd = strtok(line, " \t\n");
        if (!cmd)
        {
            continue;
        }

        if (strcmp(cmd, "help") == 0 || strcmp(cmd, "?") == 0)
        {
            print_help();
            continue;
        }
        if (strcmp(cmd, "quit") == 0 || strcmp(cmd, "exit") == 0 || strcmp(cmd, "q") == 0)
        {
            hint("  Выход.");
            break;
        }

        if (strcmp(cmd, "parse") == 0)
        {
            char *expr = strtok(NULL, "\n");
            if (!expr)
            {
                hint("  Нужно выражение:  parse 2 + (3 - 1) * x");
                printf("incorrect\n");
                continue;
            }
            Node *tree = parse_expr(expr);
            if (tree)
            {
                destroy_tree(&current_tree);
                current_tree = tree;
                hint("  Дерево построено. Дальше: save_prf, save_pst или eval");
                printf("success\n");
            }
            else
            {
                hint("  Не удалось разобрать. Проверьте скобки, операторы и имена.");
                printf("incorrect\n");
            }
        }
        else if (strcmp(cmd, "load_prf") == 0)
        {
            char *expr = strtok(NULL, "\n");
            if (!expr)
            {
                hint("  Нужна строка:  load_prf + * 2 3 4");
                printf("incorrect\n");
                continue;
            }
            Node *tree = load_prf_expr(expr);
            if (tree)
            {
                destroy_tree(&current_tree);
                current_tree = tree;
                hint("  Загружено из префикса. Дальше: save_pst или eval");
                printf("success\n");
            }
            else
            {
                hint("  Неверная префиксная запись (операнды/операторы).");
                printf("incorrect\n");
            }
        }
        else if (strcmp(cmd, "load_pst") == 0)
        {
            char *expr = strtok(NULL, "\n");
            if (!expr)
            {
                hint("  Нужна строка:  load_pst 2 3 +");
                printf("incorrect\n");
                continue;
            }
            Node *tree = load_pst_expr(expr);
            if (tree)
            {
                destroy_tree(&current_tree);
                current_tree = tree;
                hint("  Загружено из постфикса. Дальше: save_prf или eval");
                printf("success\n");
            }
            else
            {
                hint("  Неверная постфиксная запись.");
                printf("incorrect\n");
            }
        }
        else if (strcmp(cmd, "save_prf") == 0)
        {
            if (current_tree)
            {
                massiveToken res = save_prf(current_tree);
                printf("%s\n", res.data);
                free(res.data);
                hint("  (строка выше — префиксная запись)");
            }
            else
            {
                hint("  Сначала выполните parse, load_prf или load_pst.");
                printf("not_loaded\n");
            }
        }
        else if (strcmp(cmd, "save_pst") == 0)
        {
            if (current_tree)
            {
                massiveToken res = save_pst(current_tree);
                printf("%s\n", res.data);
                free(res.data);
                hint("  (строка выше — постфиксная запись)");
            }
            else
            {
                hint("  Сначала выполните parse, load_prf или load_pst.");
                printf("not_loaded\n");
            }
        }
        else if (strcmp(cmd, "eval") == 0)
        {
            char *vars_str = strtok(NULL, "\n");
            if (!current_tree)
            {
                hint("  Нет дерева: сначала parse / load_prf / load_pst.");
                printf("not_loaded\n");
                continue;
            }
            while (vars_str && isspace((unsigned char)*vars_str))
            {
                vars_str++;
            }
            VARS *vars = NULL;
            if (vars_str && *vars_str)
            {
                char *token = strtok(vars_str, ",");
                while (token)
                {
                    char *eq = strchr(token, '=');
                    if (!eq)
                    {
                        hint("  Ожидается имя=число, например:  a=1,b=2");
                        break;
                    }
                    *eq = '\0';
                    char *name = token;
                    while (*name == ' ')
                    {
                        name++;
                    }
                    char *end_name = name + strlen(name) - 1;
                    while (end_name > name && *end_name == ' ')
                    {
                        *end_name-- = '\0';
                    }
                    long long val = atoll(eq + 1);
                    VARS *new_var = (VARS *)malloc(sizeof(VARS));
                    if (!new_var)
                    {
                        break;
                    }
                    strncpy(new_var->name, name, sizeof(new_var->name) - 1);
                    new_var->name[sizeof(new_var->name) - 1] = '\0';
                    new_var->value = val;
                    new_var->next = vars;
                    vars = new_var;
                    token = strtok(NULL, ",");
                }
            }
            long long result = 0;
            if (eval(current_tree, vars, &result))
            {
                printf("%lld\n", result);
                if (interactive)
                {
                    fprintf(stderr, "  ↑ результат (целое число)\n");
                }
            }
            else
            {
                printf("eval_error\n");
                hint("  Не заданы переменные, переполнение или некорректное выражение.");
            }
            VARS *tmp;
            while (vars)
            {
                tmp = vars->next;
                free(vars);
                vars = tmp;
            }
        }
        else
        {
            fprintf(stderr, "  Неизвестная команда «%s». Введите: help\n", cmd);
        }
    }
    destroy_tree(&current_tree);
    return 0;
}
