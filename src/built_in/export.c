/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geudes <geudes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 07:54:37 by geudes            #+#    #+#             */
/*   Updated: 2023/07/22 04:41:50 by geudes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static inline int	is_alpha_num(int c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')
		|| (c >= '0' && c <= '9') || c == '_');
}

int	error_or_no(char *str)
{
	int	i;

	i = -1;
	while (str[++i] && str[i] != '=')
		if (!is_alpha_num(str[i]))
			return (1);
	return (0);
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
		if (error_or_no(lcmd->cmd[i]))
			returnvalue = (write(lcmd->error,
						"Minishell: export: not a valid identifier\n", 42), 1);
		if (error_or_no(lcmd->cmd[i]) || count_equals(lcmd->cmd[i]) == 0)
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
