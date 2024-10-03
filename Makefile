NAMESERVER = serveur
NAMECLIENT = client

SRCSERVER = serveur.c
SRCCLIENT = client.c
PRINTF_SRC = ft_printf/ft_printf.c ft_printf/ft_hex.c ft_printf/ft_ptr.c ft_printf/ft_putcharstr.c ft_printf/ft_itoa.c ft_printf/ft_unsigned_itoa.c ft_printf/ft_strlen.c
LIBFT_SRC = libft/ft_atoi.c libft/ft_isspace.c

OBJSSERVER := $(SRCSERVER:%.c=%.o)
OBJSCLIENT := $(SRCCLIENT:%.c=%.o)
PRINTF_OBJS := $(PRINTF_SRC:%.c=%.o)
LIBFT_OBJS := $(LIBFT_SRC:%.c=%.o)

CC = gcc
FLAGS = -Wall -Wextra -Werror

all: $(NAMESERVER) $(NAMECLIENT)

$(NAMESERVER) : $(OBJSSERVER) $(PRINTF_OBJS) $(LIBFT_OBJS)
	$(CC) $(FLAGS) $(OBJSSERVER) $(PRINTF_OBJS) $(LIBFT_OBJS) -o $(NAMESERVER)

$(NAMECLIENT) : $(OBJSCLIENT) $(PRINTF_OBJS)
	$(CC) $(FLAGS) $(OBJSCLIENT) $(PRINTF_OBJS) $(LIBFT_OBJS) -o $(NAMECLIENT)

clean:
	rm -rf $(OBJSSERVER) $(OBJSCLIENT) $(PRINTF_OBJS) $(LIBFT_OBJS)

fclean: clean
	rm -rf $(NAMESERVER) $(NAMECLIENT)

re: fclean all
