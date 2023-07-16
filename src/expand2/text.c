/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   text.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geudes <geudes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 01:08:20 by geudes            #+#    #+#             */
/*   Updated: 2023/07/16 19:56:18 by geudes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_lexer	**expand_text2(t_lexer **root, t_minishell *ms)
{
	t_lexer	**return_value;
	t_lexer	*my_litle_slly_trash;
	t_lexer	*next;

	next = (*root)->next;
	my_litle_slly_trash = *root;
	*root = expand_wc_v2((*root)->content, ms);
	my_litle_slly_trash->next = 0;
	lexer_add_back(&(ms->trash_wc), my_litle_slly_trash);
	return_value = lexer_get_last(root);
	lexer_add_back(root, next);
	return (&(*return_value)->next);
}

t_lexer	**expand_text(t_lexer **root, t_minishell *ms)
{
	int		i;
	int		what_i_find;
	char	*buffer;

	i = -1;
	what_i_find = 0;
	while ((*root)->content[++i] && !(what_i_find & 1))
		what_i_find |= (((*root)->content[i] == '$') + 2
				* ((*root)->content[i] == '*'));
	if (what_i_find & 1)
	{
		buffer = (*root)->content;
		(*root)->content = expand_dollar_sign((*root)->content, ms);
		free(buffer);
	}
	else if (what_i_find & 2)
		return (expand_text2(root, ms));
	return (&((*root)->next));
}
