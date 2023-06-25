/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geudes <geudes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 15:07:04 by geudes            #+#    #+#             */
/*   Updated: 2023/06/25 10:27:58 by geudes           ###   ########.fr       */
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

// Returns 1 if OK 0 if not
int	check_redirect(t_lexer *root)
{
	static char	am_i_redirrect[] = {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1,
		1, 0, 0, 0, 0, 0, 0};
	int			last_was_redirect;

	last_was_redirect = 0;
	while (root)
	{
		if (last_was_redirect && root->type == TEXT)
		{
			last_was_redirect = -1;
			while (root->content && root->content[++last_was_redirect])
				if (root->content[last_was_redirect] == '*')
					return (0);
		}
		last_was_redirect = am_i_redirrect[root->type];
		root = root->next;
	}
	return (1);
}

int	syntax(t_lexer *root)
{
	if (!check_parenthesis(root))
		return (write(2, "Minishell: Syntax error: Missing parenthesis\n", 45),
			0);
	if (!check_quote(root))
		return (write(2, "Minishell: Syntax error: Missing quote\n", 39), 0);
	if (!check_special(root))
		return (write(2, "Minishell: Syntax error: Missing file or command\n",
				48), 0);
	if (!check_redirect(root))
		return (write(2, "Minishell: Syntax error: Ambigous redirect\n", 43), 0);
	return (1);
}
