/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readargs_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonsok <hyeonsok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 16:04:04 by hyeonsok          #+#    #+#             */
/*   Updated: 2021/04/09 17:30:56 by hyeonsok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

void	initialize_args(t_args *args)
{
	ft_memset(args, 0, sizeof(t_args));
}

int		ft_isflag(int c)
{
	return ((c == '0') || (c == '-'));
}

int		ft_istype(char c, t_args *args)
{
	char	*type;

	type = ft_strchr(CONV, c);
	if (type != NULL)
	{
		args->type = *type;
		return (1);
	}
	return (0);
}

int		ft_getdigits(char *str)
{
	char	*idx;

	idx = str;
	if (*idx == '+' || *idx == '-')
		idx++;
	while (ft_isdigit(*idx))
		idx++;
	return (idx - str);
}
