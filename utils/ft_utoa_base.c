/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonsok <hyeonsok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 15:48:22 by hyeonsok          #+#    #+#             */
/*   Updated: 2021/04/10 19:45:24 by hyeonsok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libftprintf.h"

static unsigned	int		get_len(unsigned long long n)
{
	if (n >= 0 && n < 10)
		return (1);
	return (1 + get_len(n / 10));
}

static char			*conv_abs_to_str(char *str, unsigned long long abs, char *set)
{
	if (str == NULL)
		return (NULL);
	if (abs == 0)
		return (str);
	else
	{
		*(--str) = set[abs % ft_strlen(set)];
	}
	return (conv_abs_to_str(str, abs / ft_strlen(set), set));
}

char				*ft_utoa_base(unsigned long long n, char *set)
{
	unsigned long long	len;
	char			*str;

	len = get_len(n);
	str = ft_calloc(len + 1, sizeof(char));
	if (!str)
		return (NULL);
	if (n == 0)
	{
		*str = '0';
		return (str);
	}
	return (conv_abs_to_str(str + len, n, set));
}
