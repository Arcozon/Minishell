/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcardv2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geudes <geudes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 05:09:43 by geudes            #+#    #+#             */
/*   Updated: 2023/06/16 20:20:25 by geudes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_patern(char *patern, char *str)
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

static char	*gimme_next_file_name(DIR *dir, char *patern)
{
	struct dirent	*f;

	f = readdir(dir);
	while (f && (f->d_name[0] == '.' || !check_patern(patern, f->d_name)))
		f = readdir(dir);
	if (!f)
		return (0);
	return (ft_strdup(f->d_name));
}

int	count_match(char *patern)
{
	struct dirent	*f;
	char			*pwd;
	DIR				*dir;
	int				count;

	pwd = get_pwd();
	count = 0;
	if (!pwd)
		return (write(2, "Minishell: wildcard: can't find pwd\n", 36), 0);
	dir = opendir(pwd);
	if (!dir)
		return (write(2, "Minishell: wildcard: can't open directory\n", 6),
			free(pwd), 0);
	f = readdir(dir);
	while (f && (f->d_name[0] == '.' || !check_patern(patern, f->d_name)))
	{
		++count;
		f = readdir(dir);
	}
	closedir(dir);
	return (count);
}

static char	**i_found_one(char *patern, int count)
{
	DIR		*dir;
	char	*pwd;
	char	**res;

	res = malloc (sizeof(char *) * (count + 1));
	if (!res)
		return (write(2, "Minishell: wildcard: Malloc error\n", 34),
			(char **)0);
	res[count] = 0;
	pwd = get_pwd();
	if (!pwd)
		return (free(res), (char **)0);
	dir = opendir(pwd);
	if (!dir)
		return (free(res), free(pwd), (char **)0);
	while (--count >= 0)
		res[count] = gimme_next_file_name(dir, patern);
	free(pwd);
	closedir(dir);
	return (res);
}

t_lexer	*expand_wc_v2(char *patern)
{
	char	**res;
	t_lexer	*lres;
	int		i;
	int		count;

	count = count_match(patern);
	if (!count)
	{
		res = malloc(sizeof(char *) * 2);
		if (!res)
			return (write(2, "Minishell: wildcard: Malloc error\n", 34),
				(t_lexer *)0);
		res[0] = ft_strdup(patern);
		res[1] = 0;
	}
	else
		res = i_found_one(patern, count);
	my_bbsort(res);
	i = -1;
	lres = 0;
	while (res[++i])
		(lexer_add_back(&lres, lexer_new(ARGS, res[i])),
			lexer_add_back(&lres, lexer_new(SPACE_, 0)));
	free(res);
	return (lres);
}
