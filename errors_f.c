/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_f.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkalinic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 14:10:56 by kkalinic          #+#    #+#             */
/*   Updated: 2021/04/12 14:11:58 by kkalinic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_head.h"

void	malloc_error(void)
{
	printf("Malloc error!\n");
	exit(EXIT_FAILURE);
}

void	just_exit(void)
{
	printf("See you soon!\n");
	exit(EXIT_FAILURE);
}

void	no_file(void)
{
	printf("No such file or directory!\n");
	exit(EXIT_FAILURE);
}

void	map_err(void)
{
	printf("Bad map!\n");
	exit(EXIT_FAILURE);
}
