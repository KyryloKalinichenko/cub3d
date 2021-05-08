/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkalinic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 16:53:17 by kkalinic          #+#    #+#             */
/*   Updated: 2021/05/08 16:53:27 by kkalinic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/cub_head.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*n_s;

	n_s = s;
	while (n)
	{
		*n_s = 0;
		n_s++;
		n--;
	}
}

int	ft_get_r(int m)
{
	return (0x00000000 | ((m >> 16) & 0xFFFFFFFF));
}

int	ft_get_g(int m)
{
	return (0x00000000 | ((m >> 8) & 0xFFFFFFFF));
}

int	ft_get_b(int m)
{
	return (0x00000000 | ((m) & 0xFFFFFFFF));
}

void	limits(int *start, int *end, int limit)
{
	if (*start < 0)
		*start = 0;
	if (*end > limit)
		*end = limit;
}
