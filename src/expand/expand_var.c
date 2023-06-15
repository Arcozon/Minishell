/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geudes <geudes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 22:44:10 by geudes            #+#    #+#             */
/*   Updated: 2023/06/15 05:25:13 by geudes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//char to ascii
const char	*g_ctoa[256] = {
	"0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13",
	"14", "15", "16", "17", "18", "19", "20", "21", "22", "23", "24", "25",
	"26", "27", "28", "29", "30", "31", "32", "33", "34", "35", "36", "37",
	"38", "39", "40", "41", "42", "43", "44", "45", "46", "47", "48", "49",
	"50", "51", "52", "53", "54", "55", "56", "57", "58", "59", "60", "61",
	"62", "63", "64", "65", "66", "67", "68", "69", "70", "71", "72", "73",
	"74", "75", "76", "77", "78", "79", "80", "81", "82", "83", "84", "85",
	"86", "87", "88", "89", "90", "91", "92", "93", "94", "95", "96", "97",
	"98", "99", "100", "101", "102", "103", "104", "105", "106", "107",
	"108", "109", "110", "111", "112", "113", "114", "115", "116", "117",
	"118", "119", "120", "121", "122", "123", "124", "125", "126", "127",
	"128", "129", "130", "131", "132", "133", "134", "135", "136", "137",
	"138", "139", "140", "141", "142", "143", "144", "145", "146", "147",
	"148", "149", "150", "151", "152", "153", "154", "155", "156", "157",
	"158", "159", "160", "161", "162", "163", "164", "165", "166", "167",
	"168", "169", "170", "171", "172", "173", "174", "175", "176", "177",
	"178", "179", "180", "181", "182", "183", "184", "185", "186", "187",
	"188", "189", "190", "191", "192", "193", "194", "195", "196", "197",
	"198", "199", "200", "201", "202", "203", "204", "205", "206", "207",
	"208", "209", "210", "211", "212", "213", "214", "215", "216", "217",
	"218", "219", "220", "221", "222", "223", "224", "225", "226", "227",
	"228", "229", "230", "231", "232", "233", "234", "235", "236", "237",
	"238", "239", "240", "241", "242", "243", "244", "245", "246", "247",
	"248", "249", "250", "251", "252", "253", "254", "255"};

//Shit is faster than ever
static char	*dup_return_value(void)
{
	if (g_cmd_exit >= 0 && g_cmd_exit <= 255)
		return (ft_strdup(g_ctoa[g_cmd_exit]));
	return (ft_strdup("0"));
}

//Give me the text after dollar and i ll give you the meaning
char	*expand_var_name(char *text, int *start, t_env *env)
{
	char	*var_name;
	int		i;

	i = 0;
	while (text[*start + i] && text[*start + i] != ' ' && text[*start
			+ i] != '\t' && text[*start + i] != '\n' && text[*start + i] != '$')
		i++;
	var_name = ft_substr(text, *start, i);
	*start += i;
	if (!ft_strncmp(var_name, RETURN_VAR, ft_strlen(RETURN_VAR) + 1))
		return (free(var_name), dup_return_value());
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
		return_str = ft_strjoin(return_str, text + i[0] - i[1]);
		free(buffer);
	}
	return (return_str);
}
