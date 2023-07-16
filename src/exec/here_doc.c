/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nriviere <nriviere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 18:42:45 by nriviere          #+#    #+#             */
/*   Updated: 2023/07/16 18:00:29 by nriviere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include <bits/posix_opt.h>
#include <fcntl.h>
#include <stdio.h>
#include <termios.h>
#include <unistd.h>

static int	ft_heredoc_perror(char *str)
{
	int	i;

	i = ft_putstr_fd(2,
			"\nMinishell: warning: here-document at line 1 delimited by"
			" end-of-file (wanted '");
	i <<= 1;
	i += ft_putstr_fd(2, str);
	i <<= 1;
	i += ft_putstr_fd(2, "')\n");
	return (i);
}

static int	ft_check_eof(int fd, char buf[1], char *str, int len)
{
	int	i;
	int	br;

	i = -1;
	br = 1;
	while (br != 0 && ++i < len)
	{
		br = read(STDIN_FILENO, buf, 1);
		if (br == -1)
			return (-1);
		if (br == 0 || buf[0] != i[str])
			break ;
	}
	if (i == len)
	{
		br = read(STDIN_FILENO, buf, 1);
		if (br == -1)
			return (-1);
		if (buf[0] == '\n')
			return (0);
	}
	write(fd, str, i);
	if ((i < len && br != 0) || (i == len && buf[0] != '\n'))
		write(fd, buf, 1);
	return (1 + (br == 0));
}

int	ft_read_stdin(int fd, char *str, int len)
{
	char	buf[1];
	int		br;
	int		status;

	br = 1;
	status = 1;
	buf[0] = (write(STDOUT_FILENO, "> ", 2), 0);
	while (br != 0)
	{
		status = ft_check_eof(fd, buf, str, len);
		if (status == 0)
			break ;
		else if (status == -1)
			return (-1);
		else if (status == 2)
			return (ft_heredoc_perror(str), 0);
		while (buf[0] != '\n')
		{
			br = read(STDIN_FILENO, buf, 1);
			if (br == -1 || write(fd, buf, 1) == 2)
				return (-1);
		}
		write(STDOUT_FILENO, "> ", 2);
	}
	return (0);
}

void	capture_signal(int status)
{
	static struct termios	orig;
	struct termios			tmp;

	if (status == 1)
	{
		tcgetattr(STDIN_FILENO, &tmp);
		orig = tmp;
		tmp.c_cc[VQUIT] = _POSIX_VDISABLE;
		tmp.c_lflag |= ICANON | ECHO ;
		tcsetattr(STDIN_FILENO, TCSANOW, &tmp);
		set_sig_heredoc();
	}
	else if (status == 0)
	{
		tcsetattr(STDIN_FILENO, TCSANOW, &orig);
		set_sig_exec();
	}
}

int	heredoc(t_lcmd *cmd, t_ioe_put *ioe, int *ostatus)
{
	int	status;
	int	tmp_g_status;

	ioe->herename = strnrand(64);
	status = 0;
	if (ft_open_file(ioe->herename, &cmd->input, O_CREAT | O_WRONLY | O_TRUNC,
			0644))
		return (1);
	tmp_g_status = g_cmd_exit;
	capture_signal(1);
	status = ft_read_stdin(cmd->input, ioe->name, ft_strlen(ioe->name));
	capture_signal(0);
	if (g_cmd_exit == 130 || status == -1)
	{
		*ostatus = 1;
		return (1);
	}
	g_cmd_exit = tmp_g_status;
	if (ft_open_file(ioe->herename, &cmd->input, O_RDONLY, 0))
		return (1);
	return (0);
}
