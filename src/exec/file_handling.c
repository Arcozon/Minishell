#include "../../inc/minishell.h"
#include <fcntl.h>
#include <unistd.h>

static int	ft_open_file_(char *str, int oflag, int mode)
{
	int	fd;

	fd = open(str, oflag, mode);
	if (fd == -1)
		perror(str);
	return (fd);
}

int	ft_open_file(char *name, int *fd, int oflag, int mode)
{
	int	tmp;

	if (*fd > 2)
		close(*fd);
    if (mode != 0)
    {
        mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
    }
	tmp = ft_open_file_(name, oflag, mode);
	if (tmp == -1)
		return (1);
	*fd = tmp;
	return (0);
}

int	ft_write_to_fd(int fd, char *str, int len)
{
	return (write(fd, str, len) != len);
}

int	ft_putstr_to_fd(int fd, char *str)
{
	int	i;

	i = ft_strlen(str);
	return (ft_write_to_fd(fd, str, i));
}

int	process_file(t_lcmd *cmd)
{
	t_ioe_put	*tmp;
    int status;

	tmp = cmd->ioe_put;
    status = 0;
	while (tmp)
	{
		if (tmp->type == INPUT_REDIR && !ft_open_file(tmp->name, &cmd->input,
				O_RDONLY, 0))
			;
		else if (tmp->type == OUTPUT_REDIR && !ft_open_file(tmp->name,
					&cmd->output, O_CREAT | O_WRONLY | O_TRUNC, 1))
			;
		else if (tmp->type == OUTPUT_HAPPEND_REDIR && !ft_open_file(tmp->name,
					&cmd->output, O_CREAT | O_WRONLY | O_APPEND, 1))
			;
		else if (tmp->type == INPUT_HEREDOC && !heredoc(cmd, tmp, &status))
			;
		else if (tmp->type == ERROR_REDIR && !ft_open_file(tmp->name,
					&cmd->output, O_CREAT | O_WRONLY | O_TRUNC, 1))
			;
		else
			return (1 + status);
		tmp = tmp->next;
	}
	return (0);
}

