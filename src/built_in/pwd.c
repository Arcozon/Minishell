/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geudes <geudes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 11:27:43 by geudes            #+#    #+#             */
/*   Updated: 2023/02/09 05:50:47 by geudes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define SIZE 32

char	*get_pwd(void)
{
	size_t	size_path;
	char	*path;

	size_path = SIZE;
	path = malloc(size_path * sizeof(char));
	if (!path)
		return (0);
	while (!getcwd(path, size_path))
	{
		free(path);
		size_path <<= 1;
		path = malloc(size_path * sizeof(char));
		if (!path)
			return (0);
	}
	return (path);
}

// Returns 0 on succes 1 on error
// Av is a Null terminated char** with av[0] being the name of the function,
// and av[1]...av[n] the arguments
int	pwd(char **av, char **env)
{
	char	*pwd;

	(void)av;
	(void)env;
	pwd = get_pwd();
	if (!pwd)
		return (write(2, "Minishell: pwd: malloc error, 28"), 0);
	write(1, pwd, ft_strlen(pwd));
	pwd[0] = '\n';
	write(1, pwd, 1);
	free(pwd);
	return (1);
}
