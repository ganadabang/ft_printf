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
#include "stdio.h"

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
	int		res;

	digits = ft_itoa(va_arg(*ap, int));
	if (args->has_precision == 1 && digits[0] == '0')
		digits = "";
	res = 0;
	if (digits[0] == '-')
		args->precision++;
	if (args->precision < (int)ft_strlen(digits))
		args->precision = (int)ft_strlen(digits);
	if (args->width < args->precision)
		args->width = args->precision;
	if (args->flags == '\0')
		res += ft_put_padding(args->width - args->precision, ' ');
	if (digits[0] == '-')
		ft_putchar(*digits++);
	if (args->flags == '0')
		res += ft_put_padding(args->width - args->precision, '0');
	res += ft_put_padding(args->precision - ft_strlen(digits), '0');
	res += ft_putstr(digits);
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

// di

//precision이 존재할 때 flag의 0 옵션이 고려되지 않고 있다.
//그냥 flag를 가지지 않은 것과 동일하게 출력되는 것 같다.
//precision이 음수일 때는 precision이 없는 것 처럼 움직이는 것 같다.
//precision에 의해서 0이 출력될 때는 자기 자신을 게산해서 하나 제외한다.
//나머지는 거의 동일한 것으로 보인다.
//음수일때precision을 고려할 때 주의할 필요가 있다.

