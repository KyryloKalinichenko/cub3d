/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkalinic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 16:19:55 by kkalinic          #+#    #+#             */
/*   Updated: 2021/05/08 15:22:16 by kkalinic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub_head.h"

void	swap(int *xp, int *yp)
{
	int	temp;

	temp = *xp;
	*xp = *yp;
	*yp = temp;
}

void	swap_d(double *xp, double *yp)
{
	int	temp;

	temp = *xp;
	*xp = *yp;
	*yp = temp;
}

void	bubbleSort(double *arr, int *ord, int n)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < n - 1)
	{
		while (j < (n - i - 1))
		{
			if (arr[j] > arr[j + 1])
			{
				swap_d(&arr[j], &arr[j + 1]);
				swap(&ord[j], &ord[j + 1]);
			}
			++j;
		}
		j = 0;
		++i;
	}
}
