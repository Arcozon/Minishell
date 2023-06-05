/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geudes <geudes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 23:34:51 by geudes            #+#    #+#             */
/*   Updated: 2023/06/05 02:26:38 by geudes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	expand_me_onee_chan(t_lexer **root, t_env *env)
{
	while (*root)
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
