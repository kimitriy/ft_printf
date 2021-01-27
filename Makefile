# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rburton <rburton@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/09/28 11:32:38 by rburton           #+#    #+#              #
#    Updated: 2020/12/20 14:24:10 by rburton          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = ft_printf.c ft_printf_utils0.c ft_printf_utils1.c ft_printf_prsr.c ft_printf_hndlr0.c ft_printf_hndlr1.c ft_printf_frmt0.c ft_printf_frmt1.c

OBJS	= ${SRC:.c=.o}

NAME	= libftprintf.a

GCC		= gcc

CFLAGS	= -g -Wall -Wextra -Werror

RM		= rm -f

ARRC	= ar rc

FT_H	= ft_printf.h

LIB		= libftprintf.a

all:	${NAME}

bonus:	all

.c.o:
		${GCC} ${CFLAGS} -c $< -o ${<:.c=.o}

${NAME}:${OBJS}
		${ARRC} ${LIB} ${OBJS}
		${ARRC} ${LIB} ${FT_H}

gcc:
		${GCC} ${CFLAGS} ft_printf_main.c libftprintf.a

clean:
		${RM} ${OBJS}

fclean:	clean
		${RM} ${NAME}
		${RM} ${LIB}

re:		fclean all