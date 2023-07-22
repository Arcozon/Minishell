/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geudes <geudes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 11:27:48 by geudes            #+#    #+#             */
/*   Updated: 2023/07/22 05:12:47 by geudes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	g_cmd_exit = 0;

static t_minishell	init_ms(char **cenv)
{
	t_minishell	ms;

	ms.euthanasia_pid = euthanasia();
	ms.env = cpy_env(cenv);
	ms.lexer = 0;
	ms.tree = 0;
	ms.trash_wc = 0;
	return (ms);
}

int	main(int ac, char **av, char **cenv)
{
	t_minishell	ms;

	ms = ((void)ac, (void)av, set_sig_routine(), init_ms(cenv));
	while (1)
	{
		if (g_cmd_exit)
			ms.line = readline(PROMPTKO);
		else
			ms.line = readline(PROMPTOK);
		if (!ms.line)
			break ;
		ms.lexer = lexer(ms.line, &ms);
		if (ms.lexer)
			add_history(ms.line);
		else
			continue ;
		if (syntax(ms.lexer))
		{
			ms.tree = create_node(ms.lexer, 0, &ms);
			(set_sig_exec(), process_tree(&ms, ms.tree), set_sig_routine());
			ms.tree = (free_node(ms.tree), (t_node *)0);
		}
		ms.lexer = (free_lexer(ms.lexer, ms.trash_wc), free_trash(&ms), NULL);
	}
	return (bi_exit(0, &ms), 0);
}
