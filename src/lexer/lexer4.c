/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geudes <geudes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 00:09:13 by geudes            #+#    #+#             */
/*   Updated: 2023/07/05 15:04:17 by geudes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_lexer	*lexer_new(int type, char *content)
{
	t_lexer	*new;

	new = malloc(sizeof(t_lexer));
	if (!new)
	{
		write(2, "Minishel: lexer: malloc error\n", 30);
		return (0);
	}
	new->content = content;
	new->type = type;
	new->next = 0;
	return (new);
}

void	lexer_add_back(t_lexer **root, t_lexer *new)
{
	if (!root)
		return ;
	while (*root)
		root = &((*root)->next);
	*root = new;
}

void	aff_lexer(t_lexer *root, t_lexer *end_lexer)
{
	static char	*trad[] = {"TEXT", "FILE_INPUT", "FILE_OUTPUT", "FILE_ERROR",
		"CMD", "ARGS", "TEXT_SQ", "TEXT_DQ", "INPUT_REDIR",
		"INPUT_HEREDOC", "HEREDOC_EOF", "OUTPUT_REDIR", "OUTPUT_HAPPEND_REDIR",
		"ERROR_REDIR", "PIPE", "AND", "OR", "OPEN_PAR", "CLOSE_PAR",
		"SPACE"};

	while (root && root != end_lexer)
	{
		if (root->type >= 0 && root->type <= MAX_TYPE)
			printf("%s>%s<\n", trad[root->type], root->content);
		else
			printf("Errortype %d\n", root->type);
		root = root->next;
	}
}
