/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geudes <geudes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 06:17:37 by geudes            #+#    #+#             */
/*   Updated: 2023/02/10 11:07:26 by geudes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Returns 0 on succes 1 on error
// Av is a Null terminated char** with av[0] being the name of the function,
// and av[1]...av[n] the arguments
int	bi_unset(char **av, t_env **env)
{
	t_env	**root;
	t_env	*buff;
	int		i;

	i = 1;
	while (av[i])
	{
		root = env;
		while (*root)
		{
			if (!ft_strncmp((*root)->var_name, av[i], ft_strlen(av[i]) + 1))
			{
				buff = *root;
				*root = (*root)->next;
				free(buff->var_name);
				free(buff->content);
				free(buff);
				break ;
			}
			root = &((*root)->next);
		}
		i++;
	}
	return (0);
}
