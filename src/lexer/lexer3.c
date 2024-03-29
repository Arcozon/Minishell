/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geudes <geudes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 10:16:42 by geudes            #+#    #+#             */
/*   Updated: 2023/06/25 10:16:01 by geudes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	i_m_text(int pre_type, int next_type)
{
	static int	trad_pre[] = {TEXT, FILE_INPUT, FILE_OUTPUT, FILE_ERROR,
		TEXT, TEXT, TEXT, TEXT, FILE_INPUT, HEREDOC_EOF, HEREDOC_EOF,
		FILE_OUTPUT, FILE_OUTPUT, FILE_ERROR, CMD, TEXT, TEXT, TEXT, TEXT};
	static int	trad_next[] = {TEXT, FILE_INPUT, FILE_OUTPUT, FILE_ERROR,
		TEXT, TEXT, TEXT, TEXT, TEXT, TEXT, HEREDOC_EOF, TEXT, TEXT, TEXT,
		TEXT, TEXT, TEXT, TEXT, TEXT, TEXT};
	int			mytype;

	mytype = TEXT;
	(void)next_type;
	if (pre_type >= 0 && pre_type < MAX_TYPE)
		mytype = trad_pre[pre_type];
	if (mytype == TEXT && next_type >= 0 && next_type < MAX_TYPE)
		mytype = trad_next[next_type];
	return (mytype);
}

void	change_text(t_lexer *root, t_lexer *end_lexer)
{
	int		pre_type;
	int		next_type;

	pre_type = UNDEFINED_TYPE;
	while (root && root != end_lexer)
	{
		next_type = UNDEFINED_TYPE;
		if (root->next)
			next_type = root->next->type;
		if (root->type == TEXT)
			root->type = i_m_text(pre_type, next_type);
		pre_type = root->type;
		root = root->next;
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
		SPACE_, SPACE_, SPACE_, SPACE_, MUST_DELETE, MUST_DELETE,
		MUST_DELETE, MUST_DELETE, MUST_DELETE, MUST_DELETE, MUST_DELETE,
		MUST_DELETE, MUST_DELETE, MUST_DELETE, MUST_DELETE, MUST_DELETE};
	static int	trad_next[] = {SPACE_, MUST_DELETE, MUST_DELETE, MUST_DELETE,
		SPACE_, SPACE_, SPACE_, SPACE_, MUST_DELETE, MUST_DELETE,
		MUST_DELETE, MUST_DELETE, MUST_DELETE, MUST_DELETE, MUST_DELETE,
		MUST_DELETE, MUST_DELETE, MUST_DELETE, MUST_DELETE, MUST_DELETE};
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
	if (root && *root && (*root)->type == SPACE_)
		(*root)->type = MUST_DELETE;
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
		else
			root = &((*root)->next);
	}
}
