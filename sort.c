/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkalinic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 16:19:55 by kkalinic          #+#    #+#             */
/*   Updated: 2021/05/07 16:57:10 by kkalinic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_head.h"


void	merge(double *arr, int *ord, int l, int m, int r)
{
	int i;
	int	j;
	int	k;
    int n1;
    int n2;
    n1 = m - l + 1;
	n2 = r - m;
    double L[n1], R[n2];
	int l_o[n1], r_o[n2];
   
	for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];
	for (i = 0; i < n1; i++)
        l_o[i] = ord[l + i];
    for (j = 0; j < n2; j++)
        r_o[j] = ord[m + 1 + j];
    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
			ord[k] = l_o[i];
            i++;
        }
        else {
            arr[k] = R[j];
			ord[k] = r_o[j];
            j++;
        }
        k++;
    }
    while (i < n1) {
        arr[k] = L[i];
		ord[k] = l_o[i];
        i++;
        k++;
    }
    while (j < n2) {
        arr[k] = R[j];
		ord[k] = r_o[j];
        j++;
        k++;
    }
}

void mergeSort(double *arr, int *ord, int l, int r)
{
	int m;

    if (l < r) {
        m = l + (r - l) / 2;
        mergeSort(arr, ord, l, m);
        mergeSort(arr, ord, m + 1, r);
        merge(arr, ord, l, m, r);
    }
}

