/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_utils_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonsok <hyeonsok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 16:12:16 by hyeonsok          #+#    #+#             */
/*   Updated: 2021/04/16 16:40:38 by hyeonsok         ###   ########.fr       */
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
	unsigned long long	addr;
	char				*digits;
	int					res;

	res = 0;
	addr = (unsigned long long)va_arg(*ap, void *);
	digits = ft_ulltoa_base(addr, HEX);
	if (!digits)
		return (res);
	if (args->has_precision == 1 && digits[0] == '0')
		digits = free_and_dup_nul(digits);
	args->precision = cmp(args->precision, (int)ft_strlen(digits));
	args->width = cmp(args->width, args->precision + 2);
	if (args->flags == '\0')
		res += ft_put_padding(args->width - args->precision - 2, ' ');
	res += ft_putstr("0x");
	if (args->flags == '0')
		res += ft_put_padding(args->width - args->precison - 2, '0');
	args->precision -= ft_put_padding(args->precision - ft_strlen(digits), '0');
	res += ft_putstr(digits);
	res += ft_put_padding(args->width - res, ' ');
	free(digits);
	return (res);
}

int	ft_put_di(va_list *ap, t_args *args)
{
	char	*digits;
	int		dsc;
	int		res;

	res = 0;
	if (!(digits = ft_itoa(va_arg(*ap, int))))
		return (res);
	if (args->has_precision == 1 && digits[0] == '0')
		digits = free_and_dup_nul(digits);
	if (digits[0] == '-')
		args->precision++;
	args->precision = cmp(args->precision, (int)ft_strlen(digits));
	args->width = cmp(args->width, args->precision);
	dsc = ((args->has_precision == 1) && (args->flags == '0'));
	if (args->flags == '\0' || dsc)
		res += ft_put_padding(args->width - args->precision, ' ');
	if (digits[0] == '-')
		res += ft_putchar(*digits);
	if (args->flags == '0' && args->has_precision == -1)
		res += ft_put_padding(args->width - args->precision, '0');
	res += ft_put_padding(args->precision - ft_strlen(digits), '0');
	res += ft_putstr(digits + ft_isminus(*digits));
	res += ft_put_padding(args->width - res, ' ');
	free(digits);
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
