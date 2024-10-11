# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zamgar <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/07 14:29:32 by zamgar            #+#    #+#              #
#    Updated: 2024/10/07 14:29:34 by zamgar           ###   ########.fr        #
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

OBJSSERVER := $(SRCSERVER:%.c=%.o)
OBJSCLIENT := $(SRCCLIENT:%.c=%.o)
OBJSSERVER_BONUS := $(SRCSERVER_BONUS:%.c=%.o)
OBJSCLIENT_BONUS := $(SRCCLIENT_BONUS:%.c=%.o)

CC = gcc
FLAGS = -Wall -Wextra -Werror -I ./includes

.c.o:
	$(CC) $(FLAGS) -c $< -o $@

all: $(NAMESERVER) $(NAMECLIENT)

$(LIBFT_LIB):
	make -sC $(LIBFT_PATH)

bonus : $(NAMESERVER_BONUS) $(NAMECLIENT_BONUS)

$(NAMESERVER) : $(LIBFT_LIB) $(OBJSSERVER)
	$(CC) $(FLAGS) $(OBJSSERVER) $(LIBFT_LIB) -o $(NAMESERVER)

$(NAMECLIENT) : $(LIBFT_LIB) $(OBJSCLIENT)
	$(CC) $(FLAGS) $(OBJSCLIENT) $(LIBFT_LIB) -o $(NAMECLIENT)

$(NAMESERVER_BONUS) : $(LIBFT_LIB) $(OBJSSERVER_BONUS)
	$(CC) $(FLAGS) $(OBJSSERVER_BONUS) $(LIBFT_LIB) -o $(NAMESERVER_BONUS)

$(NAMECLIENT_BONUS) : $(LIBFT_LIB) $(OBJSCLIENT_BONUS)
	$(CC) $(FLAGS) $(OBJSCLIENT_BONUS) $(LIBFT_LIB) -o $(NAMECLIENT_BONUS)

clean:
	make clean -sC $(LIBFT_PATH)
	rm -rf $(OBJSSERVER) $(OBJSCLIENT) $(OBJSSERVER_BONUS) $(OBJSCLIENT_BONUS)

fclean: clean
	make fclean -sC $(LIBFT_PATH)
	rm -rf $(NAMESERVER) $(NAMECLIENT) $(NAMESERVER_BONUS) $(NAMECLIENT_BONUS)

re: fclean all

rebonus: fclean bonus

.PHONY: all bonus clean fclean re rebonus
