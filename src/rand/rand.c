/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rand.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geudes <geudes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 11:51:11 by geudes            #+#    #+#             */
/*   Updated: 2023/06/29 09:56:24 by geudes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static inline int	is_alphanum(char c)
{
	return ((c >= 97 && c <= 122) || (c >= 65 && c <= 90) || (c >= 48
			&& c <= 57));
}

char	*strnrand(int len)
{
	char	*out;
	char	b;
	char	fd;
	int		i;

	fd = open("/dev/urandom", O_RDONLY);
	if (fd == -1)
		return (0);
	out = malloc(sizeof(char) * (len + 1));
	if (!out)
		return (close(fd), out);
	out[0] = '.';
	out[len] = 0;
	i = 1;
	while (i < len)
	{
		if (read(fd, &b, 1) < 1)
			return (free(out), close(fd), (char *)0);
		if (is_alphanum(b))
			out[i++] = b;
	}
	close(fd);
	return (out);
}
