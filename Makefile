# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: maboulho <maboulho@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/23 03:45:02 by eel-ghan          #+#    #+#              #
#    Updated: 2022/12/16 05:20:36 by maboulho         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = minishell

LEX_DIR = srcs/Parsing/Lexer/

PARS_DIR = srcs/Parsing/Parser/
EXEC_DIR = srcs/execution/
BUILT_INS = srcs/builtins/
SRCS =	minishell.c minishell1.c minishell2.c minishell3.c ${LEX_DIR}lexer.c ${LEX_DIR}token.c ${LEX_DIR}lexer_utils00.c\
		${LEX_DIR}lexer_utils01.c ${LEX_DIR}redirection_utils.c ${LEX_DIR}env_utils.c\
		${LEX_DIR}dollar_utils00.c ${LEX_DIR}lexer_utils02.c ${LEX_DIR}get_value_utils.c\
		${LEX_DIR}dollar_utils.c ${LEX_DIR}skip_quote_utils.c ${LEX_DIR}skip_quote_utils01.c\
		${PARS_DIR}parser.c ${PARS_DIR}struct_cmd.c ${PARS_DIR}linked_list_utils.c\
		${PARS_DIR}parser_utils00.c ${PARS_DIR}parser_utils01.c ${PARS_DIR}parser_utils02.c\
		${EXEC_DIR}env.c ${EXEC_DIR}execution_utils.c ${EXEC_DIR}main.c ${EXEC_DIR}check_files_type.c\
		${BUILT_INS}echo.c ${BUILT_INS}exit.c ${BUILT_INS}export.c ${BUILT_INS}export2.c ${BUILT_INS}cd.c ${BUILT_INS}pwd.c\
		${EXEC_DIR}pipe.c ${BUILT_INS}unset.c ${EXEC_DIR}execution_utils2.c ${EXEC_DIR}execution_utils3.c\
		
		

OBJS = ${SRCS:.c=.o}

CNTRL = @stty -echoctl

CC = @gcc

CFLAGS = -Wall -Wextra -Werror

RM = @rm -f

libft = srcs/Libft/libft.a

INCLUDE = -lreadline -L /Users/maboulho/homebrew/opt/readline/lib -I /Users/maboulho/homebrew/opt/readline/include

${NAME} : ${SRCS}
	stty -echoctl
	@make -C srcs/Libft
	
# ${CC}  ${CFLAGS} ${SRCS} ${libft}  -o ${NAME} 
	${CC}  ${CFLAGS} ${SRCS} ${libft} ${INCLUDE} -lreadline -o ${NAME} 
	@tput setaf 2; echo "MINISHELL IS READY"

all : ${NAME}
clean :
	${RM} ${OBJS}
	@make clean -C srcs/Libft
	@tput setaf 1; echo "OBJECTS REMOVED"

fclean : clean
	${RM} ${NAME}
	${RM} ${libft}
	@tput setaf 1; echo "MINISHELL REMOVED"

re : fclean all

.phony: all clean fclean re
