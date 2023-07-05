/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geudes <geudes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 06:17:37 by geudes            #+#    #+#             */
/*   Updated: 2023/07/05 09:17:00 by geudes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Returns 0 on succes 1 on error
int	bi_unset(t_lcmd *lcmd, t_minishell *ms)
{
	t_env	**root;
	t_env	*buff;
	int		i;

	i = 1;
	while (lcmd->cmd[i])
	{
		root = &ms->env;
		while (*root)
		{
			if (!ft_strncmp((*root)->var_name, lcmd->cmd[i],
					ft_strlen(lcmd->cmd[i]) + 1))
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
		++i;
	}
	return (0);
}
