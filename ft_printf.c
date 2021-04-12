/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonsok <hyeonsok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 23:14:15 by hyeonsok          #+#    #+#             */
/*   Updated: 2021/04/11 18:54:40 by hyeonsok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"
#include <stdio.h>

int	ft_printf(const char *str, ...)
{
	char	*itr;
	int		res;
	va_list	ap;
	t_args	*args;

	itr = (char *)str;
	if (!itr)
		return (0);
	args = (t_args *)malloc(sizeof(t_args));
	va_start(ap, str);
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
