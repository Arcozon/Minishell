/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   text.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geudes <geudes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 01:08:20 by geudes            #+#    #+#             */
/*   Updated: 2023/02/13 15:46:57 by geudes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	expand_text(t_lexer *root, t_env *env)
{
	int		i;
	int		what_i_find;
	char	*buffer;

	i = -1;
	what_i_find = 0;
	while (root->text[++i] && !what_i_find)
	{
		if (root->text[i] == '$')
			what_i_find |= 1;
		if (root->text[i] == '*')
			what_i_find |= 2;
	}
	if (what_i_find & 1)
	{
		buffer = root->text;
		root->text = expand_dollar_sign(root->text, env);
		free(root->text);
	}
	else if (what_i_find & 2)
	{
		//wildcard
	}
}
