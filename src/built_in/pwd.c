/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geudes <geudes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 11:27:43 by geudes            #+#    #+#             */
/*   Updated: 2023/06/15 01:24:34 by geudes           ###   ########.fr       */
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
int	bi_pwd(t_lcmd *lcmd, t_env **env)
{
	char	*pwd;

	(void)env;
	pwd = get_pwd();
	if (!pwd)
		return (write(lcmd->error, "Minishell: pwd: malloc error", 28), 0);
	write(lcmd->output, pwd, ft_strlen(pwd));
	write(lcmd->output, "\n", 1);
	free(pwd);
	return (1);
}
