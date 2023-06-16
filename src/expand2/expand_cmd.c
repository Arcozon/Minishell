/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geudes <geudes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 05:02:04 by geudes            #+#    #+#             */
/*   Updated: 2023/06/16 18:41:58 by geudes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minshell.h"

char	**expand_lexer_part(t_lexer *lexer, t_lexer *end_lexer, t_env *env)
{
	while (*root && *root != end_lexer)
	{
		if ((*root)->type == TEXT_SQ)
		{
			expand_sq(*root, env);
			root = &((*root)->next);
		}
		else if ((*root)->type == TEXT_DQ)
		{
			expand_dq(*root, env);
			root = &((*root)->next);
		}
		else if ((*root)->type == TEXT)
			root = expand_text(root, env);
		else
			root = &((*root)->next);
	}
}
