/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geudes <geudes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 14:05:07 by geudes            #+#    #+#             */
/*   Updated: 2023/06/15 05:12:37 by geudes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ptr;
	int		i;
	int		iptr;

	if (!s1 && !s2)
		return (0);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	i = 0;
	iptr = 0;
	ptr = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (ptr == 0)
		return (0);
	while (s1[i])
		ptr[iptr++] = s1[i++];
	i = 0;
	while (s2[i])
		ptr[iptr++] = s2[i++];
	ptr[iptr] = '\0';
	return (ptr);
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

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	*us1;
	unsigned char	*us2;
	size_t			i;

	i = 0;
	us1 = ((unsigned char *)s1);
	us2 = (unsigned char *)s2;
	if (!s1)
		return (-1);
	if (!s2)
		return (1);
	while (i < n && s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return ((unsigned int)(us1[i] - us2[i]));
		i++;
	}
	if (i < n && (s1[i] || s2[i]))
		return ((unsigned int)(us1[i] - us2[i]));
	return (0);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	i;

	if (!s)
		return (0);
	if (start > ft_strlen(s))
		return (ft_strdup(""));
	if (ft_strlen(s + start) < len)
		len = ft_strlen(s + start);
	str = malloc((len + 1) * sizeof(char));
	if (!str)
		return (0);
	i = -1;
	while (++i < len && ((s + start)[i]))
		str[i] = (s + start)[i];
	str[i] = '\0';
	return (str);
}
