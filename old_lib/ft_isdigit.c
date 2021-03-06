/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkalinic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 12:26:26 by kkalinic          #+#    #+#             */
/*   Updated: 2021/05/04 13:29:46 by kkalinic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub_head.h"

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

void	tab_free(char **tab)
{
	int	i;

	i = -1;
	while (tab[++i])
		free(tab[i]);
	free(tab);
}
