/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_pid.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geudes <geudes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 13:06:36 by geudes            #+#    #+#             */
/*   Updated: 2023/07/05 13:06:51 by geudes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_get_pid(void)
{
	int		fd;
	int		pid;
	char	buf;

	fd = open("/proc/self/stat", O_RDONLY);
	if (fd == -1)
		return (-1);
	pid = 0;
	while (1)
	{
		if (read(fd, &buf, 1) == -1)
			return (close(fd), -1);
		if (buf == ' ' || buf < '0' || buf > '9')
			break ;
		pid = pid * 10 + buf - '0';
	}
	close(fd);
	return (pid);
}
