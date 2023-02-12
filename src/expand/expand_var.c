/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geudes <geudes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 22:44:10 by geudes            #+#    #+#             */
/*   Updated: 2023/02/12 06:29:52 by geudes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*dup_returnv(void)
{
	if (g_cmd_exit == 1)
		return (ft_strdup("1"));
	if (g_cmd_exit == 130)
		return (ft_strdup("130"));
	if (g_cmd_exit == 130)
		return (ft_strdup("127"));
	if (g_cmd_exit == 131)
		return (ft_strdup("131"));
	return (ft_strdup("0"));
}

//Give me the text after dollar and i ll give you the meaning
char	*expand_var_name(char *text, int *start, t_env *env)
{
	char	*var_name;
	int		i;

	i = 0;
	while (text[*start + i] && text[*start + i] != ' ' && text[*start + i]
		!= '\t' && text[*start + i] != '\n' && text[*start + i] != '$')
		i++;
	var_name = ft_substr(text, *start, i);
	*start += i;
	if (!ft_strncmp(var_name, RETURN_VAR, ft_strlen(RETURN_VAR) + 1))
		return (free(var_name), dup_returnv());
	while (env)
	{
		if (!ft_strncmp(var_name, env->var_name, ft_strlen(env->var_name) + 1))
			break ;
		env = env->next;
	}
	free(var_name);
	if (env)
		return (ft_strdup(env->content));
	return (ft_strdup(""));
}

//They actually found a dollar
static char	*hey_i_found_one_euro(char *text, int i[2], char *return_str,
	t_env *env)
{
	char	*buffer;
	char	*var_value;

	var_value = ft_substr(text, i[0] - i[1], i[1]);
	buffer = return_str;
	return_str = ft_strjoin(return_str, var_value);
	(free(buffer), free(var_value));
	i[0]++;
	i[1] = 0;
	var_value = expand_var_name(text, i, env);
	buffer = return_str;
	return_str = ft_strjoin(return_str, var_value);
	(free(buffer), free(var_value));
	return (return_str);
}

char	*expand_dollar_sign(char *text, t_env *env)
{
	char	*return_str;
	char	*buffer;
	int		i[2];

	i[0] = 0;
	i[1] = 0;
	return_str = ft_strdup("");
	while (text[i[0]])
	{
		if (text[i[0]] == '$')
			return_str = hey_i_found_one_euro(text, i, return_str, env);
		else
			i[0] += (i[1]++, 1);
	}
	if (i[1])
	{
		buffer = return_str;
		return_str = ft_strjoin(return_str, text + i[0] - i [1]);
		free(buffer);
	}
	return (return_str);
}
