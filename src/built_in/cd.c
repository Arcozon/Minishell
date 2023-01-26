/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geudes <geudes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 11:27:46 by geudes            #+#    #+#             */
/*   Updated: 2023/01/26 10:12:25 by geudes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Returns 0 on succes -1 on error
int	_cd(char *path)
{
	char	*pwd;
	char	*buffer;

	if (!path)
		return (perror("cd path NULL\n"), -1);
	if (path[0] == '/')
	{
		if (chdir(path))
			return (perror("cd path non valid\n"), -1);
		return (0);
	}
	pwd = _pwd();
	if (!pwd)
		return (perror("cd pwd error\n"), -1);
	buffer = ft_strjoin("/", path);
	if (!buffer)
		return (perror("cd malloc error\n"), free(pwd), -1);
	path = ft_strjoin(pwd, buffer);
	(free(pwd), free(buffer));
	if (chdir(path))
		return (perror("cd path non valid\n"), -1);
	free(path);
	return (0);
}
