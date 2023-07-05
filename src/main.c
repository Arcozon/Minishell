/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geudes <geudes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 11:27:48 by geudes            #+#    #+#             */
/*   Updated: 2023/07/05 12:33:25 by geudes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	g_cmd_exit = 0;

int	main(int ac, char **av, char **cenv)
{
	t_minishell	ms;

	((void)ac, (void)av);
	ms.euthanasia_pid = euthanasia();
	ms.env = cpy_env(cenv);
	while (1)
	{
		set_sig_routine();
		ms.line = readline(PROMPT);
		if (!ms.line)
			break ;
		ms.lexer = lexer(ms.line, &ms);
		if (ms.lexer)
			add_history(ms.line);
		else
			continue ;
		if (syntax(ms.lexer))
		{
			// aff_lexer(root_lexer, 0);
			ms.tree = create_node(ms.lexer, 0);
			//print_tree(tree, 0);
			set_sig_exec();
			process_tree(&ms, ms.tree);
			ms.tree = (free_node(ms.tree), (t_node *)0);
		}
		ms.lexer = (free_lexer(ms.lexer), (t_lexer *)0);
	}
	bi_exit(0, &ms);
	return (0);
}
