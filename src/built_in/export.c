/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geudes <geudes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 07:54:37 by geudes            #+#    #+#             */
/*   Updated: 2023/07/05 09:00:13 by geudes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*new_env(char *var)
{
	t_env	*new;
	int		i_equal;

	new = malloc(sizeof(t_env));
	if (!new)
		return (write(2, "Malloc error during var assigment\n", 34), (t_env *)0);
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

t_env	*do_i_exist_in_env(char *var, t_env *root)
{
	char	*var_name;
	int		i_equal;

	i_equal = 0;
	while (var[i_equal] && var[i_equal] != '=')
		i_equal++;
	if (!var[i_equal])
		return (0);
	var_name = ft_substr(var, 0, i_equal);
	i_equal++;
	while (root)
	{
		if (!ft_strncmp(var_name, root->var_name, i_equal))
			return (free(var_name), root);
		root = root->next;
	}
	return (free(var_name), (t_env *)0);
}

int	count_equals(char *var)
{
	int	i;
	int	nb_equals;

	i = -1;
	nb_equals = 0;
	while (var[++i])
		if (var[i] == '=')
			nb_equals++;
	return (nb_equals);
}

// Returns 0 on succes 1 on error
int	bi_export(t_lcmd *lcmd, t_minishell *ms)
{
	t_env	*do_i;
	int		i_equal;
	int		i;
	int		returnvalue;

	returnvalue = 0;
	i = 0;
	while (lcmd->cmd[++i])
	{
		if (lcmd->cmd[i][0] == '=')
			returnvalue = (write(lcmd->error,
						"Minishell: export: not a valid identifier\n", 42), 1);
		if (lcmd->cmd[i][0] == '=' || count_equals(lcmd->cmd[i]) == 0)
			continue ;
		do_i = do_i_exist_in_env(lcmd->cmd[i], ms->env);
		if (!do_i)
			env_addback(&ms->env, new_env(lcmd->cmd[i]));
		if (!do_i)
			continue ;
		i_equal = (free(do_i->content), 0);
		while (lcmd->cmd[i][i_equal] && lcmd->cmd[i][i_equal] != '=')
			i_equal++;
		do_i->content = ft_strdup(lcmd->cmd[i] + i_equal + 1);
	}
	return (returnvalue);
}
