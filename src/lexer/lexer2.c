/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geudes <geudes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 19:05:21 by geudes            #+#    #+#             */
/*   Updated: 2023/02/06 08:27:51 by geudes           ###   ########.fr       */
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

static inline int	lasttypeisundefined(int type)
{
	static int	typemap[] = {0, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1};

	if (type >= 0 && type < MAX_TYPE)
		return (typemap[type]);
	return (0);
}

// Arcozon war here, info&1 for i m in var, info&2 for i m in cmd
void	change_text_into_cmd_args_but_not_var(t_lexer *root)
{
	int	info;

	info = 0;
	while (root)
	{
		if (root->type == TEXT && !info)
		{
			root->type = CMD;
			info |= 2;
		}
		else if (root->type == TEXT && info & 2 && !(info & 1))
			root->type = ARGS;
		else if (lasttypeisundefined(root->type) && !(info & 2))
			info = 0;
		if (!(info & 2) && root->type == EQUAL)
			info |= 1;
		root = root->next;
	}
}
