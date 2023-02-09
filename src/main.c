/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geudes <geudes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 11:27:48 by geudes            #+#    #+#             */
/*   Updated: 2023/02/09 05:46:29 by geudes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **_env)
{
	t_env	*env;
	char	*line;
	t_lexer	*root_lexer;

	(void)ac;
	(void)av;
	env = cpy_env(_env);
	char *exp[] = {"env", "=abc", "PATH=LECACA", 0};
	bi_export(exp, &env);
	bi_env(0, env);
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
