/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   owo.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geudes <geudes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 02:42:20 by geudes            #+#    #+#             */
/*   Updated: 2023/07/05 10:36:50 by geudes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#define MAX_EMOJIES 7

static const char	*g_lookuptable[128] = {
[0] = "\x00", [1] = "\x01", [2] = "\x02", [3] = "\x03", [4] = "\x04",
[5] = "\x05", [6] = "\x06", [7] = "\x07", [8] = "\x08",
[9] = "\x09", [10] = "\x0A", [11] = "\x0B", [12] = "\x0C",
[13] = "\x0D", [14] = "\x0E", [15] = "\x0F", [16] = "\x10",
[17] = "\x11", [18] = "\x12", [19] = "\x13", [20] = "\x14",
[21] = "\x15", [22] = "\x16", [23] = "\x17", [24] = "\x18",
[25] = "\x19", [26] = "\x1A", [27] = "\x1B", [28] = "\x1C",
[29] = "\x1D", [30] = "\x1E", [31] = "\x1F", [32] = " ", [33] = "!",
[34] = "\"", [35] = "#", [36] = "$", [37] = "%", [38] = "&",
[39] = "'", [40] = "(", [41] = ";)", [42] = "*", [43] = "+",
[44] = ",", [45] = "-", [46] = ".", [47] = "/", [48] = "0w0",
[49] = "1", [50] = "2", [51] = ":3", [52] = "4", [53] = "5",
[54] = "6", [55] = "7", [56] = "8", [57] = "9", [58] = ":",
[59] = ";", [60] = "<", [61] = "=", [62] = "'>'", [63] = "?",
[64] = "@", [65] = "A", [66] = "B", [67] = "C", [68] = "D",
[69] = "E", [70] = "F", [71] = "G", [72] = "H", [73] = "I",
[74] = "J", [75] = "K", [76] = "L", [77] = "M", [78] = "N",
[79] = "OzO", [80] = "P", [81] = "Q", [82] = "R", [83] = "S",
[84] = "T", [85] = "UzU", [86] = "V", [87] = "W", [88] = "XoXo",
[89] = "Y", [90] = "Z", [91] = "[", [92] = "\\", [93] = "]",
[94] = "^^", [95] = "_", [96] = "`", [97] = "a", [98] = "b",
[99] = "c", [100] = "d", [101] = "e", [102] = "f", [103] = "g",
[104] = "h", [105] = "i", [106] = "j", [107] = "k", [108] = "l",
[109] = "m", [110] = "n", [111] = "oWo", [112] = "p", [113] = "q",
[114] = "w", [115] = "s", [116] = "t", [117] = "uWu", [118] = "v",
[119] = "w", [120] = "xoxo", [121] = "y", [122] = "z", [123] = "{",
[124] = "|", [125] = "}", [126] = "~", [127] = "\x7F"};

// Returns 0 on succes 1 on error
int	bi_owo(t_lcmd *lcmd, t_minishell *ms)
{
	static const char	*end_str[MAX_EMOJIES] = {"❤💕💜💞💖💙", "(｡♥‿♥｡)",
		"(⁄ ⁄•⁄ω⁄•⁄ ⁄)", "(◕ᴗ◕✿)", "🌸🌺🌼", "ʕ•́ᴥ•̀ʔっ", "(づ｡◕‿‿◕｡)づ"};
	static int			cmptr = 0;
	int					i;
	int					j;

	j = 1;
	(void)ms;
	while (lcmd->cmd[j])
	{
		i = -1;
		while (lcmd->cmd[j][++i])
			write(lcmd->output, g_lookuptable[(int)lcmd->cmd[j][i]],
				ft_strlen((char *)g_lookuptable[(int)lcmd->cmd[j][i]]));
		write(lcmd->output, " ", 1);
		write(lcmd->output, end_str[cmptr % MAX_EMOJIES],
			ft_strlen((char *)end_str[cmptr % MAX_EMOJIES]));
		write(lcmd->output, "\n", 1);
		++cmptr;
		++j;
	}
	return (0);
}
