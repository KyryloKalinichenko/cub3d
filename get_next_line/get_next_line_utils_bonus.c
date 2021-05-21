/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkalinic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 14:47:09 by kkalinic          #+#    #+#             */
/*   Updated: 2021/05/13 17:21:49 by kkalinic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub_head.h"
#include <unistd.h>

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	j;
	char	*str;

	if (s)
	{
		str = malloc(sizeof(char) * (len + 1));
		if (!str)
			return (NULL);
		i = 0;
		j = 0;
		while (s[i])
		{
			if (i >= start && j < len)
			{
				str[j] = s[i];
				j++;
			}
			i++;
		}
		str[j] = '\0';
		return (str);
	}
	return (NULL);
}

char	*ft_strdup(const char *s)
{
	char	*dup;
	int		i;

	i = -1;
	if (s)
	{
		dup = malloc(sizeof(char) * (ft_strlen((char *)s) + 1));
		if (dup == NULL)
			return (NULL);
		while (s[++i])
			dup[i] = s[i];
		dup[i] = '\0';
		return (dup);
	}
	return (NULL);
}

char	*ft_strchr(const char *s, int c)
{
	if (s)
	{
		if ((char)c == '\0')
			return ((char *)s + ft_strlen(s));
		while (*s)
		{
			if (*s == c)
				return ((char *)s);
			s++;
		}
	}
	return (NULL);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*a;

	if (s1 && s2)
	{
		a = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
		if (a == NULL)
			return (NULL);
		a[(ft_strlen(s1) + ft_strlen(s2))] = '\0';
		a = ft_strncpy(a, s1, (ft_strlen(s1) + 1));
		a = ft_strcat(a, s2);
		return (a);
	}
	return (NULL);
}

int	reading(int fd, char *buff, int *i)
{
	*i = read(fd, buff, BUFFER_SIZE);
	if (*i > 0)
	{
		buff[*i] = '\0';
		return (1);
	}
	else
		return (0);
}
