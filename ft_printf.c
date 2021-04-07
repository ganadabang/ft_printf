/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonsok <hyeonsok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 23:14:15 by hyeonsok          #+#    #+#             */
/*   Updated: 2021/04/07 22:07:01 by hyeonsok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdarg.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>

#define CONV "disuxX"

/*
** update libft
*/
int ft_putchar(char c)
{
	return (write(1, &c, 1));
}

int ft_putstr(char *str)
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

/*:
**  update header
**  %[parameter][flags][width][.precision][length]type
*/

void	*ft_memset(void *b, int c, size_t len)
{
	void *first_b;

	first_b = b;
	while (len--)
		*(unsigned char *)b++ = (unsigned char)c;
	return (first_b);
}

typedef struct	s_args
{
	int	has_flags;
	int	flags;
	int has_width;
	int width;
	int precision;
	int has_precision;
	int type;
	int error;

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
	return ( c == '0' || c == '-');
}

int	readflags(char *str, t_args *args)
{
	int	res;

	res = 0;
	while (ft_isflag(*str) || ft_isspace(*str))
	{
		if (*str == '-')
			args->flags = '-'; //45
		else if (*str == '0' && args->flags != '-')	//0과 -같이 사용될 수 없음
				args->flags = '0'; //48
		str++;
		res++;
	}
	if (args->flags > 0)
		args->has_flags = 1;
	else
		args->has_flags = -1;
	return (res);
}

int ft_istype(char c, t_args *args)	//1개 읽음
{
	char *type;

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
	char *idx;

	idx = str;
	if (*idx == '+' || *idx == '-')
		idx++;
	while (ft_isdigit(*idx))
		idx++;
	return (idx - str);
}


int	readwidth(char *str, t_args *args)
{
	int res;

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

int readprecision(char *str, t_args *args)
{
	int res;

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
	return(res);
}

int	readargs(char *str, t_args **args)
{
	char *	idx;
	t_args	*r_args;

	r_args = malloc(sizeof(t_args));
	idx = str;
	initialize_args(r_args);
	while (*idx != '\0' && !ft_istype(*idx, r_args))
	{
		if (r_args->has_flags == 0)
			idx += readflags(idx, r_args);
		else if (r_args->has_width == 0)
			idx += readwidth(idx, r_args);
		else if (r_args->has_precision == 0)
			idx += readprecision(idx, r_args);
		else
			idx++;
	}
	*args = r_args;
	return (idx - str);
}

int ft_printf(const char * format, ...)
{
	char	*itr;
	int		res;
	va_list	ap;
	t_args	*args;

	itr = (char *)format;
	if (!itr)
		return (-1);
	va_start(ap, format);
	{
		res = 0;
		while (*itr)
		{
			if (*itr == '%')
			{
				itr++;
				itr += readargs(itr, &args);

				// res += ft_put_conv(ap, args);
				continue;
			}
			// res += ft_putchar(*itr);
			itr++;
		}
		printf("args->type %c\n", (*args).type);

		printf("args->flags %c\n", (*args).flags);
		printf("args->has_flags %i\n", (*args).has_flags);

		printf("args->width %i\n", (*args).width);
		printf("args->has_width %i\n", (*args).has_width);

		printf("args->precision %i\n", (*args).precision);
		printf("args->has_precision %i\n\n", (*args).has_precision);
	}
	free(args);
	va_end(ap);
	return (res);
}

// #ifdef TEST
# define F(...) \
	ft_printf(__VA_ARGS__)
// #else
// # include <stdio.h>
// # define F(...) \
// 	ft_printf(__VA_ARGS__)
// #endif


int	main(void)
{
	printf("test\n");
	F("%-011.7i");
	F("%-20s");
	F("%.5x");

	return (0);

}