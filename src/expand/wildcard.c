/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geudes <geudes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 23:51:10 by geudes            #+#    #+#             */
/*   Updated: 2023/02/15 04:28:30 by geudes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_patern(char *patern, char *str)
{
	if (!patern[0] && !str[0])
		return (1);
	if (patern[0] == '*')
		while (patern[1] == '*')
			patern++;
	if (patern[0] == '*' && patern[1] && !str[0])
		return (0);
	if (patern[0] == str[0])
		return (check_patern(patern + 1, str + 1));
	if (patern[0] == '*')
		return (check_patern(patern + 1, str) || check_patern(patern, str + 1));
	return (0);
}

char	*gimme_next_file_name(DIR *dir, char *patern)
{
	struct dirent	*f;

	f = readdir(dir);
	while (f && (f->d_name[0] == '.' || !check_patern(patern, f->d_name)))
		f = readdir(dir);
	if (!f)
		return (0);
	return (ft_strdup(f->d_name));
}

t_lexer	*find_all_wc(char *patern)
{
	char	*text;
	t_lexer	*res;
	DIR		*dir;

	text = get_pwd();
	if (!text)
		return (write(2, "Minishell: wildcard: can't find pwd\n", 36),
			(t_lexer *)0);
	res = 0;
	dir = opendir(text);
	if (!dir)
		return (write(2, "Minishell: wildcard: can't open directory\n", 6),
			free(text), (t_lexer *)0);
	text = (free(text), gimme_next_file_name(dir, patern));
	if (!text)
		return (write(2, "Minishell: wildcard: No match\n", 30),
			lexer_new(TEXT, ft_strdup(patern)));
	while (text)
	{
		lexer_add_back(&res, lexer_new(SPACE_, 0));
		lexer_add_back(&res, lexer_new(TEXT, text));
		text = gimme_next_file_name(dir, patern);
	}
	return (closedir(dir), res);
}

void	expand_wc(t_lexer **root)
{
	t_lexer	*next;
	char	*patern;

	next = (*root)->next;
	patern = (*root)->content;
	free(*root);
	*root = find_all_wc(patern);
	free(patern);
	lexer_add_back(root, next);
}
