# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tcassu <tcassu@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/11 01:58:24 by tcassu            #+#    #+#              #
#    Updated: 2025/03/27 15:28:57 by tcassu           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC			= server.c client.c utils.c

SRCS 		= ${SRC}

OBJS		= ${SRCS:.c=.o}

LIBFLAGS= -Llibft -lft

INCLUDES	= ./

NAME		= libminitalk.a

AR			= ar rc

RM			= rm -f

RANLIB		= ranlib

GCC			= gcc

CFLAGS		= -Wall -Werror -Wextra

all:		${NAME}

.c.o:
			${GCC} ${CFLAGS} -c -I ${INCLUDES} $< -o ${<:.c=.o}

${NAME}:	${OBJS}
			${AR} ${NAME} ${OBJS}
			${RANLIB} ${NAME}
			cd libft && $(MAKE)
			$(GCC) -o server server.c utils.c $(NAME) $(LIBFLAGS)
			$(GCC) -o client client.c $(NAME) $(LIBFLAGS)

clean:
			rm -f ${OBJS}

fclean:		clean
			rm -f ${NAME}
			rm -f server
			rm -f client
			cd libft && $(MAKE) fclean

re:			fclean all
			
.PHONY:		all clean fclean re