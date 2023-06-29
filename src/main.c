/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geudes <geudes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 11:27:48 by geudes            #+#    #+#             */
/*   Updated: 2023/06/29 11:40:34 by geudes           ###   ########.fr       */
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
		set_sig_exec();
		if (!ms.line)
			break ;
		ms.lexer = lexer(ms.line, ms);
		if (ms.lexer)
			add_history(ms.line);
		else
			continue ;
		if (!syntax(ms.lexer))
			continue ;
		// aff_lexer(root_lexer, 0);
		ms.tree = create_node(ms.lexer, 0);
		// print_tree(tree, 0);
		process_tree(ms.tree, ms.env);
		free_lexer(ms.lexer);
	}
	kill(ms.euthanasia_pid, SIGUSR1);
	bi_exit();
	return (0);
}
