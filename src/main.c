/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geudes <geudes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 11:27:48 by geudes            #+#    #+#             */
/*   Updated: 2023/02/07 05:54:29 by geudes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*new_env(char *var)
{
	t_env	*new;
	int		i_equal;

	new = malloc(sizeof(t_env));
	if (!new)
		return (0);
	new->next = 0;
	i_equal = 0;
	while (var[i_equal] && var[i_equal] != '=')
		i_equal++;
	if (!var[i_equal])
		return (free(new), 0);
	new->var_name = ft_substr(var, 0, i_equal - 1);
	new->
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

	i = 0;
}

int	main(int ac, char **av, char **_env)
{
	t_env	*env;
	char	*line;
	t_lexer	*root_lexer;

	(void)ac;
	(void)av;
	env = cpy_env(_env);
	line = 0;
	while (1)
	{
		line = readline(PROMPT);
		if (ft_strlen(line))
			add_history(line);
		root_lexer = lexer(line);
		aff_lexer(root_lexer);
		printf("Syntax: %d\n", syntax(root_lexer));
	}
	return (0);
}
