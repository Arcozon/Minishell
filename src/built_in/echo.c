/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geudes <geudes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 08:44:42 by geudes            #+#    #+#             */
/*   Updated: 2023/06/25 09:02:41 by geudes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	get_option(t_lcmd *lcmd, int *dashn)
{
	int	i;
	int	j;

	i = 0;
	while (lcmd->cmd[++i])
	{
		j = 0;
		if (lcmd->cmd[i][j] == '-')
		{
			while (lcmd->cmd[i][++j] && lcmd->cmd[i][j] == 'n')
				if (!*dashn)
					*dashn = 1;
			if (lcmd->cmd[i][j])
				break ;
		}
		else
			break ;
	}
	return (i);
}

static int	echo_error(int fd_error)
{
	write(fd_error, "echo: write error: no space left on device\n", 43);
	return (1);
}

// Returns 0 on succes 1 on error
int	bi_echo(t_lcmd *lcmd, t_env *env)
{
	int	i;
	int	dashn;

	(void)env;
	dashn = 0;
	i = get_option(lcmd, &dashn);
	while (lcmd->cmd[i])
	{
		if (write(lcmd->output, lcmd->cmd[i], ft_strlen(lcmd->cmd[i]))
			!= (int)ft_strlen(lcmd->cmd[i]))
			return (echo_error(lcmd->error));
		if (lcmd->cmd[++i])
			if (write(lcmd->output, " ", 1) != 1)
				return (echo_error(lcmd->error));
	}
	if (!dashn)
		if (write(lcmd->output, "\n", 1) != 1)
			return (echo_error(lcmd->error));
	return (0);
}
