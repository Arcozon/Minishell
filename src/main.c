/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geudes <geudes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 11:27:48 by geudes            #+#    #+#             */
/*   Updated: 2023/02/03 17:12:20 by geudes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **_env)
{
	char	*line;
	t_lexer	*root_lexer;

	(void)ac;
	(void)av;
	(void)_env;
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
