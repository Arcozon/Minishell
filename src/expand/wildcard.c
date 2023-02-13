/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geudes <geudes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 23:51:10 by geudes            #+#    #+#             */
/*   Updated: 2023/02/13 16:49:48 by geudes           ###   ########.fr       */
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

int	count_curdir(char *pwd, char *patern)
{
	struct dirent	*files;
	DIR				*dir;
	int				count;
	int				ret;

	dir = opendir(pwd);
	if (!dir)
		return (write(2, "error\n", 6), 0);
	count = 0;
	ret = 1;
	files = readdir(dir);
	if (files && (files->d_name[0] == '.' || !wildcard(patern, files->d_name)))
		count --;
	while (files)
	{
		count++;
		files = readdir(dir);
		if (!files)
			break ;
		if (files->d_name[0] == '.' || !wildcard(patern, files->d_name))
			count --;
	}
	closedir(dir);
	return (count);
}

char	*gimme_next_file_name(DIR *dir, char *patern)
{
	struct dirent	*f;
	char			*res;

	f = readdir(dir);
	while (f && (f->d_name[0] == '.' || !wildcard(patern, f->d_name)))
		f = readdir(dir);
	if (!f)
		return (0);
	res = ft_strdup(f->d_name);
	return (res);
}

void	expand_wc(char *patern)
{

}
