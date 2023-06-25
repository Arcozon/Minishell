/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   text.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geudes <geudes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 01:08:20 by geudes            #+#    #+#             */
/*   Updated: 2023/06/25 05:34:02 by geudes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_lexer	**expand_text(t_lexer **root, t_env *env)
{
	int		i;
	int		what_i_find;
	char	*buffer;
	t_lexer	**next;

	i = -1;
	what_i_find = 0;
	while ((*root)->content[++i] && !(what_i_find & 1))
		what_i_find |= (((*root)->content[i] == '$') + 2
			* ((*root)->content[i] == '*'));
	if (what_i_find & 1)
	{
		buffer = (*root)->content;
		(*root)->content = expand_dollar_sign((*root)->content, env);
		free(buffer);
	}
	else if (what_i_find & 2)
	{
		next = &((*root)->next);
		*root = expand_wc_v2((*root)->content);
		lexer_add_back(root, *next);
		return (next);
	}
	return (&((*root)->next));
}
