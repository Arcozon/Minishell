/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geudes <geudes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 15:07:04 by geudes            #+#    #+#             */
/*   Updated: 2023/07/24 19:15:36 by geudes           ###   ########.fr       */
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
	static int	is_special[MAX_TYPE] = {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1,
		1, 1, 1, 1, 1, 0, 0, 0};
	static char	am_i_redirrect[MAX_TYPE] = {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1,
		1, 1, 0, 0, 0, 0, 0, 0};
	int			last_type_was_special;
	int			last_type;

	last_type = PIPE;
	last_type_was_special = 1;
	while (root)
	{
		if (last_type_was_special && root->type >= 0 && root->type < MAX_TYPE
			&& is_special[root->type] && !((last_type == PIPE || last_type == OR
					|| last_type == AND) && am_i_redirrect[root->type]))
			return (0);
		if (root->type >= 0 && root->type < MAX_TYPE)
		{
			last_type = root->type;
			last_type_was_special = is_special[last_type];
		}
		if (last_type_was_special && !root->next)
			return (0);
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
			if (root->content[0] != root->content[ft_strlen(root->content) - 1]
				|| ft_strlen(root->content) == 1)
				return (0);
		root = root->next;
	}
	return (1);
}

// Returns 1 if OK 0 if not
int	check_redirect(t_lexer *root)
{
	static char	am_i_redirrect[MAX_TYPE] = {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0,
		1, 1, 1, 0, 0, 0, 0, 0, 0};
	int			in_redirect;
	int			i;

	in_redirect = 0;
	while (root)
	{
		if (in_redirect && root->type != TEXT && root->type != TEXT_SQ
			&& root->type != TEXT_DQ)
			in_redirect = 0;
		else if (!in_redirect && am_i_redirrect[root->type])
			in_redirect = 1;
		if (in_redirect && root->type == TEXT)
		{
			i = -1;
			while (root->content && root->content[++i])
				if (root->content[i] == '*')
					return (0);
		}
		root = root->next;
	}
	return (1);
}

//Return 0 on OK, 1 or 2 on error depending on error type
int	syntax(t_lexer *root)
{
	int	return_value;

	return_value = 0;
	if (!check_parenthesis(root))
		return_value = (write(2,
					"Minishell: Syntax error: Missing parenthesis\n", 45), 2);
	if (!check_quote(root))
		return_value = (write(2, "Minishell: Syntax error: Missing quote\n",
					39), 2);
	if (!check_special(root))
		return_value = (write(2,
					"Minishell: Syntax error: Missing file or command\n", 49),
				2);
	if (!check_redirect(root))
		return_value = (write(2, "Minishell: Syntax error: Ambigous redirect\n",
					43), 1);
	if (return_value)
		return (g_cmd_exit = return_value, return_value);
	return (0);
}
