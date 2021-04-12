/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_conv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonsok <hyeonsok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 16:11:51 by hyeonsok          #+#    #+#             */
/*   Updated: 2021/04/12 20:57:27 by hyeonsok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int	ft_put_u(va_list *ap, t_args *args)
{
	char	*digits;
	int		len;

	digits = ft_utoa_base(va_arg(*ap, int), DEC);
	len = ft_strlen(digits);
	args->width -= (args->precision + len);
	args->precision -= len;
	if (args->flags == '\0')
		args->width -= ft_put_padding(args->width, ' ');
	if (args->flags == '0')
		args->width -= ft_put_padding(args->width, '0');
	ft_put_padding(args->precision, '0');
	ft_putstr(digits);
	ft_put_padding(args->width, ' ');
	return (ft_putstr(digits));
}

int	ft_put_x(va_list *ap, t_args *args)
{
	char	*digits;
	int		res;

	digits = ft_utoa_base(va_arg(*ap, int), HEX);
	if (args->has_precision == 1 && digits[0] == '0')
	{
		free(digits);
		digits = "";
	}
	res = 0;
	if (args->precision < (int)ft_strlen(digits))
	args->precision = (int)ft_strlen(digits);
	if (args->width < args->precision)
		args->width = args->precision;
	if (args->flags == '0')
		res += ft_put_padding(args->width - args->precision, '0');
	if (args->flags == '\0')
		res += ft_put_padding(args->width - args->precision, ' ');
	res += ft_put_padding(args->precision - ft_strlen(digits), ' ');
	res += ft_putstr(digits);
	res += ft_put_padding(args->width - res, ' ');
	return (res);
}

int	ft_put_cx(va_list *ap, t_args *args)
{
	char	*digits;
	int		res;

	digits = ft_utoa_base(va_arg(*ap, int), CHEX);
	if (args->has_precision == 1 && digits[0] == '0')
		digits = "";
	res = 0;
	if (args->precision < (int)ft_strlen(digits))
	args->precision = (int)ft_strlen(digits);
	if (args->width < args->precision)
		args->width = args->precision;
	if (args->flags == '0')
		res += ft_put_padding(args->width - args->precision, '0');
	if (args->flags == '\0')
		res += ft_put_padding(args->width - args->precision, ' ');
	args->precision -= ft_put_padding(args->precision - ft_strlen(digits), '0');
	res += ft_putstr(digits);
	res += ft_put_padding(args->width - res, ' ');
	return (res);
}

int	ft_put_padding(int num, int c)
{
	int res;

	res = 0;
	while (num > 0)
	{
		ft_putchar((char)c);
		num--;
		res++;
	}
	return (res);
}

int	ft_put_conv(va_list *ap, t_args *args)
{
	if (args->w_asterisk)
		args->width = va_arg(*ap, int);
	if (args->p_asterisk)
		args->precision = va_arg(*ap, int);
	//negavtive width
	if (args->precision < 0)
	{
		args->has_precision = -1;
		args->precision = 0;
	}
	if (args->width < 0)
	{
		args->width *= -1;
		args->flags = '-';
	}
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
