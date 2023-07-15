/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_finding.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nriviere <nriviere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 18:43:03 by nriviere          #+#    #+#             */
/*   Updated: 2023/07/15 18:43:04 by nriviere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*ft_strjoin_weq(char const *s1, char const *s2)
{
	char	*ptr;
	int		i;
	int		iptr;

	if (!s1 && !s2)
		return (0);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	i = 0;
	iptr = 0;
	ptr = malloc((ft_strlen((char *)s1) + ft_strlen((char *)s2) + 1 + 1)
			* sizeof(char));
	if (ptr == 0)
		return (0);
	while (s1[i])
		ptr[iptr++] = s1[i++];
	ptr[iptr++] = '=';
	i = 0;
	while (s2[i])
		ptr[iptr++] = s2[i++];
	ptr[iptr] = '\0';
	return (ptr);
}

int	t_env_len(t_env *env)
{
	int	n;

	n = 0;
	while (env)
	{
		n++;
		env = env->next;
	}
	return (n);
}

char	**t_env_to_charr(t_env *env)
{
	int		len;
	int		i;
	char	**out;

	if (!env)
		return (0);
	len = t_env_len(env);
	i = 0;
	out = malloc(sizeof(char *) * (len + 1));
	if (!out)
		exit(76);
	while (i < len)
	{
		out[i] = ft_strjoin_weq(env->var_name, env->content);
		if (!out[i])
			exit(78);
		i++;
		env = env->next;
	}
	out[i] = 0;
	return (out);
}

char	**ft_get_path(t_env *env)
{
	while (env)
	{
		if (!ft_strcmp(env->var_name, "PATH"))
			return (ft_split(env->content, ':'));
		env = env->next;
	}
	return (0);
}
