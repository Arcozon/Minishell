/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   text.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geudes <geudes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 01:08:20 by geudes            #+#    #+#             */
/*   Updated: 2023/06/05 02:24:51 by geudes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_lexer	**expand_text(t_lexer **root, t_env *env)
{
	int		i;
	int		what_i_find;
	char	*buffer;

	i = -1;
	what_i_find = 0;
	while ((*root)->content[++i] && !(what_i_find & 1))
	{
		if ((*root)->content[i] == '$')
			what_i_find |= 1;
		if ((*root)->content[i] == '*')
			what_i_find |= 2;
	}
	if (what_i_find & 1)
	{
		buffer = (*root)->content;
		(*root)->content = expand_dollar_sign((*root)->content, env);
		free(buffer);
	}
	else if (what_i_find & 2)
		return(expand_wc(root));
	return (&((*root)->next));
}
