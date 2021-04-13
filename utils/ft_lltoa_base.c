/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lltoa_base .c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonsok <hyeonsok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 15:48:22 by hyeonsok          #+#    #+#             */
/*   Updated: 2021/04/12 19:24:00 by hyeonsok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libftprintf.h"

static unsigned int	get_len(unsigned int n, unsigned int len)
{
	if (n >= 0 && n < len)
		return (1);
	return (1 + get_len(n / len, len));
}

static char			*conv_abs_to_str(char *str, size_t abs, char *set)
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

char				*ft_lltoa_base(long long n, char *set)
{
	long long	len;
	char		*str;

	len = get_len(n, ft_strlen(set));
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
