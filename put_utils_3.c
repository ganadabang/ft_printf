/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_utils_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonsok <hyeonsok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 17:32:21 by hyeonsok          #+#    #+#             */
/*   Updated: 2021/04/14 15:27:23 by hyeonsok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

char	*free_and_dup_nul(char *digits)
{
	free(digits);
	return (ft_strdup(""));
}

int		cmp(int num1, int num2)
{
	if (num1 < num2)
		return (num2);
	return (num1);
}

int		ft_isminus(int c)
{
	if (c == '-')
		return (1);
	return (0);
}
