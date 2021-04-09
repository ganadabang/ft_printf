/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putargs_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonsok <hyeonsok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 16:12:16 by hyeonsok          #+#    #+#             */
/*   Updated: 2021/04/09 17:15:32 by hyeonsok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int	ft_put_c(va_list *ap, t_args *args)
{
	int	c;
	int	len;

	c = va_arg(*ap, int);
	len = 1;
	args->precision = 0;
	args->width -= (args->precision + len);
	args->precision -= len;
	if (args->flags == 0)
		args->width -= ft_put_padding(args->width, ' ');
	if (args->flags == '0')
		args->width -= ft_put_padding(args->width, '0');
	ft_put_padding(args->precision, '0');
	ft_putchar(c);
	ft_put_padding(args->width, ' ');
	return (len);
}

int	ft_put_s(va_list *ap, t_args *args)
{
	char	*string;
	size_t	len;

	string = va_arg(*ap, char *);
	if (!string)
		string = "(null)";
	len = ft_strlen(string);
	args->precision = 0;
	args->width -= (args->precision + len);
	args->precision -= len;
	if (args->flags == 0)
		args->width -= ft_put_padding(args->width, ' ');
	if (args->flags == '0')
		args->width -= ft_put_padding(args->width, '0');
	ft_put_padding(args->precision, '0');
	ft_putstr(string);
	ft_put_padding(args->width, ' ');
	return (len);
}

int	ft_put_p(va_list *ap, t_args *args)
{
	int		len;
	size_t	addr;
	char	*digits;

	addr = (size_t)va_arg(*ap, void *);
	digits = ft_utoa_base(addr, HEX);
	len = 2 + ft_strlen(digits);
	args->width -= (args->precision + len);
	args->precision -= len;
	if (args->flags == 0)
		args->width -= ft_put_padding(args->width, ' ');
	ft_putstr("0x");
	if (args->flags == '0')
		args->width -= ft_put_padding(args->width, '0');
	ft_put_padding(args->precision, '0');
	ft_putstr(digits);
	ft_put_padding(args->width, ' ');
	return (len);
}

int	ft_put_di(va_list *ap, t_args *args)
{
	char	*digits;
	int		len;

	digits = ft_itoa(va_arg(*ap, int));
	len = ft_strlen(digits);
	args->width -= (args->precision + len);
	args->precision -= len;
	if (args->flags == 0)
		args->width -= ft_put_padding(args->width, ' ');
	if (args->flags == '0')
		args->width -= ft_put_padding(args->width, '0');
	ft_put_padding(args->precision, '0');
	ft_putstr(digits);
	ft_put_padding(args->width, ' ');
	return (len);
}

int	ft_put_percent(va_list *ap, t_args *args)
{
	int	len;

	len = 1;
	args->precision = 0;
	args->width -= (args->precision + len);
	args->precision -= len;
	if (args->flags == 0)
		args->width -= ft_put_padding(args->width, ' ');
	if (args->flags == '0')
		args->width -= ft_put_padding(args->width, '0');
	ft_put_padding(args->precision, '0');
	ft_putchar('%');
	ft_put_padding(args->width, ' ');
	return (len);
}
