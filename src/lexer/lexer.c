/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geudes <geudes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 13:56:07 by geudes            #+#    #+#             */
/*   Updated: 2023/07/16 18:50:06 by geudes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	short_add_chain(t_lexer **root, const char *line, int *start, int t)
{
	static int	len[] = {0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 0, 1, 2, 2,
		1, 2, 2, 1, 1, 0};

	(*root)->type = t;
	(*root)->content = ft_substr(line, *start, len[t]);
	(*start) += len[t];
}

static void	add_chain2(t_lexer **root, const char *line, int *start)
{
	if (!ft_strncmp(line + *start, "&&", 2))
		short_add_chain(root, line, start, AND);
	else if (!ft_strncmp(line + *start, "||", 2))
		short_add_chain(root, line, start, OR);
	else if (line[*start] == '|')
		short_add_chain(root, line, start, PIPE);
	else if (line[*start] == '(')
		short_add_chain(root, line, start, OPEN_PAR);
	else if (line[*start] == ')')
		short_add_chain(root, line, start, CLOSE_PAR);
	else
		get_text(line, start, root);
}

void	add_chain(t_lexer **root, const char *line, int *start,
	t_minishell *ms)
{
	while (*root)
		root = &((*root)->next);
	*root = malloc(sizeof(t_lexer));
	awaiting_death(!*root, ms);
	(*root)->content = 0;
	(*root)->type = ERROR;
	(*root)->next = 0;
	if (!ft_strncmp(line + *start, "<<", 2))
		short_add_chain(root, line, start, INPUT_HEREDOC);
	else if (!ft_strncmp(line + *start, ">>", 2))
		short_add_chain(root, line, start, OUTPUT_HAPPEND_REDIR);
	else if (!ft_strncmp(line + *start, "2>", 2))
		short_add_chain(root, line, start, ERROR_REDIR);
	else if (line[*start] == '>')
		short_add_chain(root, line, start, OUTPUT_REDIR);
	else if (line[*start] == '<')
		short_add_chain(root, line, start, INPUT_REDIR);
	else
		add_chain2(root, line, start);
	awaiting_death(!(*root)->content, ms);
}

t_lexer	*lexer(const char *line, t_minishell *ms)
{
	t_lexer	*root;
	int		start;

	start = 0;
	root = 0;
	while (line[start])
		add_chain(&root, line, &start, ms);
	change_space(&root);
	return (root);
}
