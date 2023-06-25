/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geudes <geudes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 08:44:42 by geudes            #+#    #+#             */
/*   Updated: 2023/06/25 04:01:31 by geudes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// Returns 0 on succes 1 on error
int	bi_echo(t_lcmd *lcmd, t_env *env)
{
	int	i;
	int	dashn;
	int	j;

	i = ((void)env, 0);
	while (lcmd->cmd[++i])
	{
		j = 0;
		if (lcmd->cmd[i][0] == '-')
		{
			while (lcmd->cmd[i][++j] && lcmd->cmd[i][j] == 'n')
				dashn = 1;
			if (lcmd->cmd[i][j])
				break ;
		}
		else
			break ;
	}
	while (lcmd->cmd[i])
	{
		write(lcmd->output, lcmd->cmd[i], ft_strlen(lcmd->cmd[i]));
		if (lcmd->cmd[++i])
			write(lcmd->output, " ", 1);
	}
	if (!dashn)
		write(lcmd->output, "\n", 1);
	return (0);
}
