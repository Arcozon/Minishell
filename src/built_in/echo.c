/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geudes <geudes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 08:44:42 by geudes            #+#    #+#             */
/*   Updated: 2023/01/26 10:12:30 by geudes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define DASH_N "-n"

void	_echo(char **args)
{
	int	i;
	int	dash_n;

	if (!args || !args[0])
		return ;
	i = -1;
	dash_n = 0;
	if (!ft_strncmp(args[0], DASH_N, ft_strlen(DASH_N) + 1))
		dash_n = (i++, 1);
	while (args[++i])
	{
		write(1, args[i], ft_strlen(args[i]));
		if (args[i + 1])
			write(1, " ", 1);
	}
	if (!dash_n)
		write(1, "\n", 1);
}
