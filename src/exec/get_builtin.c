#include "../../inc/minishell.h"
#define BUILTINNBR 7
#define BUILTINSPLIT 3

static char *builtin[] = {"cd", "export", "unset",
    "pwd", "echo", "env", "exit"};

static int (*bi_func[])() = {bi_cd, bi_export, bi_unset,
    bi_pwd, bi_echo, bi_env};

int ft_strcmp(char *str1, char *str2)
{
    while (*str1 && *str2 && (unsigned char)*str1 == (unsigned char)*str2)
    {
        str1++;
        str2++;
    }
    return ((unsigned char)*str1 - (unsigned char)*str2);
}

void ft_exec_builtin(t_lcmd *cmd, t_env *env, int nbr)
{
    if (nbr == 0)
    {
        if ((bi_func[nbr])(cmd, env))
            exit(747);
    } 
    else if (nbr > 0 && nbr <= BUILTINSPLIT)
    {
        if ((bi_func[nbr])(cmd, &env))
            exit(748);
    }
    else if (nbr > BUILTINSPLIT && nbr < BUILTINNBR - 1)
    {
        if ((bi_func[nbr])(cmd, env))
            exit(749);
    }
    else if (nbr == BUILTINNBR - 1)
        bi_exit();
}

int ft_is_builtin(t_lcmd *cmd, t_env *env)
{
    int i = 0;

    while (i < BUILTINNBR)
    {
        if (cmd->cmd && ft_strcmp(*(cmd->cmd), builtin[i]) == 0)
        {
            ft_exec_builtin(cmd, env, i);
            return (1);
            break ;
        }
        i++;
    }
    return (0);
}
