#include "../../inc/minishell.h"
#include "../../inc/get_next_line.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/types.h>

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
    ioe->herename = strnrand(8);
	if (ft_open_file(ioe->herename, &cmd->input, O_CREAT | O_WRONLY | O_TRUNC, 0644))
		return (1);
	if (ft_heredoc_sub(cmd, ioe))
		return (1);
	if (ft_open_file(ioe->herename, &cmd->input, O_RDONLY, 0))
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
		else if (tmp->type == ERROR_REDIR && !ft_open_file(tmp->name, &cmd->output, O_CREAT | O_WRONLY | O_TRUNC, 0622))
			;
		else
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

void    set_up_dup(t_lcmd *cmd)
{
	if (cmd->input != STDIN_FILENO)
		dup2(cmd->input, STDIN_FILENO);
	if (cmd->output != STDOUT_FILENO)
		dup2(cmd->output, STDOUT_FILENO);
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

static int	ft_get_words(const char *s, char sep)
{
	int	length;
	int	words;

	length = 0;
	words = 0;
	while (*s)
	{
		if (*s == sep)
		{
			if (length > 0)
			{
				words++;
				length = 0;
			}
		}
		else
			length++;
		s++;
	}
	if (length)
		words++;
	return (words);
}

static void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*s_t;

	s_t = s;
	while (n--)
		s_t[n] = c;
	return (s);
}

void	*ft_calloc(size_t nmemb, size_t n)
{
	void	*ptr;

	if (!n)
		return (malloc(0));
	if (nmemb * n / n != nmemb)
		return (0);
	ptr = malloc(nmemb * n);
	if (ptr)
		ft_memset(ptr, 0, nmemb * n);
	return (ptr);
}

char	*ft_substr_split(char const *s, unsigned int start, size_t len)
{
	char	*out;
	size_t	i;
	size_t	len_s;

	if (!s)
		return (0);
	len_s = (unsigned int)ft_strlen(s);
	if (start <= 0 || start >= len_s)
		start = 0;
	if (len_s <= start)
		len = 0;
	if (len > len_s - start || len <= 0)
		len = len_s - start;
	i = 0;
	out = ft_calloc(len + 1, sizeof(char));
	if (out)
	{
		while (i < len && s[start + i])
		{
			out[i] = s[start + i];
			i++;
		}
	}
	return (out);
}

static int	ft_get_next_word(const char *s, char c, char **out)
{
	int	start;
	int	length;

	start = 0;
	length = 0;
	while (s[start] && s[start] == c)
		start++;
	while (s[start + length] && s[start + length] != c)
		length++;
	*out = ft_substr_split(s, start, length);
	return (start + length);
}

char	**ft_split(char const *s, char c)
{
	char	**out;
	int		size;
	int		i;
	int		ln;

	if (!s)
		return (0);
	size = ft_get_words(s, c);
	out = ft_calloc(size + 1, sizeof(char *));
	ln = 0;
	i = 0;
	if (!out)
		return (out);
	while (i < size)
	{
		ln += ft_get_next_word(s + ln, c, &out[i]);
		if (!out[i])
		{
			ft_free_strr(out);
			return (out);
		}
		i++;
	}
	out[i] = 0;
	return (out);
}

char	**ft_get_path(t_env *env)
{
	char	**path;

	if (!env)
		return (0);
	path =  0;
	while (env)
	{
		if (!ft_strcmp(env->var_name, "PATH"))
		{
			path = ft_split(env->content, ':');
			break ;
		}
		env = env->next;
	}
	return (path);
}

int	ft_strchr(char *str, char c)
{
	while (*str)
	{
		if (*str == c)
			return (1);
		str++;
	}
	return (0);
}

char	*ft_strcat_split(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*out;

	if (!s1)
		return (s2);
	if (!s2)
		return (s1);
	out = ft_calloc(sizeof(char), ft_strlen(s1) + ft_strlen(s2) + 2);
	if (!out)
		return (out);
	i = -1;
	while (s1[++i])
		out[i] = s1[i];
	j = -1;
	out[i] = '/';
	i++;
	while (s2[++j])
		out[i + j] = s2[j];
	return (out);
}

void	ft_get_working_path(char **path, char **cmd)
{
	char	*tmp;
	int		i;

	if (!path)
		return ;
	if (ft_strchr(*cmd, '/'))
		return ;
	i = 0;
	while (path[i])
	{
		tmp = ft_strcat_split(path[i], *cmd);
		if (access(tmp, F_OK | X_OK) != -1)
		{
			free(*cmd);
			*cmd = tmp;
			return ;
		}
		free(tmp);
		i++;
	}
}

void    ft_child(t_lcmd *cmd, t_env *env)
{
	char    **envstrr;

	cmd->pid = fork();
	if (cmd->pid == -1)
		exit(75);
	else if (cmd->pid == 0)
	{
		set_up_dup(cmd);
		envstrr = t_env_to_charr(env);
		if (!envstrr)
			exit(77);
		if (cmd->input > 2)
			close(cmd->input);
		if (cmd->output > 2)
			close(cmd->output);
		if (cmd->error > 2)
			close(cmd->error);
		execve(*(cmd->cmd), cmd->cmd, envstrr);
		perror(*(cmd->cmd));
		ft_free_strr(envstrr);
		exit(0);
	}
}

void    cmd_wait(t_lcmd *cmd)
{
	int status;

	status = 0;
	while (cmd)
	{
		if (cmd->pid > 0)
			waitpid(cmd->pid, &status, 0);
		else if (!cmd->next)
			return ;
		cmd = cmd->next;
	}
	g_cmd_exit = WEXITSTATUS(status);
}

void  here_unlink(t_lcmd *cmd)
{
    t_ioe_put *tmp;

    while (cmd)
    {
        tmp = cmd->ioe_put;
        while (tmp)
        {
            if (tmp->type == INPUT_HEREDOC && tmp->herename)
                unlink(tmp->herename);
            tmp = tmp->next;
        }
        cmd = cmd->next;
    }
}

void    process_cmd(t_lcmd *cmd, t_env *envdeeznuts)
{
	int    p[2];
	int    lastdeeznuts;
	t_lcmd *tmp;
	char   **path;

    lastdeeznuts = 0;
    tmp = cmd;
    while (tmp)
    {
        expand_cmd_ioe(tmp, envdeeznuts);
        process_file(tmp);
        if (tmp->next)
        {
            if (pipe(p) == -1)
                exit(66);
            if (tmp->input > 2 && lastdeeznuts > 0)
            {
                close(tmp->input);
                tmp->input = lastdeeznuts;
            }
            if (tmp->output > 2)
                close(tmp->output);
            tmp->output = p[1];
            if (!ft_is_builtin(tmp, envdeeznuts))
            {
                path = ft_get_path(envdeeznuts);
                ft_get_working_path(path, &(*(tmp->cmd)));
                ft_child(tmp, envdeeznuts);
                ft_free_strr(path);
            }
            close(p[1]);
            if (lastdeeznuts > 2)
                close(lastdeeznuts);
            lastdeeznuts = p[0];
        }
        else
        {
            if (lastdeeznuts > 2)
            {
                if (tmp->input > 2)
                    close(tmp->input);
                tmp->input = lastdeeznuts;
            }
            if (!ft_is_builtin(tmp, envdeeznuts))
            {
                path = ft_get_path(envdeeznuts);
                ft_get_working_path(path, &(*(tmp->cmd)));
                ft_child(tmp, envdeeznuts);
                ft_free_strr(path);
            }
        }
        tmp = tmp->next;
    }
    cmd_wait(cmd);
    here_unlink(cmd);
    if (lastdeeznuts > 2)
        close(lastdeeznuts);
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


