/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_conv_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonsok <hyeonsok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 16:12:16 by hyeonsok          #+#    #+#             */
/*   Updated: 2021/04/12 21:46:27 by hyeonsok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int	ft_put_c(va_list *ap, t_args *args)
{
	int	c;
	int	res;

	c = va_arg(*ap, int);
	res = 0;
	if (args->flags == 0)
		res += ft_put_padding(args->width - 1, ' ');
	if (args->flags == '0')
		res += ft_put_padding(args->width - 1, '0');
	res += ft_putchar(c);
	res += ft_put_padding(args->width - res, ' ');
	return (res);
}

int	ft_put_s(va_list *ap, t_args *args)
{
	char	*string;
	int		res;

	string = va_arg(*ap, char *);
	res = 0;
	if (!string)
		string = "(null)";
	if (args->precision > (int)ft_strlen(string) || args->has_precision == -1)
		args->precision = (int)ft_strlen(string);
	if (args->flags == 0)
		res += ft_put_padding(args->width - args->precision, ' ');
	if (args->flags == '0')
		res += ft_put_padding(args->width - args->precision, '0');
	while (args->precision > 0 && *string != '\0')
	{
		res += ft_putchar(*string++);
		args->precision--;
	}
	res += ft_put_padding(args->width - res, ' ');
	return (res);
}

int	ft_put_p(va_list *ap, t_args *args)
{
	long long	addr;
	char		*digits;
	int			res;

	addr = (long long)va_arg(*ap, void *);
	digits = ft_lltoa_base(addr, HEX);
	if (args->has_precision == 1 && digits[0] == '0')
		digits = "";
	res = 0;
	if (args->precision < (int)ft_strlen(digits))
		args->precision = (int)ft_strlen(digits);
	if (args->width < args->precision + 2)
		args->width = args->precision + 2;
	if (args->flags == '0')
		res += ft_put_padding(args->width - args->precision - 2, '0');
	if (args->flags == '\0')
		res += ft_put_padding(args->width - args->precision - 2, ' ');
	res += ft_putstr("0x");
	args->precision -= ft_put_padding(args->precision - ft_strlen(digits), '0');
	res += ft_putstr(digits);
	res += ft_put_padding(args->width - res, ' ');
	return (res);
}

int	ft_put_di(va_list *ap, t_args *args)
{
	char	*digits;
	int		dsc;
	int		res;

	digits = ft_itoa(va_arg(*ap, int));
	if (args->has_precision == 1 && digits[0] == '0')
		digits = "";
	if (digits[0] == '-')
		args->precision++;
	res = 0;
	if (args->precision < (int)ft_strlen(digits))
		args->precision = (int)ft_strlen(digits);
	if (args->width < args->precision)
		args->width = args->precision;
	dsc = (args->has_precision == 1) && (args->flags == '0');
	if (args->flags == '\0' || dsc)
		res += ft_put_padding(args->width - args->precision, ' ');
	if (digits[0] == '-')
		res += ft_putchar(*digits);
	if (args->flags == '0' && args->has_precision == -1)
		res += ft_put_padding(args->width - args->precision, '0');
	res += ft_put_padding(args->precision - ft_strlen(digits), '0');
	res += ft_putstr(digits + ft_isminus(*digits));
	res += ft_put_padding(args->width - res, ' ');
	return (res);
}

int	ft_put_percent(t_args *args)
{
	int	res;

	res = 0;
	if (args->flags == 0)
		res += ft_put_padding(args->width - 1, ' ');
	if (args->flags == '0')
		res += ft_put_padding(args->width - 1, '0');
	res += ft_putchar('%');
	if (args->flags == '-')
		res += ft_put_padding(args->width - res, ' ');
	return (res);
}
