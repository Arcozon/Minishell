#include "../../inc/minishell.h"
#include "../../inc/get_next_line.h"
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

    if (*fd > 2)
        close(*fd);
    tmp = ft_open_file_(name, oflag, mode);
    if (tmp == -1)
        return (1);
    *fd = tmp;
    return (0);
}

int ft_write_to_fd(int fd, char *str, int len)
{
    if (write(fd, str, len) != len)
        return (1);
    return (0);
}

int ft_heredoc_sub(t_lcmd *cmd, t_ioe_put *ioe)
{
    char    *buf;
    int    len2;
    int    len;

    len = ft_strlen(ioe->name);
    write(1, "> ", 2);
    while (1)
    {
        buf = get_next_line(STDIN_FILENO);
        if (!buf)
        {
            write(2, "Warning : heredoc delimited by EOF (wanted '", 44);
            (write(2, ioe->name, len), write(2, "')\n", 3));
            return (free(buf), 1);
        }
        len2 = ft_strlen(buf) - 1;
        if (len == len2 && !ft_strncmp(buf, ioe->name, len))
                break ;
        if (len2 + 1 > 0)
            write(1, "> ", 2);
        if (ft_write_to_fd(cmd->input, buf, len2 + 1))
            return (free(buf), 1);
        free(buf);
    }
    return (free(buf), 0);
}

int   ft_heredoc(t_lcmd *cmd, t_ioe_put *ioe)
{
    if (ft_open_file(".heredoc", &cmd->input, O_CREAT | O_WRONLY | O_TRUNC, 0644))
        return (1);
    if (ft_heredoc_sub(cmd, ioe))
        return (1);
    if (ft_open_file(".heredoc", &cmd->input, O_RDONLY, 0))
        return (1);
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
        else if (tmp->type == INPUT_HEREDOC && !ft_heredoc(cmd, tmp))
            ;
        else
            return (1);
        tmp = tmp->next;
    }
    return (0);
}

void    set_up_dup(t_lcmd *cmd, int p1, int lastfd)
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
        dup2(p1, STDOUT_FILENO);
        cmd->output = p1;
    }
    if (cmd->error != STDERR_FILENO)
        dup2(cmd->error, STDERR_FILENO);
}

char	*ft_strjoin_weq(char const *s1, char const *s2)
{
	char	*ptr;
	int		i;
	int		iptr;

	if (!s1 && !s2)
		return (0);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	i = 0;
	iptr = 0;
	ptr = malloc((ft_strlen(s1) + ft_strlen(s2) + 1 + 1) * sizeof(char));
	if (ptr == 0)
		return (0);
	while (s1[i])
		ptr[iptr++] = s1[i++];
	ptr[iptr++] = '=';
	i = 0;
	while (s2[i])
		ptr[iptr++] = s2[i++];
	ptr[iptr] = '\0';
	return (ptr);
}

int    t_env_len(t_env *env)
{
    int    n;

    n = 0;
    while (env)
    {
        n++;
        env = env->next;
    }
    return (n);
}

char    **t_env_to_charr(t_env *env)
{
    int    len;
    int    i;
    char    **out;

    if (!env)
        return (0);
    len = t_env_len(env);
    i = 0;
    out = malloc(sizeof(char *) * (len + 1));
    if (!out)
        exit(76);
    while (i < len)
    {
        out[i] = ft_strjoin_weq(env->var_name, env->content);
        if (!out[i])
            exit(78);
        i++;
        env = env->next;
    }
    out[i] = 0;
    return (out);
}

void    ft_free_strr(char **str)
{
    int    i;

    i = 0;
    while (str[i])
    {
        free(str[i]);
        i++;
    }
    free(str);
}


void    ft_child(t_lcmd *cmd, int p1, int lastfd, t_env *env)
{
    char    **envstrr;

    cmd->pid = fork();
    if (cmd->pid == -1)
        exit(75);
    else if (cmd->pid == 0)
    {
        set_up_dup(cmd, p1, lastfd);
        envstrr = t_env_to_charr(env);
        if (!envstrr)
            exit(77);
        execve(*(cmd->cmd), cmd->cmd, envstrr);
        perror(*(cmd->cmd));
        ft_free_strr(envstrr);
    }
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
        ft_child(tmp, p[1], lastdeeznuts, envdeeznuts);
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
