/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonsok <hyeonsok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 23:14:15 by hyeonsok          #+#    #+#             */
/*   Updated: 2021/04/14 15:23:55 by hyeonsok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int	readargs(char *str, t_args *args)
{
	char	*idx;

	idx = str;
	idx++;
	initialize_args(args);
	while (*idx != '\0' && ft_isformat(*idx))
	{
		if (args->has_flags == 0)
			idx += readflags(idx, args);
		if (args->has_width == 0)
			idx += readwidth(idx, args);
		if (args->has_precision == 0)
			idx += readprecision(idx, args);
		if (readtype(idx, args))
		{
			idx++;
			break ;
		}
	}
	return (idx - str);
}

int	ft_put_conv(va_list *ap, t_args *args)
{
	validate_args(ap, args);
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
		return (ft_put_cx(ap, args));
	if (args->type == '%')
		return (ft_put_percent(args));
	return (0);
}

int	ft_printf(const char *str, ...)
{
	char	*itr;
	int		res;
	va_list	ap;
	t_args	args;

	itr = (char *)str;
	va_start(ap, str);
	{
		res = 0;
		while (*itr)
		{
			if (*itr == '%')
			{
				itr += readargs(itr, &args);
				res += ft_put_conv(&ap, &args);
				continue ;
			}
			res += ft_putchar(*itr++);
		}
	}
	va_end(ap);
	return (res);
}
