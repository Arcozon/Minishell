NAME 	 = minishell

CC 		 = cc
CFLAGS 	 = -Wall -Wextra -Werror
RM 		 = rm -f

SRC_PATH = src/
OBJ_PATH = obj/
INC_PATH = inc/

SRC 	 = signal/signal.c utils/ms_calloc.c utils/free2.c utils/utils2.c utils/free1.c utils/utils.c main.c euthanasia/euthanasia.c gnl/get_next_line_utils.c gnl/get_next_line.c expand2/text.c expand2/single_quote.c expand2/expand_var.c expand2/wildcardv2.c expand2/expand_cmd.c expand2/double_quote.c exec/path_finding.c exec/exec.c exec/get_pid.c exec/split.c exec/get_builtin.c exec/file_handling_2.c exec/split_2.c exec/here_doc.c exec/exec_redir.c exec/path_handling_2.c exec/file_handling.c rand/rand.c env.c lexer/lexer.c lexer/lexer2.c lexer/lexer4.c lexer/lexer3.c tree/cmd.c tree/utils2.c tree/opp.c tree/debug.c tree/node.c tree/utils.c built_in/owo.c built_in/unset.c built_in/exit.c built_in/clear.c built_in/cd.c built_in/env.c built_in/echo.c built_in/which.c built_in/export.c built_in/pwd.c syntax/syntax.c

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
