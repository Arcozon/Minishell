/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geudes <geudes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 21:05:54 by geudes            #+#    #+#             */
/*   Updated: 2023/07/20 21:12:10 by geudes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include <stdint.h>
#include <sys/stat.h>
#include <stdio.h>

#define F_BD "block device\n"
#define F_CD "character device\n"
#define F_D "directory\n"
#define F_FO "FIFO/pipe\n"
#define F_SL "symlink\n"
#define F_RG "regular file\n"
#define F_SK "socket\n"
#define F_UK "unknown\n"

static char	*g_err_strings[] = {F_UK, F_FO, F_CD, F_UK,
	F_D, F_UK, F_BD, F_UK, F_UK, F_UK, F_RG, F_UK, F_SL, F_UK, F_SK};

int64_t	ft_get_mode(char *filepath)
{
	struct stat	fs;

	if (stat(filepath, &fs) == -1)
		return (-1);
	return (fs.st_mode);
}

int	ft_is_file(char *filepath)
{
	int64_t	mode;

	mode = ft_get_mode(filepath);
	if (mode == -1)
	{
		perror(PROMPTERR);
		return (-1);
	}
	mode = mode & S_IFMT;
	if (mode != S_IFREG)
	{
		ft_putstr_to_fd(2, PROMPTERR);
		ft_putstr_to_fd(2, filepath);
		ft_putstr_to_fd(2, ": Is a ");
		ft_putstr_to_fd(2, g_err_strings[mode / 010000]);
		return (1);
	}
	return (0);
}
