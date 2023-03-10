/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geudes <geudes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 11:27:46 by geudes            #+#    #+#             */
/*   Updated: 2023/02/09 05:52:57 by geudes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_path(char **av)
{
	char	*path;
	char	*pwd;
	int		ac;

	ac = 0;
	while (av[ac])
		ac++;
	if (ac > 2)
		return (write(2, "Minishell: cd: Too many arguments\n", 34), (char *)0);
	if (ac == 1)
		return (ft_strdup("~"));
	if (ft_strlen(av[1]) > 255)
		return (write(2, "Minishell: cd: File name too long\n", 34), (char *)0);
	if (av[1][0] != '/' && av[1][0] != '~')
	{
		pwd = get_pwd();
		if (!pwd)
			return (write(2, "Minishell: cd: Pwd error\n", 25), (char *)0);
		path = ft_strjoin_with_slash(pwd, av[1]);
		free(pwd);
		return (path);
	}
	return (ft_strdup(av[1]));
}

// Returns 0 on succes 1 on error
// Av is a Null terminated char** with av[0] being the name of the function,
// and av[1]...av[n] the arguments
int	bi_cd(char **av, t_env *env)
{
	char	*path;

	(void)env;
	path = get_path(av);
	if (!path)
		return (0);
	if (chdir(path))
	{
		write (2, "Minishell: cd :", 15);
		write (2, av[1], ft_strlen(av[1]));
		write (2, ": No such file or directory\n", 28);
		free(path);
		return (0);
	}
	free(path);
	return (1);
}
