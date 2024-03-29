/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_handling_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geudes <geudes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 18:43:09 by nriviere          #+#    #+#             */
/*   Updated: 2023/07/24 17:33:42 by geudes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_strchr(char *str, char c)
{
	while (*str)
	{
		if (*str == c)
			return (1);
		str++;
	}
	return (0);
}

char	*ft_strcat_split(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*out;

	if (!s1)
		return (s2);
	if (!s2)
		return (s1);
	out = ft_calloc(sizeof(char), ft_strlen(s1) + ft_strlen(s2) + 2);
	if (!out)
		return (out);
	i = -1;
	while (s1[++i])
		out[i] = s1[i];
	j = -1;
	out[i] = '/';
	i++;
	while (s2[++j])
		out[i + j] = s2[j];
	return (out);
}

int	ft_get_working_path(char **path, char **cmd)
{
	char	*tmp;
	int		i;

	if (!cmd || !(*cmd))
		return (1);
	else if (ft_strchr(*cmd, '/'))
		return (access(*cmd, F_OK | X_OK));
	else if (!ft_strcmp(*cmd, ".") || !ft_strcmp(*cmd, "..") || !path)
		return (3);
	i = 0;
	while (path[i])
	{
		tmp = ft_strcat_split(path[i], *cmd);
		if (!tmp)
			return (ft_write_to_fd(2, "Malloc error\n", 14), 2);
		if (access(tmp, F_OK | X_OK) != -1)
		{
			free(*cmd);
			*cmd = tmp;
			return (0);
		}
		free(tmp);
		i++;
	}
	return (3);
}
