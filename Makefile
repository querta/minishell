# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmonte <mmonte@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/12 18:23:46 by spitt             #+#    #+#              #
#    Updated: 2021/04/07 20:30:39 by mmonte           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = gcc
HEADERS = minishell.h
CFLAG = -Wall -Werror -Wextra
SRC = main.c utils.c ft_exit.c ft_errors.c \
		./termcaps/ft_signal.c ./termcaps/ft_termcap_commands.c ./termcaps/ft_termcaps_env.c \
		./struct_commands/job_editor.c ./struct_commands/pipe_editor.c ./struct_commands/rdir_editor.c \
		./parser/parser.c ./parser/ft_write_string_prestruct.c ./parser/ft_string_rewriter.c ./parser/ft_parser_env.c \
		./parser/ft_len_string_prestruct.c ./parser/ft_from_env_write.c ./parser/ft_from_env_len.c \
		./lexer/ft_check_token.c ./lexer/ft_lexer_env.c ./lexer/lexer.c \
		./history/ft_history_env.c ./history/ft_create_history.c \
		./get_next_lines/get_next_line.c ./get_next_lines/get_next_line_classic.c \
		./executer/external_functions.c ./executer/redirects.c ./executer/executer.c ./executer/environment.c \
		./buildin/buildin_funcs.c ./buildin/unset.c ./buildin/export.c ./buildin/run_cd.c ./buildin/run_echo.c
	

HEADER = -I ./

TERMCAP = -ltermcap

LIBFT_DIR = ./libft/
LOBJ = ${LIBFT_DIR:.c=.o}
OBJ = ${SRC:.c=.o}
DL = ${SRC:.c=.d}

.PHONY: all, clean, fclean, re, libft

all: 	libft $(NAME)

%.o:%.c $(HEADERS)
	${CC} ${CFLAG} ${HEADER} -c $< -o $@

$(NAME):	$(OBJ) $(LOBJ)
		${CC} ${CFLAG} ${OBJ} ./libft/libft.a ${TERMCAP} -o ${NAME}

libft:
		make -C ${LIBFT_DIR}

clean:
	make fclean -C ${LIBFT_DIR}
	rm -f ${OBJ}
	rm -rf ${DL}

fclean:	clean
	rm -f ${NAME}

re:	fclean all
