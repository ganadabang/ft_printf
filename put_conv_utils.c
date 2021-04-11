/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_conv_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonsok <hyeonsok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 16:12:16 by hyeonsok          #+#    #+#             */
/*   Updated: 2021/04/11 21:42:21 by hyeonsok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"
#include "stdio.h"

int	ft_put_c(va_list *ap, t_args *args)
{
	int	c;
	int	len;

	c = va_arg(*ap, int);
	len = 1;
	args->precision = 0;
	if (args->width < 0)
	{
		args->width *= -1;
		args->flags = '-';
	}
	args->width -= (args->precision + len);
	args->precision -= len;
	if (args->width > 0)
		len += args->width;
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
	int		len;
	int		res;

	string = va_arg(*ap, char *);
	if (!string)
		string = "(null)";
	len = ft_strlen(string);
	if (args->has_precision == -1 || args->precision >= len || args->precision < 0)
		args->precision = ft_strlen(string);
	else
		len = args->precision;
	if (args->width < 0)
	{
		args->width *= -1;
		args->flags = '-';
	}
	if (args->width > len)
		len = args->width; //패딩 포함 문자길이
	res = len;
	if (args->flags == 0)
		len -= ft_put_padding(len - args->precision, ' ');
	if (args->flags == '0')
		len -= ft_put_padding(len - args->precision, '0');
	while (args->precision-- && *string != '\0')
	{
		ft_putchar(*string++);
		len--;
	}
	ft_put_padding(len, ' ');
	return (res);
}

int	ft_put_p(va_list *ap, t_args *args)
{
	int					len;
	unsigned long long	addr;
	char				*digits;
	int					res;

	addr = (unsigned long long)va_arg(*ap, void *);
	digits = ft_utoa_base(addr, HEX);
	if (args->has_precision == 1 && digits[0] == '0')
		digits = "";
	if (args->width < 0)
	{
		args->width *= -1;
		args->flags = '-';
	}
	res = ft_strlen(digits) + 2;
	if (args->precision + 2 > res)
		res = args->precision + 2;
	len = res;
	if (args->width > res)
		len = args->width;
	if (args->flags == '0')
		args->width -= ft_put_padding(len - res, '0');
	if (args->flags == '\0')
		args->width -= ft_put_padding(len - res, ' ');
	ft_putstr("0x");
	args->precision -= ft_put_padding(args->precision - ft_strlen(digits), '0');
	ft_putstr(digits);
	if (args->flags == '-')
		ft_put_padding(len - res, ' ');
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

int	ft_put_percent(t_args *args)
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
