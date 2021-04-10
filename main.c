/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonsok <hyeonsok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 20:21:18 by hyeonsok          #+#    #+#             */
/*   Updated: 2021/04/10 22:20:59 by hyeonsok         ###   ########.fr       */
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
	// printf("-->|%c|<--\n", c);
	// printf("-->|%*.c|<--\n", -4, c);
	// printf("-->|%*.c|<--\n", -3, c);
	// printf("-->|%*c|<--\n", 3, c);
	// printf("-->|%*c|<--\n", 4, c);
	// printf("-->|%1.c|<--\n", c);
	// Printf("-->|%1c|<--\n", c);
	// printf("-->|%2.c|<--\n", c);

	// num = printf("-->|%*.c|<--\n", -4, c);
	// printf("%d\n", num);
	// num = printf("-->|%*.s|<--\n", NULL);
	// printf("%d\n", num);
	// num = printf("-->|%*.1s|<--\n", NULL);
	// printf("%d\n", num);
	// num = printf("-->|%*.2s|<--\n", NULL);
	// printf("%d\n", num);
	// num = ft_printf("-->|%0.10s|<--\n", NULL, "Hello world");
	// printf("%d\n", num);
	// num = printf("-->|%*.4s|<--\n", NULL);
	// printf("%d\n", num);
	char *s;

	s = "hello";
// F("-->|%-16.s|<--\n", s);
// F("-->|%-16.*c|<--\n", -4, c);
// F("-->|%016.*s|<--\n", -3, s);
// F("-->|%-16.*s|<--\n", -2, s);
// F("-->|%-16.*s|<--\n", -1, s);
// F("-->|%-16.13s|<--\n", s);
// F("-->|%-16.14s|<--\n", s);
// F("-->|%-16.15s|<--\n", s);
// F("-->|%-16.16s|<--\n", s);
// F("-->|%-16s|<--\n", s);



// F("-->|%-16s|<--\n", s);
// s = NULL;
// F("-->|%-16s|<--\n", s);

// num = F("-->|%-16.s|<--\n", s);

// printf("%d", num);


// printf("-->|%-16.*s|<--\n", -4, s) == ft_printf("-->|%-16.*s|<--\n", -4, s)), function test_func_s, file sources/test_func_s.c, line 15.
// ./printf_lover.sh: line 249: 84837 Abort trap: 6           $ASSERT_TESTS_PATH/printf_breaker_returns $text > $OUTPUTS_PATH/asserts_output

	// s = NULL;
	char *p;

	p = s;
F("-->|%*.p|<--\n", -16, p);
F("-->|%*.p|<--\n", -15, p);
F("-->|%-15.p|<--\n", p);
F("-->|%-3.p|<--\n", p);
F("-->|%-16.p|<--\n", p);
p = NULL;
F("-->|%*.p|<--\n", -16, p);
F("-->|%*.p|<--\n", -15, p);
F("-->|%-15.p|<--\n", p);
F("-->|%-17.0p|<--\n", p);
F("-->|%-17.1p|<--\n", p);
F("-->|%-17.2p|<--\n", p);
F("-->|%-17.3p|<--\n", p);
F("-->|%-17.4p|<--\n", p);

}