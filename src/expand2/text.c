/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   text.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geudes <geudes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 01:08:20 by geudes            #+#    #+#             */
/*   Updated: 2023/07/20 18:58:10 by geudes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_dollar_sign(char *text, t_minishell *ms)
{
	char	*return_str;
	int		last_find;
	int		i;

	i = 0;
	last_find = 0;
	return_str = ft_strdup("");
	awaiting_death(!return_str, ms);
	while (text[i])
	{
		if (text[i] == '$')
		{
			return_str = join_rest_text(text, return_str, last_find,
					i - last_find);
			awaiting_death(!return_str, ms);
			return_str = join_n_find_var(text, &i, return_str, ms);
			last_find = i;
		}
		else
			++i;
	}
	return_str = join_rest_text(text, return_str, last_find, i - last_find);
	awaiting_death(!return_str, ms);
	return (return_str);
}

static t_lexer	**expand_text2(t_lexer **root, t_minishell *ms)
{
	t_lexer	**return_value;
	t_lexer	*my_litle_slly_trash;
	t_lexer	*next;
	t_lexer	**ms_root;

	ms_root = &(ms->lexer);
	while (*ms_root && *ms_root != *root)
		ms_root = &((*ms_root)->next);
	next = (*root)->next;
	my_litle_slly_trash = *root;
	*root = expand_wc_v2((*root)->content, ms);
	*ms_root = *root;
	free(my_litle_slly_trash->content);
	free(my_litle_slly_trash);
	return_value = lexer_get_last(root);
	lexer_add_back(root, next);
	return (&(*return_value)->next);
}

t_lexer	**expand_text(t_lexer **root, t_minishell *ms, int in_here)
{
	int		i;
	int		what_i_find;
	char	*buffer;

	i = -1;
	what_i_find = 0;
	while ((*root)->content[++i] && !(what_i_find & 1))
		what_i_find |= (((*root)->content[i] == '$') + 2
				* ((*root)->content[i] == '*'));
	if (what_i_find & 1 && !in_here)
	{
		buffer = (*root)->content;
		(*root)->content = expand_dollar_sign((*root)->content, ms);
		free(buffer);
	}
	else if (what_i_find & 2 && !in_here)
		return (expand_text2(root, ms));
	return (&((*root)->next));
}
