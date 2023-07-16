/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geudes <geudes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 05:02:04 by geudes            #+#    #+#             */
/*   Updated: 2023/07/16 21:42:14 by geudes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	expand_cmd_ioe(t_lcmd *lcmd, t_minishell *ms)
{
	t_lexer	**root;

	root = &(lcmd->start_lexer);
	while (*root && *root != lcmd->end_lexer)
	{
		if ((*root)->type == TEXT_SQ)
			expand_sq(*root, ms);
		else if ((*root)->type == TEXT_DQ)
			expand_dq(*root, ms);
		else if ((*root)->type == TEXT)
		{
			root = expand_text(root, ms);
			continue ;
		}
		root = &((*root)->next);
	}
	change_text(lcmd->start_lexer, lcmd->end_lexer);
	change_text_into_cmd_args(lcmd->start_lexer, lcmd->end_lexer);
	lcmd->cmd = create_cmd(lcmd->start_lexer, lcmd->end_lexer, ms);
	lcmd->ioe_put = create_ioeput(lcmd->start_lexer, lcmd->end_lexer, ms);
	aff_lexer(lcmd->start_lexer, 0);
	write(2, "\n", 1);
}
