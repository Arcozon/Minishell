/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geudes <geudes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 05:02:04 by geudes            #+#    #+#             */
/*   Updated: 2023/07/20 19:00:28 by geudes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	in_here_handle(int type, int in_here)
{
	if (!in_here && type == INPUT_HEREDOC)
		in_here = 1;
	else if (in_here && type != TEXT_SQ && type != TEXT_DQ && type != TEXT)
		in_here = 0;
	return (in_here);
}

void	expand_cmd_ioe(t_lcmd *lcmd, t_minishell *ms)
{
	t_lexer	**root;
	int		in_here;

	in_here = 0;
	root = &(lcmd->start_lexer);
	while (*root && *root != lcmd->end_lexer)
	{
		in_here = in_here_handle((*root)->type, in_here);
		if ((*root)->type == TEXT_SQ)
			expand_sq(*root, ms);
		else if ((*root)->type == TEXT_DQ)
			expand_dq(*root, ms, in_here);
		else if ((*root)->type == TEXT)
		{
			root = expand_text(root, ms, in_here);
			continue ;
		}
		root = &((*root)->next);
	}
	change_text(lcmd->start_lexer, lcmd->end_lexer);
	change_text_into_cmd_args(lcmd->start_lexer, lcmd->end_lexer);
	lcmd->cmd = create_cmd(lcmd->start_lexer, lcmd->end_lexer, ms);
	lcmd->ioe_put = create_ioeput(lcmd->start_lexer, lcmd->end_lexer, ms);
}
