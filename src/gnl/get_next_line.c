/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nriviere <nriviere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 10:52:02 by nriviere          #+#    #+#             */
/*   Updated: 2023/01/07 20:22:46 by nriviere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// Concatene the null-terminated string str1,
// at the end of the null-terminated string str.
void	ft_strcat(char *str, char *str1)
{
	int	i;
	int	i2;

	i = 0;
	i2 = 0;
	if (!str || !str1)
		return ;
	while (str[i])
		i++;
	while (str1[i2])
	{
		str[i + i2] = str1[i2];
		i2++;
	}
	str[i + i2] = 0;
}

static int	ft_check_endl(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (-1);
	while (str[i])
	{
		if (str[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

static int	get_next_time_sub(int i[4], int fd, char *buffer, char **fd_lines)
{
	while (i[0] > 0 && i[3] == -1)
	{
		i[0] = read(fd, buffer, BUFFER_SIZE);
		if (i[0] < 0)
			return (0);
		buffer[i[0]] = 0;
		if (i[0] > i[1])
		{
			while (i[0] > i[1])
			{
				i[1] += i[2];
				i[2] *= 2;
			}
			fd_lines[fd] = ft_realloc(&(fd_lines[fd]), i[2]);
		}
		ft_strcat(fd_lines[fd], buffer);
		i[1] -= i[0];
		i[3] = ft_check_endl(fd_lines[fd]);
		if (i[0] == 0)
			return (1);
	}
	return (1);
}

char	*get_next_line(int fd)
{
	static char	*fd_lines[MAXFD];
	char		*buffer;
	int			i[4];

	if (fd < 0 || fd > MAXFD)
		return (0);
	i[3] = ft_check_endl(fd_lines[fd]);
	if (i[3] != -1)
		return (ft_strncut(&(fd_lines[fd]), i[3]));
	i[0] = 1;
	i[1] = 0;
	i[2] = BUFFER_SIZE;
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (free(buffer), (char *)0);
	if (!get_next_time_sub(i, fd, buffer, fd_lines))
		return (free(buffer), (char *)0);
	free(buffer);
	return (ft_strncut(&(fd_lines[fd]), i[3]));
}
