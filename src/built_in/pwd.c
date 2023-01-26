/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geudes <geudes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 11:27:43 by geudes            #+#    #+#             */
/*   Updated: 2023/01/26 10:13:01 by geudes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define SIZE 32

char	*_pwd(void)
{
	size_t	size_path;
	char	*path;

	size_path = SIZE;
	path = malloc(size_path * sizeof(char));
	if (!path)
		return (perror("Pwd malloc error\n"), (char *)0);
	while (!getcwd(path, size_path))
	{
		free(path);
		size_path <<= 1;
		path = malloc(size_path * sizeof(char));
		if (!path)
			return (perror("Pwd malloc error\n"), (char *)0);
	}
	return (path);
}
