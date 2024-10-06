# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zamgar <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/06 19:25:03 by zamgar            #+#    #+#              #
#    Updated: 2024/10/06 19:25:04 by zamgar           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAMESERVER = serveur
NAMECLIENT = client

NAMESERVER_BONUS = serveur_bonus
NAMECLIENT_BONUS = client_bonus

LIBFT_PATH = ./libft/
LIBFT_NAME = libft.a
LIBFT_LIB = $(addprefix $(LIBFT_PATH), $(LIBFT_NAME))

SRCSERVER = serveur.c
SRCCLIENT = client.c
SRCSERVER_BONUS = serveur_bonus.c
SRCCLIENT_BONUS = client_bonus.c
PRINTF_SRC = ft_printf/ft_printf.c ft_printf/ft_hex.c ft_printf/ft_ptr.c ft_printf/ft_putcharstr.c ft_printf/ft_itoa.c ft_printf/ft_unsigned_itoa.c ft_printf/ft_strlen.c

OBJSSERVER := $(SRCSERVER:%.c=%.o)
OBJSCLIENT := $(SRCCLIENT:%.c=%.o)
OBJSSERVER_BONUS := $(SRCSERVER_BONUS:%.c=%.o)
OBJSCLIENT_BONUS := $(SRCCLIENT_BONUS:%.c=%.o)
PRINTF_OBJS := $(PRINTF_SRC:%.c=%.o)

CC = gcc
FLAGS = -Wall -Wextra -Werror -I ./includes

.c.o:
	$(CC) $(FLAGS) -c $< -o $@

all: $(NAMESERVER) $(NAMECLIENT)

$(LIBFT_LIB):
	make -sC $(LIBFT_PATH)

bonus : $(NAMESERVER_BONUS) $(NAMECLIENT_BONUS)

$(NAMESERVER) : $(LIBFT_LIB) $(OBJSSERVER) $(PRINTF_OBJS)
	$(CC) $(FLAGS) $(OBJSSERVER) $(LIBFT_LIB) $(PRINTF_OBJS) -o $(NAMESERVER)

$(NAMECLIENT) : $(LIBFT_LIB) $(OBJSCLIENT) $(PRINTF_OBJS)
	$(CC) $(FLAGS) $(OBJSCLIENT) $(LIBFT_LIB) $(PRINTF_OBJS) -o $(NAMECLIENT)

$(NAMESERVER_BONUS) : $(LIBFT_LIB) $(OBJSSERVER_BONUS) $(PRINTF_OBJS)
	$(CC) $(FLAGS) $(OBJSSERVER_BONUS) $(LIBFT_LIB) $(PRINTF_OBJS) -o $(NAMESERVER_BONUS)

$(NAMECLIENT_BONUS) : $(LIBFT_LIB) $(OBJSCLIENT_BONUS) $(PRINTF_OBJS)
	$(CC) $(FLAGS) $(OBJSCLIENT_BONUS) $(LIBFT_LIB) $(PRINTF_OBJS) -o $(NAMECLIENT_BONUS)

clean:
	make clean -sC $(LIBFT_PATH)
	rm -rf $(OBJSSERVER) $(OBJSCLIENT) $(OBJSSERVER_BONUS) $(OBJSCLIENT_BONUS) $(PRINTF_OBJS)

fclean: clean
	make fclean -sC $(LIBFT_PATH)
	rm -rf $(NAMESERVER) $(NAMECLIENT) $(NAMESERVER_BONUS) $(NAMECLIENT_BONUS)

re: fclean all

.PHONY: all bonus clean fclean re
