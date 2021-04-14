/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonsok <hyeonsok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 17:10:38 by hyeonsok          #+#    #+#             */
/*   Updated: 2021/04/13 17:16:42 by hyeonsok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libftprintf.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	void *first_dst;

	first_dst = dst;
	if (dst == src)
		return (first_dst);
	while (n--)
		*(char *)dst++ = *(char *)src++;
	return (first_dst);
}
