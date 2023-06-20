/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nriviere <nriviere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 10:52:28 by nriviere          #+#    #+#             */
/*   Updated: 2022/12/19 21:39:39 by nriviere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// Returns the length of str.
int	ft_strlen_gnl(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

// Returns an exact malloc'ed copy of up to ln characters from str.
char	*ft_strdup_gnl(char *str, int ln)
{
	int		i;
	int		len;
	char	*out;

	if (!str)
		return (0);
	len = ft_strlen_gnl(str);
	if (ln > len)
		ln = len;
	else if (ln < 0)
		ln = 0;
	i = 0;
	out = malloc(sizeof(char) * (ln + 1));
	if (!out)
		return (out);
	while (i < ln)
	{
		out[i] = str[i];
		i++;
	}
	out[i] = 0;
	return (out);
}

// Cut str in two, returning the first part as a new malloc'ed string
// and leaving the rest in str.
char	*ft_strncut(char **str, int ln)
{
	int		len;
	char	*out;
	char	*tmp;

	if (!str || !(*str))
		return (0);
	len = ft_strlen_gnl(*str);
	if (ln > len)
		ln = len;
	if (ln < 0)
		ln = len - 1;
	out = ft_strdup_gnl(*str, ln + 1);
	if (!out)
		return (out);
	tmp = ft_strdup_gnl((*str) + ln + 1, len - ln);
	if (!tmp)
		return (free(out), tmp);
	free((*str));
	if (tmp[0])
		*str = tmp;
	else
		*str = (free(tmp), (char *)0);
	return (out);
}

// Re-Allocate the previously allocated string in str,
// making the new string size bytes long,
// freeing str and returning the newly created string
void	*ft_realloc(char **str, size_t size)
{
	char	*out;
	size_t	ln;

	if (!str)
		return (0);
	ln = ft_strlen_gnl(*str);
	if (ln > size)
		return (0);
	out = malloc(sizeof(char) * (size + 1));
	if (!out)
		return (out);
	out[0] = 0;
	ft_strcat(out, *str);
	free((*str));
	return (out);
}
