/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geudes <geudes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 19:05:21 by geudes            #+#    #+#             */
/*   Updated: 2023/07/16 18:48:06 by geudes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static inline int	is_special_char(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '|' || c == '('
		|| c == ')' || c == '<' || c == '>' || c == '\'' || c == '"');
}

static int	whatsmytype(char lastsep)
{
	if (lastsep == '\'')
		return (TEXT_SQ);
	else if (lastsep == '"')
		return (TEXT_DQ);
	else if (lastsep == ' ' || lastsep == '\t' || lastsep == '\n')
		return (SPACE_);
	return (TEXT);
}

void	get_text(const char *line, int *start, t_lexer **root)
{
	int		len;
	char	lastsep;

	len = 0;
	lastsep = line[*start];
	if (line[*start] && (line[*start] == ' ' || line[*start] == '\t'))
		while (line[*start + len] && (line[*start + len] == ' '
				|| line[*start + len] == '\t' || line[*start + len] == '\n'))
			len++;
	else if (line[*start] && (line[*start] == '\'' || line[*start] == '"'))
		while (line[*start + ++len] && line[*start + len] != lastsep)
			;
	else
		while (line[*start + len] && !is_special_char(line[*start + len])
			&& ft_strncmp(line + *start + len, "&&", 2))
			len++;
	(*root)->type = whatsmytype(lastsep);
	if ((lastsep == '\'' || lastsep == '"') && line[*start + len])
		++len;
	free((*root)->content);
	(*root)->content = ft_substr(line, *start, len);
	(*start) += len;
}

static inline int	lasttypeisundefined(int type)
{
	static int	typemap[] = {0, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1};

	if (type >= 0 && type < MAX_TYPE)
		return (typemap[type]);
	return (0);
}

void	change_text_into_cmd_args(t_lexer *root, t_lexer *end_lexer)
{
	int	i_m_in_cmd;

	i_m_in_cmd = 0;
	while (root && root != end_lexer)
	{
		if (root->type == TEXT && !i_m_in_cmd)
		{
			root->type = CMD;
			while (root && root != end_lexer && root->type != SPACE_)
			{
				if (root->type == TEXT)
					root->type = CMD;
				root = root->next;
			}
			if (!root || root == end_lexer)
				break ;
			i_m_in_cmd = 1;
		}
		else if (root->type == TEXT && i_m_in_cmd)
			root->type = ARGS;
		else if (lasttypeisundefined(root->type) && !i_m_in_cmd)
			i_m_in_cmd = 0;
		if (root)
			root = root->next;
	}
}
