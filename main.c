/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonsok <hyeonsok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 20:21:18 by hyeonsok          #+#    #+#             */
/*   Updated: 2021/04/12 21:13:36 by hyeonsok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"
#include <stdio.h>

#ifdef TEST
# define F(...) \
	ft_printf(__VA_ARGS__)
# else

# define F(...) \
	printf(__VA_ARGS__)
#endif

int	main(void)
{
	int	num;
	int c;

	c = 'a';

	// printf("-->|%-1c|<--\n", c);
	// Printf("-->|%.c|<--\n", c);

	char *s;
	char *p;

	s = "hello";
	p = s;
	// F("-->|%*.9p|<--\n", -16, p);
	// F("-->|%*.p|<--\n", -15, p);
	// F("-->|%-15.p|<--\n", p);
	// F("-->|%-3.p|<--\n", p);
	// F("-->|%-16.p|<--\n", p);
	// p = NULL;
	// F("-->|%*.p|<--\n", -16, p);
	// F("-->|%*.p|<--\n", -15, p);
	// F("-->|%-15.p|<--\n", p);
	// F("-->|%-17.0p|<--\n", p);
	// F("-->|%-17.p|<--\n", p);
	// F("-->|%-17.2p|<--\n", p);
	// F("-->|%-17.3p|<--\n", p);
	// F("-->|%-17.20p|<--\n", p);

	// F("-->|%*.p|<--\n", 12, p);
	// F("-->|%*.p|<--\n", 13, p);
	// F("-->|%*.p|<--\n", 14, p);
	// F("-->|%*.p|<--\n", 15, p);
	// F("-->|%*.p|<--\n", 16, p);
	// p = NULL;
	// F("-->|%-15p|<--\n", p);
	// F("-->|%-15p|<--\n", p);
	// F("-->|%-16.p|<--\n", p);
	// F("-->|%-16p|<--\n", p);
	// F("-->|%-16p|<--\n", p);
	// F("-->|%-4.%|<--\n");
	// F("-->|%-4.*%|<--\n", -4);
	// F("-->|%-4.*%|<--\n", -3);
	// F("-->|%-4.*%|<--\n", -2);
	// F("-->|%-4.*%|<--\n", -1);
	// F("-->|%-4.1%|<--\n");
	// F("-->|%-4.2%|<--\n");
	// F("-->|%-4.3%|<--\n");
	// F("-->|%-4.4%|<--\n");
	// F("-->|%-4%|<--\n");
	int d;
	d = 0;
	int x;
	x = d;
	// F("-->|%-4.1x|<--\n", x);
	// F("-->|%-4.2x|<--\n", x);
	// F("-->|%-4.3x|<--\n", x);
	// F("-->|%-4.4x|<--\n", x);
	d = -135;
	F("-->|%-4.*d|<--\n", 4, d);

	printf("%-10.7s", "hello");
}

// Assertion failed: (printf("-->|%-2p|<--\n", p) == ft_printf("-->|%-2p|<--\n", p)), function
//  test_func_p, file sources/test_func_p.c, line 41.
// ./printf_lover.sh: line 249: 53500 Abort trap: 6           $ASSERT_TESTS_PATH/printf_breake
// r_returns $text > $OUTPUTS_PATH/asserts_output
// }
/*
width에 음수가 -> 양수로 바꾸고 좌측정렬로 변경된다.
p의 길이가 width보다 클때 최소한 p의 길이만큼 출력된다.

precision - 주소길이 만큼 0x 다음 0을 출력시킨다
둘 중의 큰 값이 총 출력해야하는 주소의 길이가 되고	precision 이 고려된 출력값이 즉 절대로 지켜져야 되는 값인 거..

너비가 이 값보다 더 크면 그 수치만큼 패딩이 채워지고 너비가 반환값이 된다.
너비가 이 수치보다 같거나 작다면 패딩이 채워지지 않는다.

내부적으로 어떻게 이뤄지는지 이제 알겠죠??

숫자를 가지고 있음 주소의 길이를 ft_getdigits isascii

 */

/*
	int					len;
	unsigned long long	addr;
	char				*digits;
	int					res;

	addr = (unsigned long long)va_arg(*ap, void *);
	digits = ft_utoa_base(addr, HEX);
	if (args->has_precision == 1 && digits[0] == '0')
		digits = "";
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
*/