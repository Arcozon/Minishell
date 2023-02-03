/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geudes <geudes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 08:44:42 by geudes            #+#    #+#             */
/*   Updated: 2023/02/02 20:01:41 by geudes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define DASH_N "-n"

// Returns 0 on succes 1 on error
// Av is a Null terminated char** with av[0] being the name of the function,
// and av[1]...av[n] the arguments
int	bi_echo(char **av, char **env)
{
	int	i;
	int	dash_n;

	i = 0;
	(void)env;
	if (!av)
		return (perror("Minishell: echo: av Null\n"), 1);
	while (av[i])
		i++;
	dash_n = 0;
	if (i > 1 && !ft_strncmp(av[1], DASH_N, ft_strlen(DASH_N) + 1))
		dash_n = (i++, 1);
	i = 0;
	while (av[++i])
	{
		write(1, av[i], ft_strlen(av[i]));
		if (av[i + 1])
			write(1, " ", 1);
	}
	if (!dash_n)
		write(1, "\n", 1);
	return (1);
}
