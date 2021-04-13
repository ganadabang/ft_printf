/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftprintf.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonsok <hyeonsok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 15:39:50 by hyeonsok          #+#    #+#             */
/*   Updated: 2021/04/13 13:18:32 by hyeonsok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFTPRINTF_H
# define LIBFTPRINTF_H

# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <stdarg.h>

# define CONV "cspdiuxX%"
# define OCT "01234567"
# define DEC "0123456789"
# define HEX "0123456789abcdef"
# define CHEX "0123456789ABCDEF"

typedef struct	s_args
{
	int			has_flags;
	int			flags;
	int			has_width;
	int			width;
	int			precision;
	int			has_precision;
	int			type;
	int			w_asterisk;
	int			p_asterisk;
}				t_args;

int				ft_printf(const char *str, ...);
int				ft_put_conv(va_list *ap, t_args *args);
int				readargs(char *str, t_args *args);
/*
**		utils
*/
void			*ft_calloc(size_t count, size_t size);
size_t			ft_strlen(char *str);
char			*ft_utoa_base(int n, char *set);
char			*ft_lltoa_base(long long n, char *set);
char			*ft_itoa(int n);
int				ft_putchar(char c);
int				ft_putstr(char *str);
void			*ft_memset(void *b, int c, size_t len);
int				ft_atoi(const char *str);
int				ft_isdigit(int c);
int				ft_isspace(int c);
char			*ft_strchr(const char *s, int c);
/*
**		read_utils_1
*/
int				readflags(char *str, t_args *args);
int				readwidth(char *str, t_args *args);
int				readprecision(char *str, t_args *args);
int				readtype(char *str, t_args *args);
void			initialize_args(t_args *args);
/*
**		read_utils_2
*/
int				ft_isflag(int c);
int				ft_getdigits(char *str);
int				ft_isminus(int	c);
int				ft_isformat(int c);
/*
**		put_utils_2
*/
int				ft_put_c(va_list *ap, t_args *args);
int				ft_put_s(va_list *ap, t_args *args);
int				ft_put_p(va_list *ap, t_args *args);
int				ft_put_di(va_list *ap, t_args *args);
int				ft_put_percent(t_args *args);
/*
**		put_utils1
*/
int				ft_put_u(va_list *ap, t_args *args);
int				ft_put_x(va_list *ap, t_args *args);
int				ft_put_cx(va_list *ap, t_args *args);
int				ft_put_padding(int	num, int c);
void			control_args(va_list *ap, t_args *args);

#endif
