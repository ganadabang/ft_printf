/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_utils_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonsok <hyeonsok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 16:11:51 by hyeonsok          #+#    #+#             */
/*   Updated: 2021/04/14 15:22:47 by hyeonsok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int		ft_put_u(va_list *ap, t_args *args)
{
	char	*digits;
	int		dsc;
	int		res;

	res = 0;
	digits = ft_uitoa_base(va_arg(*ap, int), DEC);
	if (!digits)
		return (res);
	if (args->has_precision == 1 && digits[0] == '0')
		digits = free_and_dup_nul(digits);
	args->precision = cmp(args->precision, (int)ft_strlen(digits));
	args->width = cmp(args->width, args->precision);
	dsc = (args->has_precision == 1) && (args->flags == '0');
	if (args->flags == '\0' || dsc)
		res += ft_put_padding(args->width - args->precision, ' ');
	if (args->flags == '0' && args->has_precision == -1)
		res += ft_put_padding(args->width - args->precision, '0');
	res += ft_put_padding(args->precision - ft_strlen(digits), '0');
	res += ft_putstr(digits);
	res += ft_put_padding(args->width - res, ' ');
	free(digits);
	return (res);
}

int		ft_put_x(va_list *ap, t_args *args)
{
	char	*digits;
	int		dsc;
	int		res;

	res = 0;
	digits = ft_uitoa_base(va_arg(*ap, int), HEX);
	if (!digits)
		return (res);
	if (args->has_precision == 1 && digits[0] == '0')
		digits = free_and_dup_nul(digits);
	args->precision = cmp(args->precision, (int)ft_strlen(digits));
	args->width = cmp(args->width, args->precision);
	dsc = (args->has_precision == 1) && (args->flags == '0');
	if (args->flags == '\0' || dsc)
		res += ft_put_padding(args->width - args->precision, ' ');
	if (args->flags == '0' && args->has_precision == -1)
		res += ft_put_padding(args->width - args->precision, '0');
	res += ft_put_padding(args->precision - ft_strlen(digits), '0');
	res += ft_putstr(digits);
	res += ft_put_padding(args->width - res, ' ');
	free(digits);
	return (res);
}

int		ft_put_cx(va_list *ap, t_args *args)
{
	char	*digits;
	int		dsc;
	int		res;

	res = 0;
	digits = ft_uitoa_base(va_arg(*ap, int), CHEX);
	if (!digits)
		return (res);
	if (args->has_precision == 1 && digits[0] == '0')
		digits = free_and_dup_nul(digits);
	args->precision = cmp(args->precision, (int)ft_strlen(digits));
	args->width = cmp(args->width, args->precision);
	dsc = (args->has_precision == 1) && (args->flags == '0');
	if (args->flags == '\0' || dsc)
		res += ft_put_padding(args->width - args->precision, ' ');
	if (args->flags == '0' && args->has_precision == -1)
		res += ft_put_padding(args->width - args->precision, '0');
	res += ft_put_padding(args->precision - ft_strlen(digits), '0');
	res += ft_putstr(digits);
	res += ft_put_padding(args->width - res, ' ');
	free(digits);
	return (res);
}

int		ft_put_padding(int num, int c)
{
	int	res;

	res = 0;
	while (num > 0)
	{
		ft_putchar((char)c);
		num--;
		res++;
	}
	return (res);
}

void	validate_args(va_list *ap, t_args *args)
{
	if (args->w_asterisk)
		args->width = va_arg(*ap, int);
	if (args->p_asterisk)
		args->precision = va_arg(*ap, int);
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
}
