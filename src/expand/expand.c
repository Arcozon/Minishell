/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geudes <geudes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 23:34:51 by geudes            #+#    #+#             */
/*   Updated: 2023/02/15 04:15:02 by geudes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	expand_me_onee_chan(t_lexer **root, t_env *env)
{
	t_lexer	**next;

	while (*root)
	{
		next = &((*root)->next);
		if ((*root)->type == TEXT_SQ)
			expand_sq(*root, env);
		else if ((*root)->type == TEXT_DQ)
			expand_dq(*root, env);
		else if ((*root)->type == TEXT)
			expand_text(root, env);
		root = next;
	}
}
