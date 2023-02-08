/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geudes <geudes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 00:05:34 by geudes            #+#    #+#             */
/*   Updated: 2023/02/08 00:29:33 by geudes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*new_env(char *var)
{
	t_env	*new;
	int		i_equal;

	new = malloc(sizeof(t_env));
	if (!new)
		return (perror("Malloc error during var assigment\n"), (t_env *)0);
	new->next = 0;
	i_equal = 0;
	while (var[i_equal] && var[i_equal] != '=')
		i_equal++;
	if (!var[i_equal])
		return (free(new), (t_env *)0);
	new->var_name = ft_substr(var, 0, i_equal);
	new->content = ft_substr(var, i_equal + 1, ft_strlen(var));
	return (new);
}

void	env_addback(t_env **root, t_env *new)
{
	while (*root)
		root = &((*root)->next);
	*root = new;
}

t_env	*cpy_env(char **_env)
{
	int			i;
	t_env		*env;

	i = -1;
	env = 0;
	while (_env[++i])
		env_addback(&env, new_env(_env[i]));
	return (env);
}
