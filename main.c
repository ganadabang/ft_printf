/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonsok <hyeonsok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 20:21:18 by hyeonsok          #+#    #+#             */
/*   Updated: 2021/04/09 23:04:56 by hyeonsok         ###   ########.fr       */
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

	num = ft_printf("-->|%.4c|<--\n", c);
	printf("%d\n", num);
	num = printf("-->|%.4c|<--\n", c);
	printf("%d\n", num);
}
