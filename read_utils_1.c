/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readargs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonsok <hyeonsok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 16:03:15 by hyeonsok          #+#    #+#             */
/*   Updated: 2021/04/10 01:47:45 by hyeonsok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int		readflags(char *str, t_args *args)
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

int		readwidth(char *str, t_args *args)
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

int		readprecision(char *str, t_args *args)
{
	int	res;

	res = 0;
	if (*str == '.')
	{
		args->has_precision = 1;
		res++;
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

int		readtype(char *str, t_args *args)
{
	char	*type;

	type = ft_strchr(CONV, *str);
	if (type != NULL)
	{
		args->type = *type;
		return (1);
	}
	return (0);
}

void	initialize_args(t_args *args)
{
	ft_memset(args, 0, sizeof(t_args));
}
