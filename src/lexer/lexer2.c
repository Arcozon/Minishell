/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geudes <geudes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 19:05:21 by geudes            #+#    #+#             */
/*   Updated: 2023/01/26 11:16:04 by geudes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	aff_lexer(t_lexer *root)
{
	static char	*trad[] = {"TEXT", "FILE_INPUT", "FILE_OUTPUT", "FILE_ERROR",
		"CMD", "ARGS", "VAR", "TEXT_SQ", "TEXT_DQ", "INPUT_REDIR",
		"INPUT_HEREDOC", "HEREDOC_EOF", "OUTPUT_REDIR", "OUTPUT_HAPPEND_REDIR",
		"ERROR_REDIR", "PIPE", "AND", "OR", "OPEN_PAR", "CLOSE_PAR", "EQUAL",
		"SPACE"};

	while (root)
	{
		if (root->type >= 0 && root->type <= MAX_TYPE)
			printf("%s>%s<\n", trad[root->type], root->content);
		else
			printf("Errortype\n");
		root = root->next;
	}
}

static inline int	is_special_char(char c)
{
	return (c == ' ' || c == '|' || c == '(' || c == ')' || c == '='
		|| c == '<' || c == '>' || c == '\'' || c == '"');
}

void	get_text(const char *line, int *start, t_lexer **root)
{
	int		len;
	char	lastsep;

	len = 0;
	lastsep = line[*start];
	if (line[*start] && line[*start] == ' ')
		while (line[*start + len] && line[*start + len] == ' ')
			len++;
	else if (line[*start] && (line[*start] == '\'' || line[*start] == '"'))
		while (line[*start + ++len] && line[*start + len] != lastsep)
			;
	else
		while (line[*start + len] && !is_special_char(line[*start + len])
			&& ft_strncmp(line + *start + len, "&&", 2))
			len++;
	(*root)->type = TEXT;
	if (lastsep == '\'')
		(*root)->type = (len++, TEXT_SQ);
	else if (lastsep == '"')
		(*root)->type = (len++, TEXT_DQ);
	else if (lastsep == ' ')
		(*root)->type = SPACE_;
	(*root)->content = ft_substr(line, *start, len);
	(*start) += len;
}
