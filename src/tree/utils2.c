/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geudes <geudes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 20:33:05 by geudes            #+#    #+#             */
/*   Updated: 2023/06/12 20:34:06 by geudes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*join_same_type(t_lexer *lexer)
{
	char	*res;
	char	*buff;
	int		type;

	if (!lexer)
		return (0);
	type = lexer->type;
	res = 0;
	while (lexer && lexer->type == type)
	{
		buff = res;
		res = ft_strjoin(res, lexer->content);
		free(buff);
		lexer = lexer->next;
	}
	return (res);
}
