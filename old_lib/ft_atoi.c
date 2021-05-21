/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkalinic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 12:28:52 by kkalinic          #+#    #+#             */
/*   Updated: 2021/05/04 13:28:51 by kkalinic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub_head.h"

int	ft_isotherwhitespace(char c)
{
	return (c == '\v' || c == '\f' || c == '\r');
}

int	ft_isstrwhitespace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

int	ft_iswhitespace(char c)
{
	return (ft_isstrwhitespace(c) || ft_isotherwhitespace(c));
}

int	ft_atoi(const char *str)
{
	int						i;
	unsigned long long int	nbr;
	long long int			sign;

	i = 0;
	nbr = 0;
	sign = 1;
	while (ft_iswhitespace(str[i]))
		i++;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	while (str[i] && ft_isdigit(str[i]))
	{
		nbr = nbr * 10 + str[i] - '0';
		i++;
	}
	if (nbr < 0 || i > 19)
	{
		if (sign > 0)
			return (-1);
	}
	return (nbr * sign);
}
