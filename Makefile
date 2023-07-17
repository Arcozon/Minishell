NAME 	 = minishell

CC 		 = cc
CFLAGS 	 = -Wall -Wextra -Werror -g
RM 		 = rm -f

SRC_PATH = src/
OBJ_PATH = obj/
INC_PATH = inc/

SRC 	 = built_in/cd.c built_in/clear.c built_in/echo.c built_in/env.c built_in/exit.c built_in/export.c built_in/owo.c built_in/pwd.c built_in/unset.c built_in/which.c env.c euthanasia/euthanasia.c exec/exec.c exec/exec_redir.c exec/file_handling.c exec/file_handling_2.c exec/ft_printf.c exec/get_builtin.c exec/get_pid.c exec/here_doc.c exec/path_finding.c exec/path_handling_2.c exec/split.c exec/split_2.c expand2/double_quote.c expand2/expand_cmd.c expand2/expand_var.c expand2/single_quote.c expand2/text.c expand2/wildcardv2.c lexer/lexer.c lexer/lexer2.c lexer/lexer3.c lexer/lexer4.c main.c rand/rand.c signal/signal.c syntax/syntax.c tree/cmd.c tree/debug.c tree/node.c tree/opp.c tree/utils.c tree/utils2.c utils/free1.c utils/free2.c utils/ms_calloc.c utils/utils.c utils/utils2.c

OBJ 	 = $(addprefix $(OBJ_PATH), $(patsubst %.c,%.o,$(SRC)))

INC 	 = inc/minishell.h

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ -lreadline

$(OBJ) : $(OBJ_PATH)%.o : $(SRC_PATH)%.c $(INC)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -I$(INC_PATH) -c $< -o $@

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
