/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nriviere <nriviere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 22:44:10 by geudes            #+#    #+#             */
/*   Updated: 2023/07/15 18:50:35 by nriviere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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
	while (g_cmd_exit > 255)
		g_cmd_exit -= 256;
	while (g_cmd_exit < 0)
		g_cmd_exit += 256;
	return (ft_strdup(g_ctoa[g_cmd_exit]));
}

//Give me the text after dollar and i ll give you the meaning
char	*expand_var_name(char *var_name, t_env *env)
{
	if (!ft_strncmp(var_name, RETURN_VAR, ft_strlen(RETURN_VAR) + 1))
		return (dup_return_value());
	while (env)
	{
		if (!ft_strncmp(var_name, env->var_name, ft_strlen(env->var_name) + 1))
			break ;
		env = env->next;
	}
	if (env)
		return (ft_strdup(env->content));
	return (ft_strdup(""));
}

char	*join_n_find_var(char *text, int *i, char *return_str, t_minishell *ms)
{
	char	*buff;
	char	*var_name;
	char	*var_content;
	int		len;

	++*i;
	len = 0;
	if (!((text[*i] >= 'a' && text[*i] <= 'z') || (text[*i] >= 'A'
				&& text[*i] <= 'Z') || (text[*i] >= '0' && text[*i] <= '9')))
		len = 1;
	else
		while (text[*i + len] && text[*i + len] != ' ' && text[*i + len] != '\t'
			&& text[*i + len] != '\n' && text[*i + len] != '$')
			++len;
	var_name = ft_substr(text, *i, len);
	awaiting_death(!var_name, ms);
	var_content = expand_var_name(var_name, ms->env);
	awaiting_death(!var_content, ms);
	buff = return_str;
	return_str = ft_strjoin(return_str, var_content);
	(free(buff), free(var_name), free(var_content));
	awaiting_death(!return_str, ms);
	*i += len;
	return (return_str);
}

char	*join_rest_text(char *text, char *return_str, int i, int len)
{
	char	*buff;
	char	*rest;

	rest = ft_substr(text, i, len);
	if (!rest)
		return (0);
	buff = return_str;
	return_str = ft_strjoin(return_str, rest);
	(free(buff), free(rest));
	return (return_str);
}

char	*expand_dollar_sign(char *text, t_minishell *ms)
{
	char	*return_str;
	int		last_find;
	int		i;

	i = 0;
	last_find = 0;
	return_str = ft_strdup("");
	awaiting_death(!return_str, ms);
	while (text[i])
	{
		if (text[i] == '$')
		{
			return_str = join_rest_text(text, return_str, last_find,
					i - last_find);
			awaiting_death(!return_str, ms);
			return_str = join_n_find_var(text, &i, return_str, ms);
			last_find = i;
		}
		else
			++i;
	}
	return_str = join_rest_text(text, return_str, last_find, i - last_find);
	awaiting_death(!return_str, ms);
	return (return_str);
}
