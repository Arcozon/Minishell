/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geudes <geudes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 11:27:48 by geudes            #+#    #+#             */
/*   Updated: 2023/06/25 10:04:49 by geudes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	g_cmd_exit = 0;

int	main(int ac, char **av, char **_env)
{
	t_env	*env;
	char	*line;
	t_lexer	*root_lexer;
	t_node	*tree;

	(void)ac;
	(void)av;
	env = cpy_env(_env);
	line = 0;
	while (1)
	{
		line = readline(PROMPT);
		if (!line)
			break ;
		root_lexer = lexer(line);
		if (root_lexer)
			add_history(line);
		else
			continue ;
		// aff_lexer(root_lexer, 0);
		tree = create_node(root_lexer, 0);
		// print_tree(tree, 0);
		// printf("Syntax: %d\n", syntax(root_lexer));
		process_tree(tree, env);
		free_lexer(root_lexer);
	}
	bi_exit();
	return (0);
}
