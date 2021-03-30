/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkalinic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 12:28:52 by kkalinic          #+#    #+#             */
/*   Updated: 2020/12/11 18:14:10 by kkalinic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int					ft_isotherwhitespace(char c)
{
	return (c == '\v' || c == '\f' || c == '\r');
}

static int					ft_isstrwhitespace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

static int					ft_iswhitespace(char c)
{
	return (ft_isstrwhitespace(c) || ft_isotherwhitespace(c));
}

int							ft_atoi(const char *str)
{
	int						i;
	unsigned long long int	nbr;
	long long int			sign;

	i = 0;
	nbr = 0;
	sign = 1;
	while (ft_iswhitespace(str[i]))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] && ft_isdigit(str[i]))
	{
		nbr = nbr * 10 + str[i] - '0';
		i++;
	}
	if (nbr < 0 || i > 19)
		return (nbr = (sign > 0) ? -1 : 0);
	return (nbr * sign);
}
