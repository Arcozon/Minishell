/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geudes <geudes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 10:16:42 by geudes            #+#    #+#             */
/*   Updated: 2023/02/06 08:15:46 by geudes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	i_m_text(int pre_type, int next_type)
{
	static int	trad_pre[] = {ERROR, ERROR, ERROR, ERROR, ARGS, ARGS, ERROR,
		ARGS, ARGS, FILE_INPUT, HEREDOC_EOF, CMD, FILE_OUTPUT, FILE_OUTPUT,
		FILE_ERROR, CMD, TEXT, TEXT, TEXT, TEXT, TEXT};
	static int	trad_next[] = {ERROR, ERROR, ERROR, ERROR, ERROR, TEXT, TEXT,
		TEXT, TEXT, ERROR, ERROR, ERROR, TEXT, TEXT, TEXT, TEXT, TEXT, TEXT,
		TEXT, TEXT, VAR, TEXT};
	int			mytype;

	mytype = TEXT;
	(void)next_type;
	if (pre_type >= 0 && pre_type < MAX_TYPE)
		mytype = trad_pre[pre_type];
	if (mytype == TEXT && next_type >= 0 && next_type < MAX_TYPE)
		mytype = trad_next[next_type];
	return (mytype);
}

void	change_text(t_lexer *root)
{
	t_lexer	*actual_chain;
	int		pre_type;
	int		next_type;

	pre_type = UNDEFINED_TYPE;
	actual_chain = root;
	while (actual_chain)
	{
		next_type = UNDEFINED_TYPE;
		if (actual_chain->next)
			next_type = actual_chain->next->type;
		if (actual_chain->type == TEXT)
			actual_chain->type = i_m_text(pre_type, next_type);
		pre_type = actual_chain->type;
		actual_chain = actual_chain->next;
	}
}

void	free_chain_lexer(t_lexer **root)
{
	t_lexer	*buff;

	buff = *root;
	*root = (*root)->next;
	free(buff->content);
	free(buff);
}

static int	i_m_space(int pre_type, int next_type)
{
	static int	trad_pre[] = {SPACE_, MUST_DELETE, MUST_DELETE, MUST_DELETE,
		SPACE_, SPACE_, SPACE_, SPACE_, SPACE_, MUST_DELETE, MUST_DELETE,
		MUST_DELETE, MUST_DELETE, MUST_DELETE, MUST_DELETE, MUST_DELETE,
		MUST_DELETE, MUST_DELETE, MUST_DELETE, MUST_DELETE, SPACE_,
		MUST_DELETE};
	static int	trad_next[] = {SPACE_, MUST_DELETE, MUST_DELETE, MUST_DELETE,
		SPACE_, SPACE_, SPACE_, SPACE_, SPACE_, MUST_DELETE, MUST_DELETE,
		MUST_DELETE, MUST_DELETE, MUST_DELETE, MUST_DELETE, MUST_DELETE,
		MUST_DELETE, MUST_DELETE, MUST_DELETE, MUST_DELETE, SPACE_,
		MUST_DELETE};
	int			mytype;

	mytype = SPACE_;
	(void)next_type;
	if (pre_type >= 0 && pre_type < MAX_TYPE)
		mytype = trad_pre[pre_type];
	if (mytype == SPACE_ && next_type >= 0 && next_type < MAX_TYPE)
		mytype = trad_next[next_type];
	return (mytype);
}

void	change_space(t_lexer **root)
{
	t_lexer	*actual_chain;
	int		pre_type;
	int		next_type;

	pre_type = UNDEFINED_TYPE;
	actual_chain = *root;
	while (actual_chain)
	{
		if (actual_chain->next)
			next_type = actual_chain->next->type;
		if (actual_chain->type == SPACE_)
			actual_chain->type = i_m_space(pre_type, next_type);
		pre_type = actual_chain->type;
		actual_chain = actual_chain->next;
	}
	while (*root)
	{
		if ((*root)->type == MUST_DELETE)
			free_chain_lexer(root);
		root = &((*root)->next);
	}
}
