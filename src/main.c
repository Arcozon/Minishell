/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geudes <geudes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 11:27:48 by geudes            #+#    #+#             */
/*   Updated: 2023/01/26 10:12:14 by geudes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Return 0 is it foudn  built in, 1 if it didnt -1 in case of an error
int	check_built_ins(char *line, char **_cmd)
{
	(void)line;
	(void)_cmd;
	return (1);
}

int	main(int ac, char **av, char **_env)
{
	char	*line;

	(void)ac;
	(void)av;
	(void)_env;
	line = 0;
	while (1)
	{
		line = readline(PROMPT);
		// parsing_t_cmd(line, 0, 1, 2);
		lexer(line);
	}
	return (0);
}
