S_BUILT_IN =  pwd.c  cd.c  echo.c  env.c  exit.c
D_BUILT_IN = built_in/
SRC_BUILT_IN = $(addprefix ${D_BUILT_IN}, ${S_BUILT_IN})

S_LEXER =  lexer.c  lexer2.c  lexer3.c
D_LEXER = lexer/
SRC_LEXER = $(addprefix ${D_LEXER}, ${S_LEXER})

S_SYNTAX =  syntax.c
D_SYNTAX = syntax/
SRC_SYNTAX = $(addprefix ${D_SYNTAX}, ${S_SYNTAX})

S_UTILS =  utils.c  utils2.c
D_UTILS = utils/
SRC_UTILS = $(addprefix ${D_UTILS}, ${S_UTILS})

S_SRC = main.c    ${SRC_BUILT_IN}  ${SRC_LEXER}  ${SRC_SYNTAX}  ${SRC_UTILS}
D_SRC = ./src/
SRC = $(addprefix ${D_SRC}, ${S_SRC})

S_OBJ = ${S_SRC:.c=.o}
D_OBJ = ./obj/
OBJ = $(addprefix ${D_OBJ}, ${S_OBJ})

S_INC = minishell.h
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
	mkdir -p ${D_OBJ}${D_SYNTAX}
	mkdir -p ${D_OBJ}${D_UTILS}

clean :
	rm -f ${OBJ}

fclean :
	rm -f ${NAME} ${OBJ}

re : fclean all

.PHONY : all clean fclean re
