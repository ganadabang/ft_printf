/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonsok <hyeonsok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 15:37:48 by hyeonsok          #+#    #+#             */
/*   Updated: 2021/04/09 17:36:30 by hyeonsok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libftprintf.h"

void	*ft_calloc(size_t count, size_t size)
{
	void				*ptr;
	void				*first_ptr;
	unsigned long long	len;

	len = size * count;
	ptr = (void *)malloc(len);
	if (!ptr)
		return (NULL);
	first_ptr = ptr;
	while (len--)
		*(char *)ptr++ = '\0';
	return (first_ptr);
}
