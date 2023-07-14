#include "../../inc/minishell.h"

static int	ft_get_words(const char *s, char sep)
{
	int	length;
	int	words;

	length = 0;
	words = 0;
	while (*s)
	{
		if (*s == sep)
		{
			if (length > 0)
			{
				words++;
				length = 0;
			}
		}
		else
			length++;
		s++;
	}
	if (length)
		words++;
	return (words);
}

char	*ft_substr_split(char const *s, unsigned int start, size_t len)
{
	char	*out;
	size_t	i;
	size_t	len_s;

	if (!s)
		return (0);
	len_s = (unsigned int)ft_strlen((char *)s);
	if (start <= 0 || start >= len_s)
		start = 0;
	if (len_s <= start)
		len = 0;
	if (len > len_s - start || len <= 0)
		len = len_s - start;
	i = 0;
	out = ft_calloc(len + 1, sizeof(char));
	if (out)
	{
		while (i < len && s[start + i])
		{
			out[i] = s[start + i];
			i++;
		}
	}
	return (out);
}

static int	ft_get_next_word(const char *s, char c, char **out)
{
	int	start;
	int	length;

	start = 0;
	length = 0;
	while (s[start] && s[start] == c)
		start++;
	while (s[start + length] && s[start + length] != c)
		length++;
	*out = ft_substr_split(s, start, length);
	return (start + length);
}

char	**ft_split(char const *s, char c)
{
	char	**out;
	int		size;
	int		i;
	int		ln;

	if (!s)
		return (0);
	size = ft_get_words(s, c);
	out = ft_calloc(size + 1, sizeof(char *));
	ln = 0;
	i = 0;
	if (!out)
		return (out);
	while (i < size)
	{
		ln += ft_get_next_word(s + ln, c, &out[i]);
		if (!out[i])
		{
			ft_free_strr(out);
			return (out);
		}
		i++;
	}
	out[i] = 0;
	return (out);
}

