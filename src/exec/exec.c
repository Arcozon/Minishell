#include "../../inc/minishell.h"
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int    ft_open_file_(char *str, int oflag, int mode)
{
    int fd;

    fd = open(str, oflag, mode);
    if (fd == -1)
        perror(str);
    return (fd);
}

int    ft_open_file(char *name, int *fd, int oflag, int mode)
{
    int    tmp;

    tmp = ft_open_file_(name, oflag, mode);
    if (tmp == -1)
        return (1);
    if (*fd > 2)
        close(*fd);
    *fd = tmp;
    return (0);
}

int   ft_heredoc(void)
{
    //stuff to do
    return (0);
}
int    process_file(t_lcmd *cmd)
{
    t_ioe_put    *tmp;

    tmp = cmd->ioe_put;
    while (tmp)
    {
        if (tmp->type == INPUT_REDIR && !ft_open_file(tmp->name, &cmd->input, O_RDONLY, 0))
            ;
        else if (tmp->type == OUTPUT_REDIR && !ft_open_file(tmp->name, &cmd->output, O_CREAT | O_WRONLY | O_TRUNC, 0622))
            ;
        else if (tmp->type == OUTPUT_HAPPEND_REDIR && !ft_open_file(tmp->name, &cmd->output, O_CREAT | O_WRONLY | O_APPEND, 0622))
            ;
        else if (tmp->type == INPUT_HEREDOC && !ft_heredoc())
            ;
        else
            return (1);
        tmp = tmp->next;
    }
    return (0);
}

void    set_up_dup(t_lcmd *cmd, int p[2], int lastfd)
{
    if (cmd->input != STDIN_FILENO)
        dup2(cmd->input, STDIN_FILENO);
    else
    {
        dup2(lastfd, STDIN_FILENO);
        cmd->input = lastfd;
    }
    if (cmd->output != STDOUT_FILENO)
        dup2(cmd->output, STDOUT_FILENO);
    else
    {
        dup2(p[1], STDOUT_FILENO);
        cmd->output = p[1];
    }
    if (cmd->error != STDERR_FILENO)
        dup2(cmd->error, STDERR_FILENO);
}

void    ft_child(void)
{
    ;//TO-DO
}

void    process_cmd(t_lcmd *cmd, t_env *envdeeznuts)
{
    int    p[2];
    int    lastdeeznuts;
    t_lcmd *tmp;

    lastdeeznuts = 0;
    tmp = cmd;
    while (tmp)
    {
        process_file(tmp);
        if (pipe(p) == -1)
            exit(73);
        ft_child();
        close(p[1]);
        if (lastdeeznuts > 2)
            close(lastdeeznuts);
        lastdeeznuts = p[0];
        tmp = tmp->next;
    }
}

void    process_tree(t_node *tree, t_env *envdeeznuts)
{
    if (!tree)
        exit(69);
    if (tree->lcmd && !tree->opp)
        process_cmd(tree->lcmd, envdeeznuts);
    else if (!tree->lcmd && tree->opp)
    {
        process_tree(tree->opp->r_node, envdeeznuts);
        if (tree->opp->logical_opp == AND)
        {
            if (!g_cmd_exit)
                process_tree(tree->opp->l_node, envdeeznuts);
        }
        else if (tree->opp->logical_opp == OR)
            if (g_cmd_exit)
                process_tree(tree->opp->l_node, envdeeznuts);
    }
    else
        exit(69);
}
