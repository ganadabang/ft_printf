/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readargs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonsok <hyeonsok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 16:03:15 by hyeonsok          #+#    #+#             */
/*   Updated: 2021/04/09 17:16:58 by hyeonsok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

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
			break ;
	}
	return (idx - str);
}
