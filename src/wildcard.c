/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geudes <geudes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 12:10:58 by geudes            #+#    #+#             */
/*   Updated: 2023/02/09 03:03:03 by geudes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>

int	wildcard(char *patern, char *str)
{
	if (!patern[0] && !str[0])
		return (1);
	if (patern[0] == '*')
		while (patern[1] == '*')
			patern++;
	if (patern[0] == '*' && patern[1] && !str[0])
		return (0);
	if (patern[0] == str[0])
		return (wildcard(patern + 1, str + 1));
	if (patern[0] == '*')
		return (wildcard(patern + 1, str) || wildcard(patern, str + 1));
	return (0);
}

char	*get_pwd(void)
{
	size_t	size_path;
	char	*path;

	size_path = 32;
	path = malloc(size_path * sizeof(char));
	if (!path)
		return (0);
	while (!getcwd(path, size_path))
	{
		free(path);
		size_path <<= 1;
		path = malloc(size_path * sizeof(char));
		if (!path)
			return (0);
	}
	return (path);
}

size_t	ft_strlen(const char *s)
{
	size_t	len;

	if (!s)
		return (0);
	len = 0;
	while (s[len])
		len++;
	return (len);
}

char	*ft_strdup(const char *s)
{
	char	*str;
	int		i;

	str = 0;
	str = malloc((ft_strlen(s) + 1) * sizeof(char));
	if (!str)
		return (0);
	i = 0;
	while (s[i])
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
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

char	**thats_a_ls(char *patern)
{
	char	*pwd;
	int		count[2];
	char	**res;
	DIR		*dir;

	pwd = get_pwd();
	if (!pwd)
		return (write(2, "error\n", 6), (char **)0);
	count[0] = count_curdir(pwd, patern);
	res = malloc(sizeof(char *) * (count[0] + 1));
	if (!res)
		return (write(2, "error\n", 6), free(pwd), (char **)0);
	dir = opendir(pwd);
	if (!dir)
		return (write(2, "error\n", 6), free(res), free(pwd), (char **)0);
	count[1] = 0;
	while (count[1] < count[0])
		res[count[1]++] = gimme_next_file_name(dir, patern);
	res[count[1]] = 0;
	closedir(dir);
	free(pwd);
	return (res);

}

int	main(int ac, char **av)
{
	int		i;
	char	**resls;

	if (ac < 2)
		return (0);
	printf("Patern:>%s<\n", av[1]);
	i = 0;
	resls = thats_a_ls(av[1]);
	if (!resls)
		return (0);
	while (resls[i])
	{
		printf("%s\n", resls[i]);
		free(resls[i]);
		i++;
	}
	free(resls);
	return (0);
}
