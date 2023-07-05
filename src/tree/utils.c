/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geudes <geudes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 23:13:16 by geudes            #+#    #+#             */
/*   Updated: 2023/06/12 20:33:15 by geudes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Is dumb af avoid using UNLESS you want end of lcmd
t_lexer	*look_for_first_opp(t_lexer *lexer, t_lexer *end_lexer)
{
	while (lexer && lexer != end_lexer)
	{
		if (lexer->type == OR || lexer->type == AND)
			return (lexer);
		lexer = lexer->next;
	}
	return (0);
}

//Doesnt see the opps inside parenthesys so is smart
t_lexer	*look_for_last_opp(t_lexer *lexer, t_lexer *end_lexer)
{
	t_lexer	*last_opp;
	int		count_par;

	count_par = 0;
	last_opp = 0;
	while (lexer && lexer != end_lexer)
	{
		if (lexer->type == OPEN_PAR)
			++count_par;
		if (lexer->type == CLOSE_PAR)
			--count_par;
		if ((lexer->type == OR || lexer->type == AND) && !count_par)
			last_opp = lexer;
		lexer = lexer->next;
	}
	return (last_opp);
}

//Is dumb af (doesnt count parenthesis) and shouldnt if syntax is well done
//Is less dumb cause knoz end of cmd
t_lexer	*look_for_pipe(t_lexer *lexer, t_lexer *end_lexer)
{
	while (lexer && lexer != end_lexer)
	{
		if (lexer->type == PIPE)
			return (lexer);
		lexer = lexer->next;
	}
	return (0);
}

//Is almost smart but doesnt look aat parenthesys, shouldnt be an issue if
//syntax is well done
t_lexer	*look_for_end_cmd(t_lexer *lexer, t_lexer *end_lexer)
{
	while (lexer && lexer != end_lexer)
	{
		if (lexer->type == PIPE || lexer->type == OR || lexer->type == AND)
			return (lexer);
		lexer = lexer->next;
	}
	return (end_lexer);
}

char	*join_args(t_lexer *lexer)
{
	char	*res;
	char	*buff;

	res = 0;
	while (lexer && (lexer->type == CMD || lexer->type == ARGS))
	{
		buff = res;
		res = ft_strjoin(res, lexer->content);
		free(buff);
		lexer = lexer->next;
	}
	return (res);
}
