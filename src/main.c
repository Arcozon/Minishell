/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geudes <geudes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 11:27:48 by geudes            #+#    #+#             */
/*   Updated: 2023/06/05 02:06:20 by geudes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_cmd_exit = 0;

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
		if (!line)
			break ;
		if (ft_strlen(line))
			add_history(line);
		root_lexer = lexer(line, env);
		aff_lexer(root_lexer);
		printf("Syntax: %d\n", syntax(root_lexer));
		free_lexer(root_lexer);
	}
	bi_exit();
	return (0);
}
