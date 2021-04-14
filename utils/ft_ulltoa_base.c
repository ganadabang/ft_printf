/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ulltoa_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonsok <hyeonsok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 15:48:22 by hyeonsok          #+#    #+#             */
/*   Updated: 2021/04/14 15:16:42 by hyeonsok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libftprintf.h"

static size_t	get_size(unsigned long long n, size_t len)
{
	if (n >= 0 && n < len)
		return (1);
	return (1 + get_size(n / len, len));
}

static char		*conv_to_str(char *str, size_t abs, char *set)
{
	if (str == NULL)
		return (NULL);
	if (abs == 0)
		return (str);
	else
	{
		*(--str) = set[abs % ft_strlen(set)];
	}
	return (conv_to_str(str, abs / ft_strlen(set), set));
}

char			*ft_ulltoa_base(unsigned long long n, char *set)
{
	size_t	size;
	char	*str;

	size = get_size(n, ft_strlen(set));
	str = ft_calloc(size + 1, sizeof(char));
	if (!str)
		return (NULL);
	if (n == 0)
	{
		*str = '0';
		return (str);
	}
	return (conv_to_str(str + size, n, set));
}
