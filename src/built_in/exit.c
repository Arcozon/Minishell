/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geudes <geudes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 10:02:13 by geudes            #+#    #+#             */
/*   Updated: 2023/07/22 02:53:59 by geudes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_exit_safely(t_minishell *all)
{
	rl_clear_history();
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);
	free_ms(all);
	exit(g_cmd_exit);
}

int	exit_num_arg_req(char *str, int error)
{
	if (*str == '-' || *str == '+')
		str++;
	if (*str < '0' || *str > '9')
	{
		if (error >= 0)
			write(error, "minishell: exit: numeric arguments required\n", 44);
		g_cmd_exit = 2;
		return (0);
	}
	while (!*str)
	{
		if (*str < '0' || *str > '9')
		{
			if (error >= 0)
				write(error, "minishell: exit: numeric arguments required\n",
					44);
			g_cmd_exit = 2;
			return (0);
		}
		str++;
	}
	return (1);
}

//return 0 is exit_ok 1 if not
int	exit_errors(char **cmd, int error)
{
	int	ac[2];
	int	sign;

	ac[0] = 0;
	while (cmd[ac[0]])
		ac[0]++;
	if (ac[0] == 2 && (cmd[1], error))
	{
		g_cmd_exit = 0;
		sign = 1;
		ac[1] = 0;
		if (cmd[1][ac[1]] == '-' || cmd[1][ac[1]] == '+')
		{
			if (cmd[1][ac[1]] == '-')
				sign = -1;
			++ac[1];
		}
		--ac[1];
		while (cmd[1][++ac[1]] >= '0' && cmd[1][ac[1]] <= '9')
			g_cmd_exit = g_cmd_exit * 10 + cmd[1][ac[1]] - '0';
		g_cmd_exit *= sign;
	}
	if (ac[0] > 2 && exit_num_arg_req(cmd[1], error))
		return (write(error, "minishell: exit: too many arguments\n", 36), 1);
	return (0);
}

//Return sex number cause noah is a silly little clown
int	bi_exit(t_lcmd *lcmd, t_minishell *ms)
{
	int	error;

	error = 2;
	if (lcmd)
		error = lcmd->error;
	write(error, "exit\n", 5);
	if (!lcmd || !exit_errors(lcmd->cmd, error))
		ft_exit_safely(ms);
	return (1);
}
