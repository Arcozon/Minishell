/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geudes <geudes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 07:54:37 by geudes            #+#    #+#             */
/*   Updated: 2023/02/11 01:13:52 by geudes           ###   ########.fr       */
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
// Av is a Null terminated char** with av[0] being the name of the function,
// and av[1]...av[n] the arguments
int	bi_export(char **av, t_env **env)
{
	t_env	*do_i;
	int		i_equal;
	int		i;
	int		returnvalue;

	returnvalue = 0;
	i = 0;
	while (av[++i])
	{
		if (av[i][0] == '=')
			returnvalue = (write(2,
						"Minishell: export: not a valid identifier\n", 42), 1);
		if (av[i][0] == '=' || count_equals(av[i]) != 1)
			continue ;
		do_i = do_i_exist_in_env(av[i], *env);
		if (!do_i)
			env_addback(env, new_env(av[i]));
		if (!do_i)
			continue ;
		i_equal = (free(do_i->content), 0);
		while (av[i][i_equal] && av[i][i_equal] != '=')
			i_equal++;
		do_i->content = ft_substr(av[i], i_equal + 1, ft_strlen(av[i]));
	}
	return (returnvalue);
}
