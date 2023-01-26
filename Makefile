S_BUILT_IN =  pwd.c  cd.c  echo.c  env.c  exit.c
D_BUILT_IN = built_in/
SRC_BUILT_IN = $(addprefix ${D_BUILT_IN}, ${S_BUILT_IN})
BUILT_INT = $(addprefix ${D_SRC}, ${SRC_BUILT_IN})

S_SRC = main.c  utils.c  get_cmd.c  parsing.c  lexer.c  lexer2.c  lexer3.c
D_SRC = ./src/
SRC = $(addprefix ${D_SRC}, ${S_SRC}) ${SRC_BUILT_IN}

S_OBJ = ${S_SRC:.c=.o} ${SRC_BUILT_IN:.c=.o}
D_OBJ = ./obj/
OBJ = $(addprefix ${D_OBJ}, ${S_OBJ})

S_INC = minishell.h
D_INC = ./inc/
INC = $(addprefix ${D_INC}, ${S_INC})


NAME = minishell

CC = cc

FLAGS = -Wall -Wextra -Werror -g

LFLAGS = ${FLAGS} -lreadline

${D_OBJ}%.o : ${D_SRC}%.c ${INC}
	${CC} ${FLAGS} -I${D_INC} -c $< -o $@

all	: ${NAME}

${NAME}	:	${D_OBJ}  ${OBJ}
	${CC} ${LFLAGS} ${OBJ} -o${NAME}

${D_OBJ}:
	mkdir -p ${D_OBJ}
	mkdir -p ${D_OBJ}${D_BUILT_IN}

clean :
	rm -f ${OBJ}

fclean :
	rm -f ${NAME} ${OBJ}

re : fclean all

.PHONY : all clean fclean re
