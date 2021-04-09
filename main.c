/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonsok <hyeonsok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 20:21:18 by hyeonsok          #+#    #+#             */
/*   Updated: 2021/04/10 00:49:52 by hyeonsok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"
#include <stdio.h>

# define F(...) \
	ft_printf(__VA_ARGS__)

int	main(void)
{
	int	num;
	char c = 'a';

	printf("===========================\n");
	num = ft_printf("-->|%.4c|<--\n", c);
	printf("%d\n", num);
	num = printf("-->|%.4c|<--\n", c);
	printf("%d\n", num);

	printf("===========================\n");
	num = ft_printf("-->|%|<--\n", c);
	printf("%d\n", num);
	num = printf("-->|%|<--\n", c);
	printf("%d\n", num);

	printf("===========================\n");
	num = ft_printf("-->|%4.c|<--\n", c);
	printf("%d\n", num);
	num = printf("-->|%4.c|<--\n", c);
	printf("%d\n", num);
}
