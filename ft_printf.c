/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonsok <hyeonsok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 23:14:15 by hyeonsok          #+#    #+#             */
/*   Updated: 2021/04/07 23:22:56 by hyeonsok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdarg.h>
#include <limits.h>
#include <stdlib.h>

#define CONV "cspdiuxX%"

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
	int	error;

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
	if (args->has_precision == 1)
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
		if (ft_istype(*idx, args))
		{
			idx++;
			break;
		}
		if (args->has_flags == 0)
			idx += readflags(idx, args);
		else if (args->has_width == 0)
			idx += readwidth(idx, args);
		else if (args->has_precision == 0)
			idx += readprecision(idx, args);
		else
			idx++;
	}
	return (idx - str);
}
int	ft_put_c(va_list *ap, t_args *args)
{
	int c;

	c = va_arg(*ap, int);
	return (ft_putchar(c));
}

// int	ft_put_s(va_list *ap, t_args *args)
// {
// 	size_t	len;

// 	len = ft_putstr(*ap);

// 	*ap += len + 1;
// 	return(len);
// }
// int	ft_put_p(va_list ap, t_args *args);
// int	ft_put_di(va_list ap, t_args *args);
// int	ft_put_u(va_list ap, t_args *args);
// int	ft_put_x(va_list ap, t_args *args);
// int	ft_put_X(va_list ap, t_args *args);

int	ft_put_percent(va_list *ap, t_args *args)
{
	return (ft_putchar('%'));
}

int	ft_put_conv(va_list *ap, t_args *args)
{
	if (args->type == 'c')
		return (ft_put_c(ap, args));
	if (args->type == 's')
		return (ft_put_s(ap, args));
	// if (args->type == 'p')
	// 	return (ft_put_p(ap, args));
	// if (args->type == 'd' || args->type == 'i')
	// 	return (ft_put_di(ap, args));
	// if (args->type == 'u')
	// 	return (ft_put_u(ap, args));
	// if (args->type == 'x')
	// 	return (ft_put_x(ap, args));
	// if (args->type == 'X')
	// 	return (ft_put_X(ap, args));
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
		itr = "(null)";
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

#ifdef TEST
# define F(...) \
	ft_printf(__VA_ARGS__)
#else
# include <stdio.h>
# define F(...) \
	printf(__VA_ARGS__)
#endif

int	main(void)
{
	printf("basic format test\n");
	F("%c\n");
	F("%s\n");
	F("%p\n");
	F("%d\n");
	F("%i\n");
	F("%u\n");
	F("%x\n");
	F("%X\n");
	F("%%\n");
	return (0);
}