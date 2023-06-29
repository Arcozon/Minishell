S_BUILT_IN =  pwd.c  cd.c  echo.c  env.c  exit.c  export.c  unset.c  owo.c
D_BUILT_IN = built_in/
SRC_BUILT_IN = $(addprefix ${D_BUILT_IN}, ${S_BUILT_IN})

S_LEXER =  lexer.c  lexer2.c  lexer3.c  lexer4.c
D_LEXER = lexer/
SRC_LEXER = $(addprefix ${D_LEXER}, ${S_LEXER})

S_EXPAND =  double_quote.c  expand_cmd.c  expand_var.c  single_quote.c  text.c  wildcardv2.c
D_EXPAND = expand2/
SRC_EXPAND = $(addprefix ${D_EXPAND}, ${S_EXPAND})

S_SYNTAX =  syntax.c
D_SYNTAX =	syntax/
SRC_SYNTAX = $(addprefix ${D_SYNTAX}, ${S_SYNTAX})

S_TREE =  cmd.c  node.c  opp.c  utils.c  utils2.c  debug.c
D_TREE = tree/
SRC_TREE = $(addprefix ${D_TREE}, ${S_TREE})

S_EXEC = exec.c get_builtin.c
D_EXEC = exec/
SRC_EXEC = $(addprefix ${D_EXEC}, ${S_EXEC})

S_GNL = get_next_line.c get_next_line_utils.c
D_GNL = gnl/
SRC_GNL = $(addprefix $(D_GNL), $(S_GNL))

S_UTILS =  utils.c  utils2.c free1.c free2.c ms_calloc.c
D_UTILS = utils/
SRC_UTILS = $(addprefix ${D_UTILS}, ${S_UTILS})

S_EUTHA = euthanasia.c
D_EUTHA = euthanasia/
SRC_EUTHA = $(addprefix $(D_EUTHA), $(S_EUTHA))

S_SIGNAL = signal.c
D_SIGNAL = signal/
SRC_SIGNAL = $(addprefix $(D_SIGNAL), $(S_SIGNAL))

S_RAND = rand.c
D_RAND = rand/
SRC_RAND = $(addprefix $(D_RAND), $(S_RAND))

S_SRC = main.c  env.c  ${SRC_BUILT_IN}  ${SRC_LEXER}  ${SRC_SYNTAX}  ${SRC_UTILS}  ${SRC_EXPAND}  ${SRC_TREE} ${SRC_EXEC} $(SRC_GNL) $(SRC_RAND) $(SRC_SIGNAL) $(SRC_EUTHA)
D_SRC = ./src/
SRC = $(addprefix ${D_SRC}, ${S_SRC})

S_OBJ = ${S_SRC:.c=.o}
D_OBJ = ./obj/
OBJ = $(addprefix ${D_OBJ}, ${S_OBJ})

S_INC = minishell.h get_next_line.h
D_INC = ./inc/
INC = $(addprefix ${D_INC}, ${S_INC})


NAME = minishell

CC = cc

FLAGS = -Wall -Wextra -Werror -g

LFLAGS = -lreadline

${D_OBJ}%.o : ${D_SRC}%.c ${INC}
	${CC} ${FLAGS} -I${D_INC} -c $< -o $@

all	: ${NAME}

${NAME}	:	${D_OBJ}  ${OBJ}
	${CC} ${FLAGS} ${OBJ} -o${NAME} ${LFLAGS}

${D_OBJ}:
	mkdir -p ${D_OBJ}
	mkdir -p ${D_OBJ}${D_BUILT_IN}
	mkdir -p ${D_OBJ}${D_LEXER}
	mkdir -p ${D_OBJ}${D_EXPAND}
	mkdir -p ${D_OBJ}${D_SYNTAX}
	mkdir -p ${D_OBJ}${D_UTILS}
	mkdir -p ${D_OBJ}${D_TREE}
	mkdir -p ${D_OBJ}${D_EXEC}
	mkdir -p $(D_OBJ)$(D_GNL)
	mkdir -p $(D_OBJ)$(D_RAND)
	mkdir -p $(D_OBJ)$(D_SIGNAL)
	mkdir -p $(D_OBJ)$(D_EUTHA)

clean :
	rm -f ${OBJ}

fclean :
	rm -f ${NAME} ${OBJ}
	rm -rf ${D_OBJ}

re : fclean all

.PHONY : all clean fclean re
