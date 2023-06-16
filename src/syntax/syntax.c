/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geudes <geudes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 15:07:04 by geudes            #+#    #+#             */
/*   Updated: 2023/06/16 20:03:06 by geudes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Returns 1 if OK 0 if not
int	check_parenthesis(t_lexer *root)
{
	int	n_par;

	n_par = 0;
	while (root)
	{
		if (root->type == CLOSE_PAR)
			n_par--;
		else if (root->type == OPEN_PAR)
			n_par++;
		if (n_par < 0)
			return (0);
		root = root->next;
	}
	return (n_par == 0);
}

// Returns 1 if OK 0 if not
int	check_special(t_lexer *root)
{
	static int	is_special[] = {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1,
		1, 1, 1, 1, 0, 0, 0};
	int			last_type_was_special;

	last_type_was_special = 0;
	while (root)
	{
		if (last_type_was_special && root->type >= 0 && root->type < MAX_TYPE
			&& is_special[root->type])
			return (0);
		if (root->type >= 0 && root->type < MAX_TYPE)
			last_type_was_special = is_special[root->type];
		root = root->next;
	}
	return (1);
}

// Returns 1 if OK 0 if not
int	check_cmd(t_lexer *root)
{
	int			last_saw_sep;

	last_saw_sep = 1;
	while (root)
	{
		if (last_saw_sep && (root->type == CMD || root->type == ARGS))
			last_saw_sep = 0;
		else if (!last_saw_sep && root->type >= PIPE
			&& root->type <= CLOSE_PAR)
			last_saw_sep = 1;
		else if (last_saw_sep && root->type >= PIPE && root->type <= CLOSE_PAR)
			return (0);
	}
	return (1);
}

// Returns 1 if OK 0 if not
int	check_quote(t_lexer *root)
{
	while (root)
	{
		if (root->type == TEXT_SQ || root->type == TEXT_DQ)
			if (root->content[0] != root->content[ft_strlen(root->content) - 1])
				return (0);
		root = root->next;
	}
	return (1);
}

int	syntax(t_lexer *root)
{
	if (!check_cmd(root))
		return (write(2, "Minishell: Syntax error: Missing command", 40), 0);
	if (!check_cmd(root))
		return (write(2, "Minishell: Syntax error: Missing parenthesis", 44),
			0);
	if (!check_quote(root))
		return (write(2, "Minishell: Syntax error: Missing quote", 38), 0);
	if (!check_special(root))
		return (write(2, "Minishell: Syntax error: Missing file", 37), 0);
	//bash: *: ambiguous redirect
	return (1);
}
