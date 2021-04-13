/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readargs_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonsok <hyeonsok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 16:04:04 by hyeonsok          #+#    #+#             */
/*   Updated: 2021/04/12 14:28:40 by hyeonsok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int	ft_isflag(int c)
{
	return ((c == '0') || (c == '-'));
}

int	ft_getdigits(char *str)
{
	char	*idx;

	idx = str;
	if (*idx == '+' || *idx == '-')
		idx++;
	while (ft_isdigit(*idx))
		idx++;
	return (idx - str);
}

int	ft_isminus(int c)
{
	if (c == '-')
		return (1);
	return (0);
}

int	ft_isformat(int c)
{
	return (ft_strchr(CONV, c) || ft_isspace(c) || ft_isflag(c) || \
	ft_isdigit(c) || (c == '.') || (c == '*'));
}
