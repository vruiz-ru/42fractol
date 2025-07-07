# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vruiz-ru <vruiz-ru@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/22 19:29:09 by vruiz-ru          #+#    #+#              #
#    Updated: 2024/12/21 14:09:56 by vruiz-ru         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= libftprintf.a
SRCS	= ft_putchar.c \
		ft_putpointer.c \
		ft_strlen.c \
		ft_printf.c \
		ft_putnbr_base.c \
		ft_putstr.c \

OBJS	= $(SRCS:.c=.o)
RM	= rm -f
LIBC	= ar -rcs
FLAGS	= -Wall -Wextra -Werror -fPIC

.c.o :
	$(CC) $(FLAGS) -c $< -o $@ -I.

$(NAME): $(OBJS)
	$(LIBC) $(NAME) $(OBJS) 

all: $(NAME)

fclean: clean
	$(RM) $(NAME)

clean:
	$(RM) $(OBJS)

re: fclean all

.PHONY: all clean fclean re .c.o
