#ifndef MINITALK_H
# define MINITALK_H

# include <signal.h>
# include <stdlib.h>
# include <stdarg.h>
# include <unistd.h>
# include <stdio.h>

// MINITALK


// LIBFT
int					ft_atoi(const char *str);
int					ft_isspace(int c);

// FT_PRINTF
int					ft_printf(const char *str, ...);
int					get_next_arg(va_list *ap, char c);
int					ft_dec_into_hex(unsigned int n, int b);
void				ft_print_array(char *array, int i);
char				*ft_fill_hexarray(unsigned int n, char *string,
						char *array);
int					ft_get_size_hexarray(unsigned int n);
int					ft_itoa2(int n);
char				*ft_itoa(int n);
char				*ft_min(char *str);
int					ft_count(int n);
int					ft_unsigned_itoa2(unsigned int n);
char				*ft_unsigned_itoa(unsigned int n);
int					ft_unsigned_count(unsigned int n);
int					ft_putptr(unsigned long long adress);
char				*ft_fill_ptrarray(unsigned long long adress,
						char *string, char *array);
int					ft_get_size_ptrarray(unsigned long long adress);
int					ft_putstr(char *str);
int					ft_putchar(char c);
size_t				ft_strlen(const char *s);

#endif