#include "deter.h"



createNode(char *value)
{
    
}

unsigned char len_value(char *start)
{
    unsigned char len = 0;
    while(len < 11 && isalnum(*(start+len)) )
    {
         len++;
    }
    return len;
}

Node *parse_expr(char *line)
{
    while(*line != '\0' && *line != '\n')
    {
        while(isspace(*line))
        {
            line++;
        }
        int len = len_value(line);
        if(len == 11)
        {
            // обработка ошибки
            ;
        }
        
        createNode();

    }
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