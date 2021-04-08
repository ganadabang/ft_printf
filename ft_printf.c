/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonsok <hyeonsok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 23:14:15 by hyeonsok          #+#    #+#             */
/*   Updated: 2021/04/08 20:05:12 by hyeonsok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdarg.h>
#include <limits.h>
#include <stdlib.h>

#define CONV "cspdiuxX%"
#define OCT "01234567"
#define DEC "0123456789"
#define HEX "0123456789abcdef"
#define CHEX "0123456789ABCDEF"

void	*ft_calloc(size_t count, size_t size)
{
	void				*ptr;
	void				*first_ptr;
	unsigned long long	len;

	len = size * count;
	if (!(ptr = (void *)malloc(len)))
		return (NULL);
	first_ptr = ptr;
	while (len--)
		*(char *)ptr++ = '\0';
	return (first_ptr);
}

static unsigned	int		conv_to_abs(int n)
{
	unsigned int	n_abs;

	if (n < 0)
		n_abs = n * -1;
	else
		n_abs = n;
	return (n_abs);
}

static unsigned	int		get_len(unsigned int n)
{
	if (n >= 0 && n < 10)
		return (1);
	return (1 + get_len(n / 10));
}

size_t	ft_strlen(char *str)
{
	char *ptr;

	ptr = str;
	while (*str)
		str++;
	return (str - ptr);
}

static char				*conv_abs_to_str(char *str, unsigned int abs, char *set)
{
	size_t	len;

	if (str == NULL)
		return (NULL);
	if (abs == 0)
		return (str);
	else
	{
		*(--str) = set[abs % ft_strlen(set)];
	}
	return (conv_abs_to_str(str, abs / ft_strlen(set), set));
}

char					*ft_itoa(int n)
{
	unsigned int	abs;
	unsigned int	len;
	char			is_minus;
	char			*str;

	abs = conv_to_abs(n);
	len = get_len(abs);
	is_minus = 0;
	if (n < 0)
		is_minus = 1;
	str = ft_calloc(is_minus + len + 1, sizeof(char));
	if (!str)
		return (NULL);
	if (abs == 0)
	{
		*str = '0';
		return (str);
	}
	if (is_minus == 1)
		*str = '-';
	return (conv_abs_to_str(str + is_minus + len, abs, DEC) - is_minus);
}

char					*ft_utoa_base(int n, char *set)
{
	unsigned int	abs;
	unsigned int	len;
	char			*str;

	abs = (unsigned int)n;
	len = get_len(abs);
	str = ft_calloc(len + 1, sizeof(char));
	if (!str)
		return (NULL);
	if (abs == 0)
	{
		*str = '0';
		return (str);
	}
	return (conv_abs_to_str(str + len, abs, set));
}

int	ft_putchar(char c)
{
	return (write(1, &c, 1));
}

int	ft_putstr(char *str)
{
	int	res;

	if (!str)
		return (-1);
	res = 0;
	while (*str)
	{
		res += ft_putchar(*str);
		str++;
	}
	return (res);
}

void	*ft_memset(void *b, int c, size_t len)
{
	void	*ptr;

	ptr = b;
	while (len--)
		*(unsigned char *)b++ = (unsigned char)c;
	return (ptr);
}

typedef struct s_args
{
	int	has_flags;
	int	flags;
	int	has_width;
	int	width;
	int	precision;
	int	has_precision;
	int	type;
	int	w_asterisk;
	int	p_asterisk;

}				t_args;

int	ft_isspace(int c)
{
	return ((c >= '\t' && c <= '\r') || c == ' ');
}

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

int	ft_atoi(const char *str)
{
	size_t	val;
	int		sign;

	val = 0;
	sign = 1;
	while (ft_isspace(*str))
		str++;
	if (*str == '+' || *str == '-')
		sign = 44 - *str++;
	while (ft_isdigit(*str))
	{
		val = (10 * val) + *str - '0';
		str++;
	}
	if ((val >= LLONG_MAX) && sign == 1)
		return (-1);
	if ((val > LLONG_MAX) && sign == -1)
		return (0);
	return (sign * val);
}

char	*ft_strchr(const char *s, int c)
{
	while (s != NULL && *s != '\0')
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if (*s == c)
		return ((char *)s);
	return (NULL);
}

void	initialize_args(t_args *args)
{
	ft_memset(args, 0, sizeof(t_args));
}

int	ft_isflag(int c)
{
	return ((c == '0') || (c == '-'));
}

int	readflags(char *str, t_args *args)
{
	int	res;

	res = 0;
	while (ft_isflag(*str) || ft_isspace(*str))
	{
		if (*str == '-')
			args->flags = '-';
		else if (*str == '0' && args->flags != '-')
			args->flags = '0';
		str++;
		res++;
	}
	if (*str == '*')
	{
		args->w_asterisk = 1;
		args->has_width = 1;
		res++;
	}
	if (args->flags > 0)
		args->has_flags = 1;
	else
		args->has_flags = -1;
	return (res);
}

int	ft_istype(char c, t_args *args)
{
	char	*type;

	type = ft_strchr(CONV, c);
	if (type != NULL)
	{
		args->type = *type;
		return (1);
	}
	return (0);
}

int	ft_getdigits(char *str)
{
	char	*idx;

	idx = str;
	if (*idx == '+' || *idx == '-')
		idx++;
	while (ft_isdigit(*idx))
		idx++;
	return (idx - str);
}

int	readwidth(char *str, t_args *args)
{
	int	res;

	res = 0;
	args->width = ft_atoi(str);
	if (args->width > 0)
	{
		args->has_width = 1;
		res += ft_getdigits(str);
		str += res;
	}
	else
		args->has_width = -1;
	return (res);
}

int	readprecision(char *str, t_args *args)
{
	int	res;

	res = 0;
	if (*str == '.')
	{
		args->has_precision = 1;
		str++;
	}
	if (*str == '*' && args->has_precision)
	{
		args->p_asterisk = 1;
		res++;
	}
	else if (args->has_precision == 1)
	{
		args->precision = ft_atoi(str);
		res += ft_getdigits(str);
		str += res;
	}
	else
		args->has_precision = -1;
	return (res);
}

int	readargs(char *str, t_args *args)
{
	char	*idx;

	idx = str;
	initialize_args(args);
	while (*idx != '\0')
	{
		if (args->has_flags == 0)
			idx += readflags(idx, args);
		else if (args->has_width == 0)
			idx += readwidth(idx, args);
		else if (args->has_precision == 0)
			idx += readprecision(idx, args);
		else if (ft_istype(*idx++, args))
			break;
	}
	return (idx - str);
}

int	ft_put_c(va_list *ap, t_args *args)
{
	int c;

	c = va_arg(*ap, int);
	return (ft_putchar(c));
}

int	ft_put_s(va_list *ap, t_args *args)
{
	char	*string;
	size_t	len;

	string = va_arg(*ap, char *);
	if (!string)
		string = "(null)";
	return(ft_putstr(string));
}

int	ft_put_p(va_list *ap, t_args *args)
{
	int		res;
	size_t	addr;
	char	*digits;

	addr = (size_t)va_arg(*ap, void *);
	digits = ft_utoa_base(addr, HEX);
	res += ft_putstr("0x");
	res += ft_putstr(digits);
	return (res);
}

int	ft_put_di(va_list *ap, t_args *args)
{
	char	*digits;

	digits = ft_itoa(va_arg(*ap, int));
	return (ft_putstr(digits));
}

int	ft_put_u(va_list *ap, t_args *args)
{
	char	*digits;

	digits = ft_utoa_base(va_arg(*ap, int), DEC);
	return (ft_putstr(digits));
}

int	ft_put_x(va_list *ap, t_args *args)
{
	char	*digits;

	digits = ft_utoa_base(va_arg(*ap, int), HEX);
	return (ft_putstr(digits));
}

int	ft_put_X(va_list *ap, t_args *args)
{
	char	*digits;

	digits = ft_utoa_base(va_arg(*ap, int), CHEX);
	return (ft_putstr(digits));
}

int	ft_put_percent(va_list *ap, t_args *args)
{
	return (ft_putchar('%'));
}

int	ft_put_conv(va_list *ap, t_args *args)
{
	if (args->w_asterisk)
		args->width = va_arg(*ap, int);
	if (args->p_asterisk)
		args->precision = va_arg(*ap, int);
	if (args->type == 'c')
		return (ft_put_c(ap, args));
	if (args->type == 's')
		return (ft_put_s(ap, args));
	if (args->type == 'p')
		return (ft_put_p(ap, args));
	if (args->type == 'd' || args->type == 'i')
		return (ft_put_di(ap, args));
	if (args->type == 'u')
		return (ft_put_u(ap, args));
	if (args->type == 'x')
		return (ft_put_x(ap, args));
	if (args->type == 'X')
		return (ft_put_X(ap, args));
	if (args->type == '%')
		return (ft_put_percent(ap, args));
	return (0);
}

int	ft_printf(const char *format, ...)
{
	char	*itr;
	int		res;
	va_list	ap;
	t_args	*args;

	itr = (char *)format;
	if (!itr)
		return (0);
	args = (t_args *)malloc(sizeof(t_args));
	va_start(ap, format);
	res = 0;
	while (*itr)
	{
		if (*itr == '%')
		{
			itr++;
			itr += readargs(itr, args);
			res += ft_put_conv(&ap, args);
			continue ;
		}
		res += ft_putchar(*itr++);
	}
	va_end(ap);
	free(args);
	return (res);
}
// #define TEST
// #ifndef TEST
# define F(...) \
	ft_printf(__VA_ARGS__)
// #else
// # include <stdio.h>
// # define F(...) \
// 	printf(__VA_ARGS__)
// #endif

int	main(void)
{
	int num;

	printf("==== basic format test ===\n");
	F("%*.*c\n" ,9, 9, 'B');
	F("%s\n", NULL);
	F("%p\n" , &num);
	F("%d\n", 2147483647);
	F("%i\n", -2147483648);
	F("%x\n", 2147483647);
	F("%X\n", -2147483648);
	F("%%\n");

	printf("====  flag + width test ===\n");
	F("%010.*c\n" ,9, 9, 'B');
	F("%010s\n", NULL);
	F("%010p\n" , &num);
	F("%010d\n", 2147483647);
	F("%010i\n", -2147483648);
	F("%010x\n", 2147483647);
	F("%010X\n", -2147483648);
	F("%010%\n");

	F("%-10.*c\n" ,9, 9, 'B');
	F("%-10s\n", NULL);
	F("%-10p\n" , &num);
	F("%-10d\n", 2147483647);
	F("%-10i\n", -2147483648);
	F("%-10x\n", 2147483647);
	F("%-10X\n", -2147483648);
	F("%-10%\n");

	F("%-010.*c\n" ,9, 9, 'B');
	F("%-010s\n", NULL);
	F("%-010p\n" , &num);
	F("%-010d\n", 2147483647);
	F("%-010i\n", -2147483648);
	F("%-010x\n", 2147483647);
	F("%-010X\n", -2147483648);
	F("%-010%\n");

	printf("====  flag + precision test ===\n");

	F("%0.10.*c\n" ,9, 9, 'B');
	F("%0.10s\n", NULL);
	F("%0.10p\n" , &num);
	F("%0.10d\n", 2147483647);
	F("%0.10i\n", -2147483648);
	F("%0.10x\n", 2147483647);
	F("%0.10X\n", -2147483648);
	F("%0.10%\n");

	F("%-.10.*c\n" ,9, 9, 'B');
	F("%-.10s\n", NULL);
	F("%-.10p\n" , &num);
	F("%-.10d\n", 2147483647);
	F("%-.10i\n", -2147483648);
	F("%-.10x\n", 2147483647);
	F("%-.10X\n", -2147483648);
	F("%-.10%\n");

	F("%-0.10.*c\n" ,9, 9, 'B');
	F("%-0.10s\n", NULL);
	F("%-0.10p\n" , &num);
	F("%-0.10d\n", 2147483647);
	F("%-0.10i\n", -2147483648);
	F("%-0.10x\n", 2147483647);
	F("%-0.10X\n", -2147483648);
	F("%-0.10%\n");

	printf("====  flag + width + precision test ===\n");

	F("%05.10.*c\n" ,9, 9, 'B');
	F("%05.10s\n", NULL);
	F("%05.10p\n" , &num);
	F("%05.10d\n", 2147483647);
	F("%05.10i\n", -2147483648);
	F("%05.10x\n", 2147483647);
	F("%05.10X\n", -2147483648);
	F("%05.10%\n");

	F("%-5.10.*c\n" ,9, 9, 'B');
	F("%-5.10s\n", NULL);
	F("%-5.10p\n" , &num);
	F("%-5.10d\n", 2147483647);
	F("%-5.10i\n", -2147483648);
	F("%-5.10x\n", 2147483647);
	F("%-5.10X\n", -2147483648);
	F("%-5.10%\n");

	F("%-50.10.*c\n" ,9, 9, 'B');
	F("%-05.10s\n", NULL);
	F("%-05.10p\n" , &num);
	F("%-05.10d\n", 2147483647);
	F("%-05.10i\n", -2147483648);
	F("%-05.10x\n", 2147483647);
	F("%-05.10X\n", -2147483648);
	F("%-05.10%\n");

	F("%-50.10.*c\n" ,9, 9, 'B');
	F("%-20.10s\n", NULL);
	F("%-20.10p\n" , &num);
	F("%-20.10d\n", 2147483647);
	F("%-20.10i\n", -2147483648);
	F("%-20.10x\n", 2147483647);
	F("%-20.10X\n", -2147483648);
	F("%-20.10%\n");




	return (0);
}