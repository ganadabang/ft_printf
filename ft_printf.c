/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonsok <hyeonsok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 23:14:15 by hyeonsok          #+#    #+#             */
/*   Updated: 2021/04/09 17:42:02 by hyeonsok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

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