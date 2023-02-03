/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geudes <geudes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 15:07:04 by geudes            #+#    #+#             */
/*   Updated: 2023/02/03 17:14:35 by geudes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Returns 1 if OK 0 if not
int	check_parenthesis(t_lexer *root)
{
	int	last_type;
	int	n_op;
	int	n_cp;

	n_op = 0;
	n_cp = 0;
	last_type = UNDEFINED_TYPE;
	while (root)
	{
		if ((root->type == CLOSE_PAR && last_type == OPEN_PAR)
			|| (root->type == OPEN_PAR && last_type == CLOSE_PAR))
			return (0);
		if (root->type == CLOSE_PAR)
			n_cp++;
		else if (root->type == OPEN_PAR)
			n_op++;
		last_type = root->type;
		root = root->next;
	}
	if (n_op != n_cp)
		return (0);
	return (1);
}

// Returns 1 if OK 0 if not
int	check_special(t_lexer *root)
{
	static int	is_special[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1,
		1, 1, 1, 1, 0, 0, 1};
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

int	syntax(t_lexer *root)
{
	return (check_parenthesis(root) && check_special(root));
}
