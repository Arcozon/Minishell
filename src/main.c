/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geudes <geudes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 11:27:48 by geudes            #+#    #+#             */
/*   Updated: 2023/02/11 02:00:13 by geudes           ###   ########.fr       */
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
	char *unset[] = {"unset", "PATH", "USER_ZDOTDIR", 0};
	bi_unset(unset, &env);
	bi_env(0, env);
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
	}
	bi_exit();
	return (0);
}
